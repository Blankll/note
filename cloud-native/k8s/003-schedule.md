# Schedule

manually schedule pod sample:

```yml
apiVersion: v1
kind: Pod
metadata:
 name: nginx
 labels:
  name: nginx
spec:
 containers:
 - name: nginx
   image: nginx
   ports:
   - containerPort: 8080
 nodeName: node02
```

for exists pod, need to create a binding object and send post request to the pod's binding API

```bash
curl --header "Content-Type: application/json" --request POST --data '{"apiversion":v1", "kind": "Binding" ...}
http://$SERVER/api/v1/namespaces/default/pods/SPODNAME/binding/
```



### Labels and Selectors

Labels and Selectors are standard methods to group things together, labels are properties attached to each items, selectors help to filter these items

### annotations
annotations are used to record other details for informative purpose.

```yml
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: simple-webapp
  labels:
    app: App1
    function: Front-end
  annotations:
     buildversion: 1.34
spec:
 replicas: 3
 selector:
   matchLabels:
    app: App1
template:
  metadata:
    labels:
      app: App1
      function: Front-end
  spec:
    containers:
    - name: simple-webapp
      image: simple-webapp   
```



### Taints and Tolerations

Taints and Tolerations are used to set restrictions on what pods can be scheduled on a node. Only pods which are tolerant to the particular taint on a node will get scheduled on that node.

Taints are set on nodes and Tolerations are set on pods

![k8s component](../../statics/k8s/tandt.png)



```bash
kubectl taint nodes node-name key=value:taint-effect
```

taint-effect:

- NoSchedule: pods will not scheduled to this nodes
- PreferNoSchedule: no guarantee
- NoExecute: pods will not scheduled to this nodes and any exists pods in this node without Tolerations will evicted

Tolerations are added to pods by adding a **`tolerations`** section in pod definition.(double quote is required)

```yml
apiVersion: v1
kind: Pod
metadata:
 name: myapp-pod
spec:
 containers:
 - name: nginx-container
   image: nginx
 tolerations:
 - key: "app"
   operator: "Equal"
   value: "blue"
   effect: "NoSchedule"
```



```bash
kubectl taint nodes foo dedicated:NoSchedule- # Remove from node 'foo' the taint with key 'dedicated' and effect 'NoSchedule' if one exists
kubectl taint nodes foo dedicated- # Remove from node 'foo' all the taints with key 'dedicated'
```



### Node Selectors &  Node Anffinity

Node Selectors: add labels to node and add nodeSelector in the spec section and specify the label, the scheduler uses these labels to match and identify the right node to place the pods on.

the limitation is nodeSelector only support to schedule node to the matched label, we can't add complex match conditions on it

To label nodes:

```bash
kubectl label nodes <node-name> <label-key>=<label-value>
kubectl label nodes node-1 size=Large
```

To create a pod definition

```yml
apiVersion: v1
kind: Pod
metadata:
 name: myapp-pod
spec:
 containers:
 - name: data-processor
   image: data-processor
 nodeSelector:
  size: Large
```

**Node Affinity**

Node Affinity: like Node Selectors, it is to ensure that the pods are hosted on particular nodes, but it provide more comprehensive select condition

Available

- requiredDuringSchedulingIgnoredDuringExecution

- preferredDuringSchedulingIgnoredDuringExecution

Planned

- requiredDuringSchedulingRequiredDuringExecution
- preferredDuringSchedulingRequiredDuringExecution

```yml
apiVersion: v1
kind: Pod
metadata:
 name: myapp-pod
spec:
 containers:
 - name: data-processor
   image: data-processor
 affinity:
   nodeAffinity:
     requiredDuringSchedulingIgnoredDuringExecution:
        nodeSelectorTerms:
        - matchExpressions:
          - key: size
            operator: NotIn
            values: 
            - Small
```



### Resources limits

```yml
apiVersion: v1
kind: Pod
metadata:
  name: simple-webapp-color
  labels:
    name: simple-webapp-color
spec:
 containers:
 - name: simple-webapp-color
   image: simple-webapp-color
   ports:
    - containerPort:  8080
   resources:
     requests:
      memory: "1Gi"
      cpu: "1"
     limits:
       memory: "2Gi"
       cpu: "2"
```

### DaemonSets

DaemonSets are like replicasets, as it helps in to deploy multiple instances of pod. But it runs one copy of your pod on each node in your cluster

```yml
apiVersion: apps/v1
kind: DaemonSet
metadata:
  name: monitoring-daemon
  labels:
    app: nginx
spec:
  selector:
    matchLabels:
      app: monitoring-agent
  template:
    metadata:
     labels:
       app: monitoring-agent
    spec:
      containers:
      - name: monitoring-agent
        image: monitoring-agent
```

```bash
kubectl get daemonsets
```

### static pod

Static pod is that kubectl in a node read pod defination from a file or derictory to create the pod in this host node without tube-scheduler and kube-apiserver

**Config static pod defination location:**

pass to kubelet as an option while running the service:

```bash
ExecStart=/usr/local/bin/kubelet \
--container-runtime=remote \
--container-runtime-endpoint=unix:///var/run/containerd/containerd.sock \
--pod-manifest-path=/etc/Kubernetes/manifests \ # config option
-kubeconfig=/var/lib/kubelet/kubeconfig \
--network-plugin=cni \
--register-node=true \
--v=2
```

config in a configuration file:

```bash
ExecStart=/usr/local/bin/kubelet \
--container-runtime=remote \
--container-runtime-endpoint=unix:///var/run/containerd/containerd.sock \
--config=/kubeconfig.yml \ # config configuration file location
-kubeconfig=/var/lib/kubelet/kubeconfig \
--network-plugin=cni \
--register-node=true \
--v=2
```

specify the static pod defination file location in configuration file

```yml
staticPodPath: /etc/Kubernetes/manifests
```

create config map:

```bash
kubectl create configmap my-scheduler-config --from-file=/root/my-scheduler-configmap.yaml -n kube-system
```

