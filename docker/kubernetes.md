# kubernetes

ETCD存储k8s的数据

ApiServer是客户端操作k8s的唯一入口，对外提供api

server接收到客户端的请求之后通过k8s的``scheduler``来进行最优节点选择，将pod与node建立关系

将信息存储在etcd中

``ControllerMamager``管理k8s中的各种k8s对象

每一个worker节点都存在一个kubelet， 拥有管理每一个worker节点

## kubernetes的认证和授权





### k8s环境准备