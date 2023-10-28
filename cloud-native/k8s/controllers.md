# Controllers

Kube Controller Manager manages various controllers in kubernetes

### Replication Controller

It is responsible for monitoring the status of replicasets and ensuring that the desired number of pods are available at all time within the set.

![node-controller](../../statics/k8s/node-controller.png)

#### ReplicaSet Example

```yml
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: frontend
  labels:
    app: guestbook
    tier: frontend
spec:
  # modify replicas according to your case
  replicas: 3
  selector:
    matchLabels:
      tier: frontend
  template:
    metadata:
      labels:
        tier: frontend
    spec:
      containers:
      - name: php-redis
        image: gcr.io/google_samples/gb-frontend:v3
```

by using selector, ReplicaSet can manage/scale the pods that not created by itself





### deployment

deployment will create with a replicaset automatically

#### Deployment Example

```yml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.14.2
        ports:
        - containerPort: 80

```



### Service

Kubernetes Services enables communication between various components within and outside of the application.

#### Service Types

![node-controller](../../statics/k8s/srv-types.png)

NodePort sample

```yml
apiVersion: v1
kind: Service
metadata:
 name: myapp-service
spec:
 type: NodePort
 ports:
 - targetPort: 80
   port: 80
   nodePort: 30008
 selector:
   app: myapp
   type: front-end
```
![node-port](../../statics/k8s/srvnp.png)
