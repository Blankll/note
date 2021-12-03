# instance storage

## EBS

- An Elastic Block Store Volume is a network drive you can attach to your instances while they run
- it allows your instances to persist data, even after teramination
- it can only be mounted to one instance at a time(at the CCP level)
- It are bound to a specific availability zone



EBS Volume Types

- gp2/gp3(SSD): General purpose Ssd volume that balances price and performance for a wide variety of workloads
- Io1/io2(SSD): Highest-performance SSD volume for mission-critical low-latency or high-throughput workloads(when need more than 16000IOPS)
- Stl(HDD): low cost HDD volume designed for frequently accessed throughput-intensive workloads
- Scl(HDD): lowest cost HDD volume designed for less frequently accessed workloads

Only gp2/gp3/io1/io2 can be used as boot volumes

#### encrypt an unencrypted EBS volume

1. Create an EBS snapshot of the volume
2. copy and encrypt the EBS snapshot(kms key)
3. Create new EBS volume from the encrypted snapshot
4. Attach the encrypted volume to original instance



## EFS - Elastic File System

- Managed NFS(network file system) that can be mounted on many EC2
- EFS works with EC2 instances in multi-AZ
- Highly available, scalable, expensive(3x gp2)
- Uses NFSv4.I protocol
- Uses security group to control access to EFS
- Compatible with Linux based AMI(not support windows)

Performance  mode:

- General purpose(default)
- Max I/O

Throughput mode

- Bursting
- Provision

