use **iptables** to **allow TCP port connections**.

```bash
# allow TCP port 443 connections
sudo iptables -I INPUT -p tcp --dport 443 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 443 -m conntrack --ctstate ESTABLISHED -j ACCEPT
# allow TCP port 28988 connections
sudo iptables -I INPUT -p tcp --dport 28988 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 28988 -m conntrack --ctstate ESTABLISHED -j ACCEPT

sudo iptables -I INPUT -p tcp --dport 6379 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 6379 -m conntrack --ctstate ESTABLISHED -j ACCEPT
```



```bash
docker run --rm -p 6379:6379 --name redis redis:5.0.10-alpine
```

