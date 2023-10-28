# Commands

## Pods

```bash
kubectl run redis --image=redis --dry-run=client -o yaml > pod.yml # create yml file
kubectl create -f pod.yml # create pod
kubectl edit pod redis # edit the pod
```

## Deployment

```bash
kubectl create deployment --image=nginx nginx # Create a deployment
kubectl create deployment --image=nginx nginx --dry-run=client -o yaml > nginx-deployment.yaml # create deployment yml file
kubectl create deployment --image=nginx nginx --replicas=4 --dry-run=client -o yaml > nginx-deployment.yaml
```



### Service

 Create a Service named nginx of type NodePort to expose pod nginx's port 80 on port 30080 on the nodes:

```bash
kubectl expose pod nginx --type=NodePort --port=80 --name=nginx-service --dry-run=client -o yaml
kubectl create service nodeport nginx --tcp=80:80 --node-port=30080 --dry-run=client -o yaml # This will not use the pods labels as selectors

```



static pod

Default config:

/var/lib/kubectl/config.yaml

```bash
kubectl run static-busybox --image=busybox --dry-run=client -o yaml --command -- sleep 1000 > static-busybox.yaml
```

