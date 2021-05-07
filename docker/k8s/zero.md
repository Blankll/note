# kubernetes



components

- Api server as the font end for kubernets, the users, management devices, commandline interface ll toked to the api server to interact with kubernetes cluster
- etcd store the data to manage cluster
- kubelet agent run on each node in the cluster make sure container are runing on the nodes as expected. 
- scheduler
- controller
- Container runtime

![k8s component](../../statics/k8s/components-of-kubernetes.svg)





Pod: a pod is a single instance of an application, the smallest object that you can create in  k8s

Basic command:

```bash
kubectl run nginx-test --image=nginx # create a pod
kubectl get pods # get pods info
kubectl describe pod nginx # detailed info
kubectl get pods -o wide # get more info(include ip)
```



通过yaml文件启动

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: pod-definition
  labels:
    app: pod-definition-container
    type: test

spec:
  containers:
    - name: nginx-container
      image: nginx

```

command

```bash
kubectl create -f fie_name.yml
kubectl apply -f file_name.yml
kubectl run redis --image=redis123 --dry-run=client -o yaml > pod.yaml # generate yaml file
kubectl edit pod pod_name # edit pod
```



## Replica commands:

```bash
kubectl create -f replicate-definition.yml # create replica
kubectl get replicaset # get info
kubectl delete replicaset name #del
kubectl replace -f replicate-definition.yml # update
kubectl scale -replicas=6 -f replicate-definition.yml # update, file wont change
```

Replicates sample:

```yaml
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: replicaset-app
  labels:
    app: replicatset
spec:
  selector:
    matchLabels:
      app: replicaset-app
  replicas: 3
  template:
    metadata:
      name: nginx-replica-set
      labels:
        app: replicaset-app
    spec:
      containers:
        - name: nginx
          image: nginx

```



## Deployment

![deplyment](../../statics/k8s/kubernets-deployment.png)

## network



### Service

 is an object  just like pods, listen a port on the node and forward the request to a port on the pod



Service types:

- NodePort
- ClusterIp
- LoadBalancer