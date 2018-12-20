# 使用Laravel进行Api开发

## passort

passport 是一个laravel下的oauth2.0实现

安装passport laraveldocument 

### 通过GuzzleHttp　进行请求转发

在进行oauth２．０验证时，前端需要传递包括client _id, client_secret的敏感信息，通过GuzzleHttp，我们在后端将请求的敏感信息保存在服务器端，当需要进行验证时进行请求参数拼接，再通过GuzzleHttp进行真正的请求。

安装guzzleHttp

```bash
composer require guzzlehttp/guzzle
```

在Lib下面建立一个proxy文件夹，创建一个OauthProxy trait 

```php
<?php

namespace App\Lib\Proxy;

use GuzzleHttp\Client;
use App\Exceptions\UnauthorizedException;
use GuzzleHttp\Exception\RequestException;

trait OauthProxy {
    public function passwordAuthenticate(array $data = [])
    {
        $client = new Client();
        try{
            $url = env('APP_URL').'/oauth/token';
            $params = array_merge(config('passport.password'), $data);
            $respond = $client->request('POST', $url, ['form_params' => $params]);
        }catch(RequestException $e){
            if(400 == $e->getCode())
            {
                throw new UnauthorizedException('用户名密码不匹配，请重试', 4002, 400);
            }
            else
            {
                throw new UnauthorizedException('请求失败，服务器错误');
            }
            
        }

        if($respond->getStatusCode() !== 401)
        {
            return json_decode($respond->getBody()->getContents(), true);
        }

        throw new UnauthorizedException('账号与密码不匹配');
    }
}
```

在服务器端返回登录数据时，应将refreshToken保存在coockie中,cookie的过期时间和我门在AuthServiceProvider中设置的refreshTokensExpireIn时间一致。

将请求的数据返回给客户端客户端信息如下

```json
{
    "code": 2000,
    "message": "登录成功",
    "data": {
        "token_type": "Bearer",
        "expires_in": 900,
        "access_token": "access_token",
        "refresh_token": "refresh_token"
    }
}
```

客户端在登录后每次请求中，都要将http头中的Authorization设置为如下格式

```javas
axios.defaults.headers.common['Authorization'] = token.token_type + ' ' + token.access_token
```

## 退出登录

客户端请求退出登录

服务器端将access_token删除，　refresh_token 标记为revoke,删除cookie信息

请求成功后，客户端删除token信息

