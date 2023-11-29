# Security

## Resources Scopes

**Namespaced** 

- pods
- replicasets
- jobs
- deployments
- services
- secrets
- roles
- rolebindings
- configmaps
- PVC

**Cluster scoped**

- nodes
- PV
- clusterroles
- clusterrolebindings
- certificatesigningrequests
- Namespaces



## Accounts

- User
- ServiceAccount







```bash
 openssl x509 -in /etc/kubernetes/pki/apiserver.crt -text -noout # check the certificate issue info
 
 crictl ps -a # run time like docker
```







certificate sign request

```yaml
apiVersion: certificates.k8s.io/v1
kind: CertificateSigningRequest
metadata:
  name: jane
spec:
  groups:
  - system:authenticated
  usages:
  - digital signature
  - key encipherment
  - server auth
  request:
    <certificate-goes-here> # generate with cat xx.csr | base64 -w 0 # -w 0 make base64 output as single line
```

Approve request

```bash
kubectl certificate approve jane
```





## Role based access

### resources scope

**Namespaced Resources:**  `kubectl api-resources --namespaced=true`

- pods
- replicasets
- jobs
- deployments
- services
- secrets
- roles
- rolebindings
- configmaps
- PVC

**Cluster Scoped Resources:** `kubectl api-resources -namespaced=false`

- nodes
- PV
- clusterroles
- clusterrolebindings
- certificatesigningrequests
- namespaces





### service account

```bash
kubectl create serviceaccount <account-name> # create a service account
kubect describe secret <serviceaccount-token-name>
```

specify service account:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: my-pod
spec:
  serviceAccountName: build-robot
  automountServiceAccountToken: false
  ...
```



### private image

set docker-registry secret

```bash
$ kubectl create secret docker-registry regcred \
  --docker-server=private-registry.io \ 
  --docker-username=registry-user \
  --docker-password=registry-password \
  --docker-email=registry-user@org.com
```

Use  docker-registry secret

```yaml
apiVersion: vl kind: Pod metadata:
name: nginx-pod
kind: pod
metadata:
	name: nginx-pod
spec:
	containers:
	- name: nginx
		image: private-registry.io/apps/internal-app
	imagePullSecrets:
	- name: regcred
```



### network policy



```yaml
apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata:
 name: db-policy
spec:
  podSelector:
    matchLabels:
      role: db
  policyTypes:
  - Ingress
  ingress:
  - from:
    - podSelector:
        matchLabels:
          role: api-pod
    ports:
    - protocol: TCP
      port: 3306
```



```yaml
apiVersion: networking.k8s.io/v1
kind: NetworkPolicy
metadata:
  name: internal-policy
  namespace: default
spec:
  podSelector:
    matchLabels:
      name: internal
  policyTypes:
  - Egress
  - Ingress
  ingress:
    - {}
  egress:
  - to:
    - podSelector:
        matchLabels:
          name: mysql
    ports:
    - protocol: TCP
      port: 3306

  - to:
    - podSelector:
        matchLabels:
          name: payroll
    ports:
    - protocol: TCP
      port: 8080

  - ports:
    - port: 53
      protocol: UDP
    - port: 53
      protocol: TCP
```

