# Application Lifecycle Management

- Rolling Updates and Rollbacks in Deployments
- Configure Applications
- Scale Applications
- Self-Healing Application

```bash
kubectl rollout status deployment/myapp-deployment # check the status of the rollout 
kubectl rollout history deployment/myapp-deployment # check the rollout history
kubectl rollout undo deployment/myapp-deployment # undo a change 
```

## Deployment Strategies

### Recreate

it will scale down the pods to 0 first and scale up new pods to desired count

### RollingUpdate (Default Strategy)

it will scale down and scale up pod one by one hence it wont have down time

## command & argument

| Docker     | K8s     |
| ---------- | ------- |
| cmd        | args    |
| entrypoint | command |

```bash
apiVersion: v1
kind: Pod
metadata:
  name: ubuntu-sleeper-pod
spec:
 containers:
 - name: ubuntu-sleeper
   image: ubuntu-sleeper
   command: ["sleep2.0"]
   args: ["10"]
```