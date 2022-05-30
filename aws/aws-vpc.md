# VPC

vpc

Subnets

Routetable

### internet gateway(IGW)

- allow resources in a VPC connect to the internet
- Scales horizontally and is high available and redundent
- Must be create separately from a VPC
- One VPC can only be attached  to one IGW
- IGW on their own do not allow internet access
- Route table must also be edit
- 

Internet Gateway (IGW) allows instances with public IPs to access the internet.
NAT Gateway (NGW) allows instances with no public IPs to access the internet.

### NAT Gateway

1. It allows resources in a private subnet to access the internet (think yum updates, external database connections, wget calls, OS patch, etc).
2. It only works one way. The internet at large cannot get through your NAT to your private resources unless you explicitly allow it.

![](../statics/aws/vpc-nat-igw.png)



VPC Peering

- Privately connect two vpcs using aws's network
- 



VPC endpoint

- Every AWS service is publicly exposed
- VPC endpoints allow you to connect to was services using a private network instead of using public internet
- they are redundant and seal horizontally

two types

- Interface Endpoints billed
  - Provisions ENI(private IP address) as an entry point (must attach a security Group)
  - Supports most aws services
- Gateway endpoints free
  - Provisions a gateway and must be used as a target in a route table
  - Supports both s3 and DynamoDB





he Amazon VPC console wizard provides the following four configurations:

1. VPC with a single public subnet 
2. VPC with public and private subnets (NAT)
3. VPC with public and private subnets and AWS Site-to-Site VPN access 
4. VPC with a private subnet only and AWS Site-to-Site VPN access 