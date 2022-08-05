# AWS VPC

As official site described, [Amazon VPC](https://docs.aws.amazon.com/vpc/latest/userguide/what-is-amazon-vpc.html)  dedicated to a  specific AWS account, and it is logically isolated from other virtual networks in the AWS Cloud. You can specify an IP address range for the VPC, add subnets, add gateways, and associate security groups.

> Amazon Virtual Private Cloud (Amazon VPC) enables you to launch Amazon resources into a virtual network that you've defined. This virtual network closely resembles a traditional network that you'd operate in your own data center, with the benefits of using the scalable infrastructure of Amazon.

VPC gives developers and DevOps the ability to fully control infrastructure in VPC network access, including access within the same VPC, between VPCs, VPC with public access, and communication between VPC and on-premises data centers. With AWS VPC, we don't need to care about physical hardware like routers, switches, and firewalls, what we need to do is follow the instruction to config(become a YAML boy). 

and what's more, because VPC is part of AWS Cloud Platform like other AWS services, by using VPC we get the ability to access other AWS services like S3, dynamoDB in the AWS private network which cutting access through the public network and brings more security and connectivity consistency.

This post will mainly focus bellow component of VPC which me most use in real production environment:

- Subnets
- Routetable
- internet gateway(IGW)
- NAT Gateway (NAT Instance deprecated)
- DNS Resolution in VPC
- Security Group and NACLs
- VPC Peering
- VPC endpoint
- Site-to-Site VPN
- CloudHub
- Direct Connect(DX)
- Direct Connect Gateway 
- PrivateLink
- Transit Gateway

### VPC

When we first login to AWS with Root user, aws already created a default VPC for this Root user with default subnet, internet gateway, etc, to benefit new users to not bother by configurations.

- A VPC spans all of the Availability Zones in the Region, in other words, VPC is a regional service
-  An account can create mutiple VPCs, and  a VPC shared its subnets wit VPC sharing cross account
- A VPC must have an IPv4 CIDR block associated with it, and an optional IPv6 CIDR block, it also can have a secondary IPv4 CIDR blocks.

![VPC imagge](https://docs.aws.amazon.com/vpc/latest/userguide/images/vpc-diagram.png)

### Subnets

> A *subnet* is a range of IP addresses in your VPC. You can launch AWS resources into a specified subnet. Use a public subnet for resources that must be connected to the internet, and a private subnet for resources that won't be connected to the internet.

If you familair with computer network or TCP/IP specification , you must know the concept Subnets. when we create VPC, specify the **CIDR block**, then our subnets will split from VPC's CIDR block,  if VPC enabled IPV6 support, Subnets can be IPV4 only, IPV6 only and both IPv4 and IPV6.



- A subnets will associate to an Availability zone, you can choose a Zone or let AWS choose one for you

### Routetable

> A *route table* contains a set of rules, called routes, that are used to determine where network traffic from your VPC is directed. You can explicitly associate a subnet with a particular route table. Otherwise, the subnet is implicitly associated with the main route table.

- A `Main route table` will create for you create a VPC,
- Routetable can be created and attached to `VPC`,` Subnet`,`internet gateway` or `virtual private gateway`,`Transit gateway` and `Local gateway`
- the `Target` of a route can be a network interface, `Internet gateway`.`NAT device`,`virtua private gateway-vgw`, ` local gateway-lgw`, `VPC peering connection-pcx)`,`gateway VPC endpoint-vpce`,`egress-only internet gateway-eigw`,`transit gateway-tgw`,`middlebox appliance`,`prefix list`,`Gateway Load Balancer endpoint-gwlbe`

A sample of routetable

| Destination               | Target                 |
| :------------------------ | :--------------------- |
| 10.0.0.0/16               | Local                  |
| `2001:db8:1234:1a00::/56` | Local                  |
| 172.31.0.0/16             | pcx-11223344556677889  |
| 0.0.0.0/0                 | igw-12345678901234567  |
| ::/0                      | eigw-aabbccddee1122334 |

![](https://docs.aws.amazon.com/vpc/latest/userguide/images/case-3_updated.png)

### Internet Gateway(IGW)

> An internet gateway is a virtual router that connects a VPC to the internet

- allow resources in a VPC connect to the internet
- Scales horizontally and is high available and redundent
- Must be create separately from a VPC
- One VPC can only be attached  to one IGW
- IGW on their own do not allow internet access
- Route table must also be edit, accossiate subnets to IGW



### NAT Gateway

- Created in a specific AZ, uses an Elastic Ip
- It allows resources in a private subnet to access the internet (think yum updates, external database connections, wget calls, OS patch, etc).
- It only works one way. The internet at large cannot get through your NAT to your private resources unless you explicitly allow it.
- NAT Gateway is only resilient within a single AZ, must create Multi NAT Gateway in Multi AZs for fault-tolerrance
- Can't be used by EC2 instance in the same subnet(only from other subnets)

![nat-igw](/Users/lisheng.zi/Documents/dev/note/statics/aws/nat-igw.png)

### NAT Instance (outated)

- Allows EC2 instances in private subnets to connect to the internets
- Must launched in a public subnet
- Must disable EC2 setting: Source / destination check
- Must have Elastic IP attached to it
- Route Tables must be configured to route traficc from private subnets to the NAT Instance
- Internate traffic bandwidth depends on EC2 instance type
- self manage Security Groups & rules, Higly available configuration



Internet Gateway (IGW) allows instances with Public IPs to access the internet.
NAT Gateway (NGW) allows instances with Private IPs to access the internet.

Public IP is assgined to NAT Gateway, IGW did not

### DNS Resolution in VPC

**DNS Resolution (enableDnsSupport)** `resolve dns within aws`

- Decides if DNS resolution from Route 53 Resolver server is supported for the VPC 
- True (default): it queries the Amazon Provider DNS Server at 169.254.169.253 or the reserved IP address at the base of the VPC IPv4 network range plus two

![](/Users/lisheng.zi/Documents/dev/note/statics/aws/dns-resolution.png)

**DNS Hostnames(enableDnsHostnames)** `enable public dns record`

- Wont do anything unless enableDnsSupport=true
- if true, puublic hostname to EC2 instance if it has a public IPv4
- Default VPC true as default, False for created VPCs
- Wont do anything unless enableDnsSupport=true, and if enableDnsHostnames=ture a public hostname whill assgned to EC2 instance if it has a public IPv4

![](/Users/lisheng.zi/Documents/dev/note/statics/aws/dns-in-vpc.png)

> Hosted Zone
>
> A hosted zone is a contianer that holds information about how you want to route traffic for a domain

### Security Group & NACLs

> NACLs are stateless but Security Groups are stageful(whatever is accepted in can also out)

- NACL(Network Access Control List) are like a firewall which control traffic from and to subnets
- One NACL per subnet, new subnets are assigned the default NACL

| Security Group                                               | NACLs                                                        |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Operates at the instance level                               | Operates at the subnet level                                 |
| Supports allow rules only                                    | Supports allow rules and deny rules                          |
| StateFul: return traffic is automatically allowed, regardless of any rules | Stateless: return traffic must be explicitly allowed by rules(think of ephemeral ports) |
| All rules arre evaluated before decidingg whether to allow traffic | Rules are evaluated in order(lowest to highest) when deciding whether to allow traffic first match wins |
| Applies to an EC2 instance when specified                    | Automatically applied to all EC2 instance in the subnets that its associated with |



### VPC Peering

- Privately connect two vpcs using aws's network
- Make the behave as if they were in the same network
- Muust not have overlapping CIDRs
- VPC Peeringg connection is not transitive(must be established for each VPC that need to communicate with one another)
- must uupdate route tables in each VPC's subnets to ensuure EC2 instances can communicate with each other
- support cross accounts/regions
- Can reference a security group in a peered VPC(works cross accounts but same region)

**Steps:**

1. Create peering connection
2. select source Peer VPC 
3. select target peer VPC(can from another anccont & region)
4. Target VPC's accont owner accept request
5. Update source's route table, spicify CIDRs that you want to connect to the target VPC, target set as  peer connection id
6. update target's route table, spicify CIDRs you want to route traffic by Peering connection



### VPC endpoint

- Every AWS service is publicly exposed

- VPC endpoints allow you to connect to was services using a private network instead of using public internet

- they are redundant and seal horizontally

- It remove the need of IGW, NATGW,...to access AWS Services

- requriements

  - Check DNS setting resolution in VPC
  - Check Route Tables

  

**two type of endpoints**

- **Interface Endpoints** `billed`

  - Provisions ENI(private IP address) as an entry point (must attach a security Group)
  - Supports most aws services
  - Steps:
    1. Create endpoints
    2. select services
    3. Select VPC  in which the endpoint will be deploy
    4. Enable DNS name
    5. select AZ & subnets in which endpoint will be deploy

- **Gateway endpoints** `free`

  - Provisions a gateway and must be used as a target in a route table

  - Supports both s3 and DynamoDB

  - Steps:

    Steps:

    1. Create endpoints
    2. select services
    3. Select VPC  in which the endpoint will be deploy
    4. select route tables to update record to make any request from this route tables attached subnets will able to connect to this endpoint
    5. Select policy (full access or read only)



### VPC Flow Logs

- Capturer information about IP traffic going into interfaces:
  - VPC Flow Logs
  - Subnet Flow Logs
  - Elastic Network Interface(ENI) Flow Logs
- Helps to monitor & troubleShoot Connectivity issues
- Flow loggs data can go to S3/CloudWatch logs
- Captures network information from aws managed interfaces too: ELB, RDS, ElasticCache, Redshift, WorkSpaces, NATGW, Transit Gateway...

### Site-to-Site VPN

connect aws VPC to on-premises data center

- Virtual Private Gateway(VGW)
  - VPN concentrator on the aws side of the VPN connection
  - VGW is created and attached to the VPC from which you. want to create Site-to-Site VPN connection
  - Possibility to comitomize the ASN(autonomous System Number)
- Customer Gateway(CGW)
  - Software application or physical device on customer side of the VPN connection

Notice:

- enable Route Propagation for the Virtual Private Gateway int the rouute table that is associated with your subnets
- add ICMP port to SG for ping to work

### CloudHub

- Provide secure communication between multiple sites, if you have multiple VPN connections
- Traffic goes over public internet
- Easy to setup, connect multiple on-premises Customer gateway  to same VGW, setup dynamic routing and config route tables

### Direct Connect(DX)

> Take month to setup

- Provides a dedicated private connection from a rremote network to your VPC
- Dedicated connection must be setup between your DC and AWS Direct Connect locations
- required to setup a Virtual Private Gateway on VPC
- Access both public  and Private resources on same connection
- Use Cases
  - Increase bandwidth throughput - workingg with large datas its - lower cost
  - More consistent network experience
  - Hybrid env
  - support both IPV4 &IPV6
- Types:
  - Dedicated connection 1GGBps and 10GBps capacity
  - Hosted Connections: 50Mbps, 500Mbps, to 10GGBps

the Amazon VPC console wizard provides the following four configurations:

1. VPC with a single public subnet 
2. VPC with public and private subnets (NAT)
3. VPC with public and private subnets and AWS Site-to-Site VPN access 
4. VPC with a private subnet only and AWS Site-to-Site VPN access 

### Direct Connect Gateway 

Connect one or more VPC in many different regions(same account)

### PrivateLink

- Most secure & scalable way to expose a service to 1000s of VPC(own or other accounts)
- No VPC peering, IGW, NAT, Route Table requires



### Transit Gateway