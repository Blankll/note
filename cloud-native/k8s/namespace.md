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

