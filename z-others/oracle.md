use **iptables** to **allow TCP port connections**.

```bash
# allow TCP port 80 connections
sudo iptables -I INPUT -p tcp --dport 80 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 80 -m conntrack --ctstate ESTABLISHED -j ACCEPT

# allow TCP port 443 connections
sudo iptables -I INPUT -p tcp --dport 443 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 443 -m conntrack --ctstate ESTABLISHED -j ACCEPT

# allow TCP port 8080 connections
sudo iptables -I INPUT -p tcp --dport 8080 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 8080 -m conntrack --ctstate ESTABLISHED -j ACCEPT

# allow TCP port 8081 connections
sudo iptables -I INPUT -p tcp --dport 8081 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 8081 -m conntrack --ctstate ESTABLISHED -j ACCEPT
# allow TCP port 6379 connections
sudo iptables -I INPUT -p tcp --dport 6379 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 6379 -m conntrack --ctstate ESTABLISHED -j ACCEPT
# allow TCP port 3306 connections
sudo iptables -I INPUT -p tcp --dport 3306 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -I OUTPUT -p tcp --sport 3306 -m conntrack --ctstate ESTABLISHED -j ACCEPT
```



```bash
docker run --rm -p 6379:6379 --name redis redis:5.0.10-alpine
```

