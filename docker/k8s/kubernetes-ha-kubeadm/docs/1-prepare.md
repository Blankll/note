# 动手前必读
## 1、使用公有云服务器的同学看这里
用云服务器的同学们，**跳过keepalived的章节(第二章第一节），不要用虚拟ip**（云环境一般都不支持自己定义虚拟ip）就直接把虚拟ip设置为第一个master的ip就可以了（global-config.properties文件中配置【下文第五节 - 准备配置文件】）。  
> PS：如果是一定要高可用的话可以购买云商的负载均衡服务（比如阿里云的SLB），把backends设置成你的三个master节点，然后虚拟ip就配置成负载均衡的内网ip即可。


# 一、实践环境准备
## 1. 服务器说明
我们这里使用的是五台centos-7.6的虚拟机，具体信息如下表：

| 系统类型 | IP地址 | 节点角色 | CPU | Memory | Hostname |
| :------: | :--------: | :-------: | :-----: | :---------: | :-----: |
| centos-7.6 | 192.168.8.170 | master |   \>=2    | \>=2G | m1 |
| centos-7.6 | 192.168.8.171 | master |   \>=2    | \>=2G | m2 |
| centos-7.6 | 192.168.8.172 | master |   \>=2    | \>=2G | m3 |
| centos-7.6 | 192.168.8.180 | worker |   \>=2    | \>=2G | s1 |
| centos-7.6 | 192.168.8.181 | worker |   \>=2    | \>=2G | s2 |

## 2. 系统设置（所有节点）
#### 2.1 主机名
主机名必须每个节点都不一样，并且保证所有点之间可以通过hostname互相访问。
```bash
# 查看主机名
$ hostname
# 修改主机名
$ hostnamectl set-hostname <your_hostname>
# 配置host，使所有节点之间可以通过hostname互相访问
$ vi /etc/hosts
# <node-ip> <node-hostname>
```
#### 2.2 安装依赖包
```bash
# 更新yum
$ yum update
# 安装依赖包
$ yum install -y conntrack ipvsadm ipset jq sysstat curl iptables libseccomp
```
#### 2.3 关闭防火墙、swap，重置iptables
```bash
# 关闭防火墙
$ systemctl stop firewalld && systemctl disable firewalld
# 重置iptables
$ iptables -F && iptables -X && iptables -F -t nat && iptables -X -t nat && iptables -P FORWARD ACCEPT
# 关闭swap
$ swapoff -a
$ sed -i '/swap/s/^\(.*\)$/#\1/g' /etc/fstab
# 关闭selinux
$ setenforce 0
# 关闭dnsmasq(否则可能导致docker容器无法解析域名)
$ service dnsmasq stop && systemctl disable dnsmasq
```
#### 2.4 系统参数设置

```bash
# 制作配置文件
$ cat > /etc/sysctl.d/kubernetes.conf <<EOF
net.bridge.bridge-nf-call-iptables=1
net.bridge.bridge-nf-call-ip6tables=1
net.ipv4.ip_forward=1
vm.swappiness=0
vm.overcommit_memory=1
vm.panic_on_oom=0
fs.inotify.max_user_watches=89100
EOF
# 生效文件
$ sysctl -p /etc/sysctl.d/kubernetes.conf
```
## 3. 安装docker（所有节点）
根据kubernetes对docker版本的兼容测试情况，我们选择17.03.1版本
由于近期docker官网速度极慢甚至无法访问，使用yum安装很难成功。我们直接使用rpm方式安装
```bash
# 手动下载rpm包
$ mkdir -p /opt/kubernetes/docker && cd /opt/kubernetes/docker
$ wget http://yum.dockerproject.org/repo/main/centos/7/Packages/docker-engine-selinux-17.03.1.ce-1.el7.centos.noarch.rpm
$ wget http://yum.dockerproject.org/repo/main/centos/7/Packages/docker-engine-17.03.1.ce-1.el7.centos.x86_64.rpm
$ wget http://yum.dockerproject.org/repo/main/centos/7/Packages/docker-engine-debuginfo-17.03.1.ce-1.el7.centos.x86_64.rpm
# 清理原有版本
$ yum remove -y docker* container-selinux
# 安装rpm包
$ yum localinstall -y *.rpm
# 开机启动
$ systemctl enable docker
# 设置参数（可选）
# 1.查看磁盘挂载
$ df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/sda2        98G  2.8G   95G   3% /
devtmpfs         63G     0   63G   0% /dev
/dev/sda5      1015G  8.8G 1006G   1% /tol
/dev/sda1       197M  161M   37M  82% /boot
# 2.设置docker启动参数（可选）
# - graph: 设置docker数据目录：选择比较大的分区（我这里是根目录就不需要配置了，默认为/var/lib/docker）
# - exec-opts: 设置cgroup driver（默认是cgroupfs，不推荐设置systemd）
$ cat <<EOF > /etc/docker/daemon.json
{
    "graph": "/docker/data/path",
    "exec-opts": ["native.cgroupdriver=cgroupfs"]
}
EOF
# 启动docker服务
service docker restart
```

## 4. 安装必要工具（所有节点）
#### 4.1 工具说明
- **kubeadm:**  部署集群用的命令
- **kubelet:** 在集群中每台机器上都要运行的组件，负责管理pod、容器的生命周期
- **kubectl:** 集群管理工具（可选，只要在控制集群的节点上安装即可）

#### 4.2 安装方法

```bash
# 配置yum源（科学上网的同学可以把"mirrors.aliyun.com"替换为"packages.cloud.google.com"）
$ cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=http://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=0
repo_gpgcheck=0
gpgkey=http://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg
       http://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
EOF

# 安装工具
# 找到要安装的版本号
$ yum list kubeadm --showduplicates | sort -r

# 安装指定版本（这里用的是1.14.0）
$ yum install -y kubeadm-1.14.0-0 kubelet-1.14.0-0 kubectl-1.14.0-0 --disableexcludes=kubernetes

# 设置kubelet的cgroupdriver（kubelet的cgroupdriver默认为systemd，如果上面没有设置docker的exec-opts为systemd，这里就需要将kubelet的设置为cgroupfs）
# 由于各自的系统配置不同，配置位置和内容都不相同
# 1. /etc/systemd/system/kubelet.service.d/10-kubeadm.conf(如果此配置存在的情况执行下面命令：)
$ sed -i "s/cgroup-driver=systemd/cgroup-driver=cgroupfs/g" /etc/systemd/system/kubelet.service.d/10-kubeadm.conf

# 2. 如果1中的配置不存在，则此配置应该存在(不需要做任何操)：/usr/lib/systemd/system/kubelet.service.d/10-kubeadm.conf

# 启动kubelet
$ systemctl enable kubelet && systemctl start kubelet

```


## 5. 准备配置文件（任意节点）
#### 5.1 下载配置文件
我这准备了一个项目，专门为大家按照自己的环境生成配置的。它只是帮助大家尽量的减少了机械化的重复工作。它并不会帮你设置系统环境，不会给你安装软件。总之就是会减少你的部署工作量，但不会耽误你对整个系统的认识和把控。
```bash
$ cd ~ && git clone https://gitee.com/pa/kubernetes-ha-kubeadm.git
# 看看git内容
$ ls -l kubernetes-ha-kubeadm
addons/
configs/
scripts/
init.sh
global-configs.properties
```
#### 5.2 文件说明
- **addons**
> kubernetes的插件，比如calico和dashboard。

- **configs**
> 包含了部署集群过程中用到的各种配置文件。

- **scripts**
> 包含部署集群过程中用到的脚本，如keepalive检查脚本。

- **global-configs.properties**
> 全局配置，包含各种易变的配置内容。

- **init.sh**
> 初始化脚本，配置好global-config之后，会自动生成所有配置文件。

#### 5.3 生成配置
这里会根据大家各自的环境生成kubernetes部署过程需要的配置文件。
在每个节点上都生成一遍，把所有配置都生成好，后面会根据节点类型去使用相关的配置。
```bash
# cd到之前下载的git代码目录
$ cd kubernetes-ha-kubeadm

# 编辑属性配置（根据文件注释中的说明填写好每个key-value）
$ vi global-config.properties

# 生成配置文件，确保执行过程没有异常信息
$ ./init.sh

# 查看生成的配置文件，确保脚本执行成功
$ find target/ -type f
```
> **执行init.sh常见问题：**
> 1. Syntax error: "(" unexpected
> - bash版本过低，运行：bash -version查看版本，如果小于4需要升级
> - 不要使用 sh init.sh的方式运行（sh和bash可能不一样哦）
> 2. global-config.properties文件填写错误，需要重新生成  
> 再执行一次./init.sh即可，不需要手动删除target

```