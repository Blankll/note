# gitlab

## installation

- 关闭centos防火墙

  ```bash
  systemctl stop firewalld
  systemctl stop firewalld
  ```

- 关闭SELINUX并重启系统

  ```bash
  # vim /etc/sysconfig/selinux
  SELINUX=disabled
  ```

getinforce查看selinux是否关闭

Omnibus gitlab-ce 直接安装的安装包，包含各类插件

- 安装依赖

  ```bash
  yum -y install curl policycoreutils openssh-server openssh-clients postfix
  ```

- 安装 gitlab

  ```bash
  curl -sS https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.rpm.sh | sudo bash
  ```

- 启动postfix邮件服务

  ```bash
  systemctl start postfix && systemctl enable postfix
  ```

- 安装gitlab-ce

  ```bash
  yum install -y gitlab-ce
  ```

- openssl 创建本地证书

  ```bash
  mkdir /etc/gitlab/ssl
  openssl genrsa -out "/etc/gitlab/ssl/gitlab.blank.com.key"
  openssl req -new -key "/etc/gitlab/ssl/gitlab.blank.com.key" -out "/etc/gitlab/ssl/gitlab.blank.com.csr"
  openssl x509 -req -days 365 -in "/etc/gitlab/ssl/gitlab.blank.com.csr" -signkey "/etc/gitlab/ssl/gitlab.blank.com.key" -out "/etc/gitlab/ssl/gitlab.blank.com.crt"
  openssl dhparam -out /etc/gitlab/ssl/dhparams.pem 2048
  chmod 600 ./*
  ```

  编辑gitlab配置文件

  ```bash
  # vim /etc/gitlab/gitlab.rb
  external_url 'https://gitlab.blank.com'
  
  nginx['redirect_http_to_https']=true
  nginx['ssl_certificate']="/etc/gitlab/ssl/gitlab.blank.com.key"
  nginx['ssl_certificate']="/etc/gitlab/ssl/gitlab.blank.com.key"
  nginx['ssl_dhparam']="/etc/gitlab/ssl/dhparams,pem"
  ```

  ```bash
  gitlab-ctl reconfigure
  ```

- Nginx SSL代理服务配置

  ```bash
  # vim /var/opt/gitlab/nginx/conf/gitlab-http.conf
  server_name gitlab.blank.com
  rewrite ^(.*)$ https://$host$1 permanent;
  ```

  ```bash
  gitlab-ctl restart
  ```

  在windows本机上创建一条dns记录gitlab.blank.com指向 虚拟机ip

- 初始化gitlab服务

  https://gitlab.blank.com

- clone

  ```bash
  git -c http.sslverify=false clone https://gitlab.blank.com/repository.git
  ```



## Ansible

### Ansible2.5 + python3.6 installation

1. 安装python3.6

2. 安装virtulaenv

   ```bash
   pip install virtualenv
   ```

3. 创建Ansible账户并创建python3.6版本的virtualenv实例

   ```bash
   useradd deploy && su -deploy
   virtualenv -p /usr/local/bin/python3 .py3-a2.5-env
   ```

4. 源代码安装Ansible2.5

   ```bash
   git clone https://github.com/ansible/ansible.git
   cd ansible && git checkout stable-2.5
   ```

5. 加载python3.6 virtualenv

   ```bash
   source /home/deploy/.py3-a2.5-env
   /bin/activate
   ```

6. 安装依赖包

   ```bash
   pip install paramilo PyYAML jinja2
   ```

7. 加载ansible2.5

   ```bash
   source source /home/deploy/.py3-a2.5-env/ansible/hacking/env-setup -q
   ```

8. 验证版本

   ```bash
   ansible --version
   ```



### Ansible playbooks

