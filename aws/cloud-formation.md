# CloudFormation

Resources:  your was resources declared in the template

Parameters: the dynamic inputs for your template

Mappings: the static variables for your template

Outputs: references to what has been created

Conditionals: list of conditions to perform resource creation

Metadata



## Parameters

Parameters can be controlled by all bellow settings

- Type
  - String
  - Number
  - CommaDelimiterdList
  - List<Type>
  - AWS Parameter
- Description
- Constraints
- ConstraintDescription
- Min/MaxLength
- Default
- AllowedValues
- AllowedParttens
- NoEcho(not echo to console, can protect like password things)

**Reference parameter**

- The Fn::Ref function can be leveraged to reference parameters
- Parameters can be used anywhere in a template
- The shorthand for Fn::Ref in YAML is !Ref
- The Fn::Ref can also reference other elements within the template

**Pseudo Parameters**

- aws offers pseudo parameters in any CloudFormation template
- it can be used at any time and are enabled by default

Eg:

- AWS::AccountId
- AWS::NotificationARNs
- AWS::NoValue
- AWS::Region
- AWS::StackId
- AWS::StackName



```yaml
Parameters:
  SecurityGroupDescription:
    Description: Security Group Description (Simple parameter)
    Type: String
  SecurityGroupPort:
    Description: Simple Description of a Number Parameter, with MinValue and MaxValue
    Type: Number
    MinValue: 1150
    MaxValue: 65535
  InstanceType:
    Description: WebServer EC2 instance type (has default, AllowedValues)
    Type: String
    Default: t2.small
    AllowedValues:
      - t1.micro
      - t2.nano
      - t2.micro
      - t2.small
    ConstraintDescription: must be a valid EC2 instance type.
  DBPwd:
    NoEcho: true
    Description: The database admin account password (won't be echoed)
    Type: String
  KeyName:
    Description: Name of an existing EC2 KeyPair to enable SSH access to the instances. Linked to AWS Parameter
    Type: AWS::EC2::KeyPair::KeyName
    ConstraintDescription: must be the name of an existing EC2 KeyPair.
  SecurityGroupIngressCIDR:
    Description: The IP address range that can be used to communicate to the EC2 instances
    Type: String
    MinLength: '9'
    MaxLength: '18'
    Default: 0.0.0.0/0
    AllowedPattern: (\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})/(\d{1,2})
    ConstraintDescription: must be a valid IP CIDR range of the form x.x.x.x/x.
  MyVPC:
    Description: VPC to operate in
    Type: AWS::EC2::VPC::Id
  MySubnetIDs:
    Description: Subnet IDs that is a List of Subnet Id
    Type: "List<AWS::EC2::Subnet::Id>"
  DbSubnetIpBlocks:
    Description: "Comma-delimited list of three CIDR blocks"
    Type: CommaDelimitedList
    Default: "10.0.48.0/24, 10.0.112.0/24, 10.0.176.0/24"

Resources:
  MyEC2Instance:
    Type: "AWS::EC2::Instance"
    Properties:
      #we reference the InstanceType parameter
      InstanceType: !Ref InstanceType
      KeyName: !Ref KeyName
      ImageId: "ami-a4c7edb2"
      # here we reference an internal CloudFormation resource
      SubnetId: !Ref DbSubnet1

  MySecurityGroup:
    Type: "AWS::EC2::SecurityGroup"
    Properties:
      GroupDescription: !Ref SecurityGroupDescription
      SecurityGroupIngress:
        - CidrIp: !Ref SecurityGroupIngressCIDR
          FromPort: !Ref SecurityGroupPort
          ToPort: !Ref SecurityGroupPort
          IpProtocol: tcp
      VpcId: !Ref MyVPC

  DbSubnet1:
    Type: AWS::EC2::Subnet
    Properties:
      VpcId: !Ref MyVPC
      # the select function allows us to select across a list
      CidrBlock: !Select [0, !Ref DbSubnetIpBlocks]
  DbSubnet2:
    Type: AWS::EC2::Subnet
    Properties:
      VpcId: !Ref MyVPC
      # the select function allows us to select across a list
      CidrBlock: !Select [1, !Ref DbSubnetIpBlocks]
  DbSubnet3:
    Type: AWS::EC2::Subnet
    Properties:
      VpcId: !Ref MyVPC
      # the select function allows us to select across a list
      CidrBlock: !Select [2, !Ref DbSubnetIpBlocks]

```



## Resources

- The core of the CloudFormation template
- it represent the different AWS Components that will be createda nd configured
- Resources are declared and can reference each other
- AWS figures out creation updates and deletes of resources for us
- There are over 224 types of resources
- Resources types identifiers are of the form: `AWS::aws-product-name::data-type-name`



optonal attributes

- DependsOn: draw a dependency between tow resources
- DeletionPolicy: protect resources from being deleted even if the cloud formation is deleted(e,g RDS database)
- CreationPolicy
- Metadata:



## Mappings

- Mappings are fixed variables within the CloudFormation Template
- it's very handy to differentiate between different environments
- All the values are hardcoded within the template



## Outputs

- Outputs section declares optional outputs values that can import into other stacks
- we can also view the outputs in the AWS Console or using in the AWS CLI
- Use to perform some collaboration cross stacks
- Use Fn::ImportValue to import the outputs content



## CFN-Init

EC2 **UserData**: user data script will be executed at the first boot of the instance

- cfn-init: Used to retrieve and interpret the resource metadata, install packages, creating files and starting services
- cfn-signal: a simple wrapper to signal an was CloudFormation CreationPolicy or WaitCondition, enabling to synchronize other resources in the stack with the application being ready
- cfn-get-metadata: 
- cfn-hup





## Drift















