# ec2-instance

configuration options

- Bootstrap script(configure at first launch): EC2 User Data



### EC2 User Data

- It is possible to bootstrap our instance using an EC2 User data script
- Scripts only run once at the instance first start
- EC2 User Data is used to automate boot tasks such as: install update & software..
- It runs with root user



### EC2 metadata

EC2 instance metadata is data about your instance that you can use to configure or manage the running instance. You cannot use EC2 instance metadata to put the instance in wait state. Eg.tag

### Lunch-types

- On-demand instance: short workloads, predictable pricing
- Reserved instance
- Spot instance: short workloads, cheap, can lose instance
- dedicated hosts: book an entire physical server, control instance placement

**EC2 dedicated hosts**

EC2 instances on physical servers that are dedicated for your use. Dedicated Hosts give you additional visibility and control over how instances are placed on a physical server, and you can reliably use the same physical server over time. As a result,<span style="color:red"> Dedicated Hosts enable you to use your existing server-bound software licenses like Windows Server</span> and address corporate compliance and regulatory requirements.

**EC2 dedicated instances** 

EC2 instances that run in a VPC on hardware that's dedicated to a single customer. Your dedicated instances are physically isolated at the host hardware level from instances that belong to other AWS accounts. Dedicated instances may share hardware with other instances from the same AWS account that are not dedicated instances. 

**EC2 On-Demand Instances **

 Pay, by the second, for the instances that you launch.

**EC2 Reserved Instances**

 Reduce your Amazon EC2 costs by making a commitment to a consistent instance configuration, including instance type and Region, for a term of 1 or 3 years.





**placement groups**

- Cluster placement group

  grouping of instances within a single Availability Zone. A cluster placement group can span peered VPCs in the same Region. Instances in the same cluster placement group enjoy a higher per-flow throughput limit for TCP/IP traffic and are placed in the same high-bisection bandwidth segment of the network.

- Partition placement group

  Partition placement groups help reduce the likelihood of correlated hardware failures for your application. When using partition placement groups, Amazon EC2 divides each group into logical segments called partitions. Amazon EC2 ensures that each partition within a placement group has its own set of racks. Each rack has its own network and power source. No two partitions within a placement group share the same racks, allowing you to isolate the impact of hardware failure within your application.

  can have a maximum of seven partitions per Availability Zone.

- Spread placement group

   Grouping of instances that are each placed on distinct racks, with each rack having its own network and power source. You can have a maximum of seven running instances per Availability Zone per group.





**launch template & launch configuration **

A launch template is similar to a launch configuration, in that it specifies instance configuration information such as the ID of the Amazon Machine Image (AMI), the instance type, a key pair, security groups, and the other parameters that you use to launch EC2 instances. Also, defining a launch template instead of a launch configuration allows you to have multiple versions of a template.

With launch templates, you can provision capacity across multiple instance types using both On-Demand Instances and Spot Instances to achieve the desired scale, performance, and cost.

A launch configuration is an instance configuration template that an Auto Scaling group uses to launch EC2 instances. When you create a launch configuration, you specify information for the instances such as the ID of the Amazon Machine Image (AMI), the instance type, a key pair, one or more security groups, and a block device mapping.

You cannot use a launch configuration to provision capacity across multiple instance types using both On-Demand Instances and Spot Instances. 

It is not possible to modify a launch configuration once it is created. The correct option is to create a new launch configuration to use the correct instance type. Then modify the Auto Scaling group to use this new launch configuration. Lastly to clean-up, just delete the old launch configuration as it is no longer needed.