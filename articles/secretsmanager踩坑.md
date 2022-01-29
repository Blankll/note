# AWS Secrets Manager 踩坑记

最近项目上在引入secretsmanger作为RDS密码管理以取代直接将密码放在config中的实现，同时要加入secretsmanger的password auto rotation的功能，看似平平无奇的功能，却着实让人踩了很多坑。

首先来看看secretsmanger是什么呢？顾名思义，就是一个密码管理的serverless的服务，将通常保存在config文件中的敏感数据如密码，用户名保存到secretsmanger中，可以是诸如数据库连接凭证，也可以单纯的存储其它的第三方登录凭证。

> AWS Secrets Manager helps you protect secrets needed to access your applications, services, and IT resources. The service enables you to easily rotate, manage, and retrieve database credentials, API keys, and other secrets throughout their lifecycle.

AWS Secrets Manager 以key/value pair的方式存储secrets的内容，同时支持secrets cross region replication，rotation等， 目前一下服务已经支持完备的rotaion功能，第三方的secrets也可以通过实现自己的lambda进行rotaion。

- 

### 为什么要用secretsmanager

我一直信奉大道至简的理念，如果没有迫切的需求或切实的收益而增加一个依赖或服务，就是徒增(脑)烦恼(残)。所以为什么要加入它呢？

1. 增加安全性：显而易见，敏感信息将不再存储在代码中，同时如果项目也是构建在AWS之上的，那么于其它服务的深度集成也是十分便利的
2. 地区法律或规定的要求：可能受制于地方法律或在项目合同要求密码需要rotaion，audit等等功能
3. 便于多服务下的统一密码管理

那么在没有引入诸如secretsmanager服务之前，我们通常如何管理密码的呢？

1. 纯文本存储

   一般的项目有可能直接就将密码存到config中，可能并不加密(真实case，并不是编出来的)，出于安全考虑，这个config一般不会被git trace，当然头铁放进去在天朝也不违法。那这样的安全问题就显而易见，无论是否被git trace，source code泄露或者服务器被偷都会将密码。

   但是，这就是烂的设计吗？我觉得不一定，至少分情况：如果一个应用的安全要求并没有太高(如这个博客应用)，这样的设计我认为恰好是合适的,我发了篇文章手动备个份，即便整个被黑了还不是重新部署一下的事情。如果引入我下面举例的实现，安全性提升带来的收益并不与付出与复杂性相等。所以我认为这样的方式也是有其应用场景与价值的。

2. 环境变量载入

   将密码作为环境变量进行载人，在container或主机终止时，密码信息便无法获取，非敏感配置便可以放到config中并加入version control中。这样做就需要在服务或容器或主机启动时主动注入环境变量，如果集成了如github action这样可以支持密码存储的CI/CD工具，那么也可以以比较方便且安全的方式将密码信息注入到环境变量中。但如果手动部署(不要奇怪，即便2022，不是所有项目都前后分离，也不是所有项目都有CI/CD), 那么启动参数将会爆炸。

3. 存储加密密码文本

   在这种方式下我们将敏感信息通过密钥进行加密，在容器&服务启动或在密码需要被使用时进行解密，解密的密钥一般也可以通过环境变量在容器&服务启动时注入。

3. config server

   可以将密码等信息统一的存储到config server中如[Spring Cloud Config](https://cloud.spring.io/spring-cloud-config/reference/html/)，与应用服务相解耦，减少脱库泄露密码的风险，同时，config server在微服务的项目中可以有效的减少密码和其它配置信息的冗余。

3. Secrets-manager platform

   相较于config server，secrets-manager 更关注于密码存储的安全性，如加入secrets-manager自己的ACL以及密码audit，dynamic secrets等功能，同时复杂度也会进一步的提升。AWS Secrets Manager 便是其中的一种，还有如[Valut](https://www.vaultproject.io/)等。

   

### 怎么用AWS Secrets Manager

secrets-manager的使用看上去还是很简单的，如果你使用过其它aws的服务，那么它的套路也是熟悉的配方，我们可以通过下面的cloudformation来看一下一个比较完整的case:

也可以参考官方文档中的[sample](https://docs.aws.amazon.com/AWSCloudFormation/latest/UserGuide/aws-resource-secretsmanager-rotationschedule.html)

```yml
AWSTemplateFormatVersion: '2010-09-09'
Transform: AWS::SecretsManager-2020-07-23

Parameters:
  DatabaseARN:
    Type: String
  KmsKeyARN：
  	Type: String
	SecurityGroup:
		Type: String
	VpcSubnets:
		Type: String
	
Resources:
  PostgresSecret:
    Type: AWS::SecretsManager::Secret
    Properties:
      Name: secretsName
      KmsKeyId: !Ref KmsKeyARN
      GenerateSecretString:
        SecretStringTemplate: !Sub '{"username": "postgres", "dbname": "postgres","ssl": false}'
        GenerateStringKey: password
        PasswordLength: 12
        ExcludeCharacters: "\"@/\\"
  PostgresAttachment:
    Type: AWS::SecretsManager::SecretTargetAttachment
    Properties:
      SecretId: !Ref PostgresSecret
      TargetId: !Ref DatabaseARN
      TargetType: AWS::RDS::DBInstance
  PostgresSecretRotation:
    Type: AWS::SecretsManager::RotationSchedule
    DependsOn: PostgresAttachment
    Properties:
      SecretId: !Ref PostgresSecret
      HostedRotationLambda:
        RotationType: PostgreSQLSingleUser
        RotationLambdaName: PostgreSecretsManagerRotationLambda
        KmsKeyArn: !Ref KmsKeyARN
        VpcSecurityGroupIds: !Ref SecurityGroup
        VpcSubnetIds: !Ref VpcSubnets
      RotationRules:
        AutomaticallyAfterDays: 60

```

从以上的sample中我们可以看到主要有三个resource: 密码自身、与RDS attach,以及rotation的需要的资源。我们可以逐个分析一下

1. `AWS::SecretsManager::Secret`

   密码自身，可以看到上面的sample中密码是自动生成的，我们只是做了简单的规约。同时我们需要指定一个kms 对我们的secrets进行加密。

   这里比较tricky的一点是，如果我们想要只想存储一个非rotation的密码，是没办法直接在cloudformation中完成的，我们不能把密码直接写在cloudformation中，即便用参数的方式传入，stack上的parameter是明文显示的，所以如只是存储非rotaiton的secrets，最好在stack生成之后在console上手动update。

2. `AWS::SecretsManager::SecretTargetAttachment`

   该资源用于将创建的secrets与数据库进行相关联，secrets manage目前可以支持一下服务的attach和rotaion：

   - Amazon Aurora on Amazon RDS
   - MySQL on Amazon RDS
   - PostgreSQL on Amazon RDS
   - Oracle on Amazon RDS
   - MariaDB on Amazon RDS
   - Microsoft SQL Server on Amazon RDS
   - Amazon DocumentDB
   - Amazon Redshift

3. `AWS::SecretsManager::RotationSchedule`

   定义secrets rotaion的规则。上面列出的服务都已经很好的支持的rotation，aws官方提供了lamba的实现，HostedRotationLambda 会启动一个Nested lamba来进行roation，你只需要配置好相关的参数即可。如果需要对非上述服务的密码或第三方的其它密码也进行rotaiton，则需要显示部署一个进行rotaion的lambda来实现rotaiton。需要为rotaitonlambda指定相应的secuirty group和subnets使其可以访问目标服务。

## 遇到了哪些坑？

上面的一切都看似简单且美好，但在使用它之前你可能需要看看我遇到的这些坑。

























