# instance storage

## EBS

- An Elastic Block Store Volume is a network drive you can attach to your instances while they run
- it allows your instances to persist data, even after teramination
- it can only be mounted to one instance at a time(at the CCP level)
- It are bound to a specific availability zone



EBS Volume Types

- gp2/gp3(SSD): General purpose Ssd volume that balances price and performance for a wide variety of workloads
- Io1/io2(SSD): Highest-performance SSD volume for mission-critical low-latency or high-throughput workloads
- Stl(HDD): low cost HDD volume designed for frequently accessed throughput-intensive workloads
- Scl(HDD): lowest cost HDD volume designed for less frequently accessed workloads

Only gp2/gp3/io1/io2 can be used as boot volumes



## EFS - Elastic File System

- Managed NFS(network file system) that can be mounted on many EC2
- EFS works with EC2 instances in multi-AZ
- Highly available, scalable, expensive
- Uses NFSv4.I protocol
- Uses security group to control access to EFS
- Compatible with Linux based AMI(not support windows)