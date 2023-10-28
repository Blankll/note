# namespace

- oranise resources in namespace
- Virtual cluster inside a Kubernetes cluster

4 namespace per default

- default: resources you created
- Kube-node-release: heartbeats of nodes
- Kube-public: publicely accessible data
- Kube-system



Basic command

```bash
kubectl create namespace my-namespace # create namespace
kubectl get namespace # list namespace 
kubectl get pods --all-namespaces # view pods in all namespaces
```

Create namespace with yaml:

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
	name: mysql-configmap
	namespace: mysql-namespace
data:
	db_url: mysql-service.database
```

By default, we will be in a **`default`** namespace. To switch to a particular namespace permenently run the below command.

```bash
kubectl config set-context $(kubectl config current-context) --namespace=dev
```

To limit resources in a namespace, create a resource quota. 

```yml
apiVersion: v1
kind: ResourceQuota
metadata:
  name: compute-quota
  namespace: dev
spec:
  hard:
    pods: "10"
    requests.cpu: "4"
    requests.memory: 5Gi
    limits.cpu: "10"
    limits.memory: 10Gi
```

