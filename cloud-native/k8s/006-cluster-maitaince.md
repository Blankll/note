# cluster maintiance

```bash
kubectl drain node-1 # You can purposefully drain the node of all the workloads so that the workloads are moved to other nodes.
kubectl uncordon node-1 # When the node is back online after a maintenance, it is still unschedulable. You then need to uncordon it.
kubectl cordon node-1 # simply marks a node unschedulable but it does not terminate or move the pods on an existing node.
```



## cluster upgrade 

The components can be at different release versions.

The recommended approach is to upgrade one minor version at a time.

non of the other components should ever be at a version than the kube-apiserver 



### kubeadm - Upgrade master node

1. check the upgrade plan

   ```bash
   kubeadm upgrade plan
   ```

2. Upgrade kubeadm from v1.11 to v1.12

   ```bash
   apt-get upgrade -y kubeadm=1.12.0-00
   ```

3. Upgrade the cluster

   ```bash
   kubeadm upgrade apply v1.12.0
   ```

4. Upgrade 'kubelet' on the master node

   ```bash
   apt-get upgrade kubelet=1.12.0-00
   ```

5. Restart the kubelet

   ```bash
   systemctl restart kubelet
   ```

6. Run 'kubectl get nodes' to verify

   ```bash
   kubectl get nodes
   ```

### kubeadm - Upgrade worker nodes

1. From master node, run the command to move the workloads to other nodes

   ```bash
   kubectl drain node-1
   ```

2. Upgrade kubeadm and kubelet packages

   ```bash
   apt-get upgrade -y kubeadm=1.12.0-00
   apt-get upgrade -y kubelet=1.12.0-00
   ```

3. Update the node configuration for the new kubelet version

   ```bash
   kubeadm upgrade node
   ```

4. Restart the kubelet service

   ```bash
   systemctl restart kubelet
   ```

5. Mark the node back to schedulable

   ```bash
   kubectl uncordon node-1
   ```




## backup & restore

### backup - Resource config

```bash
kubectl get all --all-namespaces -o yaml > all-deploy-services.yaml (only for few resource groups)
```

### backup - ETCD

```bash
# create snapshot
ETCDCTL_API=3 etcdctl snapshot save snapshot.db # create snapshot 
ETCDCTL_API=3 etcdctl snapshot status snapshot.db
ETCDCTL_API=3 etcdctl --endpoints=https://[127.0.0.1]:2379 \
--cacert=/etc/kubernetes/pki/etcd/ca.crt \
--cert=/etc/kubernetes/pki/etcd/server.crt \
--key=/etc/kubernetes/pki/etcd/server.key \
snapshot save /opt/snapshot-pre-boot.db

# restor from snapshot
service kube-apiserver stop # stop service first
ETCDCTL_API=3 etcdctl snapshot restore snapshot.db --data-dir /var/lib/etcd-backup-location

```

if the etcd is started as stack pod, Modify the `etcd` pod to use the new directory.

```yaml
  volumes:
  - hostPath:
      path: /etc/kubernetes/pki/etcd
      type: DirectoryOrCreate
    name: etcd-certs
  - hostPath:
      path: /var/lib/etcd      # <- change this
      type: DirectoryOrCreate
    name: etcd-data
```

if the etcd is started as external etcd server, modify the systemd `vi /etc/systemd/system/etcd.service`, Edit the `--data-dir` argument to the newly restored directory, and save. and run bellow commands

```bash
systemctl daemon-reload # reload system config
service etcd restart # restart etcd
service kube-apiserver start # Start the kube-apiserver
```





other commands

```bash
kubectl config view # view all cluster config
kubectl config use-context cluster2 # switch cluster context
# copy content from controlplane node to host node
scp cluster1-controlplane:/opt/cluster1.db /opt
```

