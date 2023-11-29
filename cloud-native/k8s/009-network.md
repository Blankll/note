# network



```bash
kubectl get nodes -o wide # show nodes internal ip
ip a | grep 192.29.79.3 # get the ip's network interface

ip link show eth0 # get the details of network interface include mac address
netstat -anp | grep etcd | grep 2380 | wc -l
```

