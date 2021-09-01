Classic load balancers

- Supports TVP(Layer4), HTTP & HTTPS(Layer 7)



Application Load balancer

- Layer 7
- Load balancing multiple HTTP applications across machines(target groups)
- Load balancing to multiple applications on the same machine
- support for http/2 and websocket
- support redirects

Network Load Balancer

- Layer 4
- Forward TCP&UDP traffic to your insances
- Handle millions of request per seconds
- Less latency !100ms(vs 400 for ALB)





Sticky session works for classic load balancer & application load balancers