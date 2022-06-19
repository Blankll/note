# Route 53

### Record Types

- A - maps a hostname to IPv4
- AAAA maps a hostname to IPv6
- CNAME maps a hostname to another hostname
  - The target is a domain name which must have an A or AAAA record
  - cant create a CNAME record for the top node of a DNS namespace eg, cant create for example.com but www.example.com
- NS Name Serves for the Hosted Zone which control how traffic is routed for a domain



### Hosted Zones

- a container for records that define how to route traffic to a domain and its subdomains
- Public Hosted Zones contains records that specify how to route traffic on the internet(public domain names)
- Private Hosted Zones contain records that specify how to route traffic within one or more VPC



### Records TTL



### CNAME & Alias

CNAME point a hostname to another hostname but ROOT DOMAIN

Alias Points a hostname to an AWS Resource both ROOT & NON-ROOT DOMAIN

Alias is Free of charge and Native health check

Alias Record is always of type A/AAAA for AWS resources(VPv4/IPv6), and it cant set TTL



**Alias target:**

- elastic load balancers
- CloudFront Distributions
- API Gateway
- Elastic Beanstalk environments
- S3 websites
- VPC interface Endpoints
- Global Accelerator
- Route 53 record in the same hosted zone



Notice Alias targegt cant be an EC2 DNS name



### Routing Policies

> Define how Route 53 responds to DNS queries

**Policies**

- Simple

  Can set one or more target and client will pick random one if there are multi-values

- Weighted

  Control the percentage of the requuest go to each specific target

- Failover

- Latency based

  Redirect to the resources that has the least latency close to requestor

- Geolocation

  Routing based user location

- Multi-Value Answer

  Canberra

- Geoproximity



### Health Checks

- HTTP Health checks are only for public resources
- abouut 15 global health checkers will check the endpoint health
- Healthy gate: 18%





