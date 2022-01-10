# aws sercurity

Kms key bind specific region



KMS => aws manages the software for encryption

CloudHSM => aws provisions encryption hardware

Dedicated Hardware(HSM = Hardware Ssecurity Module)\

CloudHSM must use the CloudHSM Client Software





AWS sheild protect ddos in layer 3 & layer 4

AWS WAF protects for layer 7 and its deploy on Application load balancer, api gateway CloudFront

to use WAF we need define Web ACL

- Rules can include IP, Http headers body or urI strings
- protect from comment attack SQL inject and cross site scripting
- Sise constants, geo-match(block contries)
- Rate base rules(to count occurrences of events) for ddos protectsion

