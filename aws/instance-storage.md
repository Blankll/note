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

|                                      |                     General Purpose SSD                      |                                                              | Provisioned IOPS SSD                                         |                                                 |                                                            |
| :----------------------------------- | :----------------------------------------------------------: | :----------------------------------------------------------: | ------------------------------------------------------------ | ----------------------------------------------- | ---------------------------------------------------------- |
| **Volume type**                      |                            `gp3`                             |                            `gp2`                             | `io2` Block Express ‡                                        | `io2`                                           | `io1`                                                      |
| **Durability**                       |  99.8% - 99.9% durability (0.1% - 0.2% annual failure rate)  |  99.8% - 99.9% durability (0.1% - 0.2% annual failure rate)  | 99.999% durability (0.001% annual failure rate)              | 99.999% durability (0.001% annual failure rate) | 99.8% - 99.9% durability (0.1% - 0.2% annual failure rate) |
| **Use cases**                        | Low-latency interactive appsDevelopment and test environments | Workloads that require:Sub-millisecond latencySustained IOPS performanceMore than 64,000 IOPS or 1,000 MiB/s of throughput | Workloads that require sustained IOPS performance or more than 16,000 IOPSI/O-intensive database workloads |                                                 |                                                            |
| **Volume size**                      |                        1 GiB - 16 TiB                        |                        4 GiB - 64 TiB                        | 4 GiB - 16 TiB                                               |                                                 |                                                            |
| **Max IOPS per volume** (16 KiB I/O) |                            16,000                            |                           256,000                            | 64,000 †                                                     |                                                 |                                                            |
| **Max throughput per volume**        |                         1,000 MiB/s                          |                         250 MiB/s *                          | 4,000 MiB/s                                                  | 1,000 MiB/s †                                   |                                                            |
| **Amazon EBS Multi-attach**          |                        Not supported                         |                          Supported                           |                                                              |                                                 |                                                            |
| **Boot volume**                      |                          Supported                           |                                                              |                                                              |                                                 |                                                            |

#### encrypt an unencrypted EBS volume

1. Create an EBS snapshot of the volume
2. copy and encrypt the EBS snapshot(kms key)
3. Create new EBS volume from the encrypted snapshot
4. Attach the encrypted volume to original instance



## EFS - Elastic File System

a shared POSIX file system for Linux systems

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



Amazon FSx

Launch 3rd party high-performance file systems on aws

fully managed service

- FSx for Lustre(linux and cluster)
  - for large scale computing, for ML, HPC
  - its integrates with S3, When linked to an S3 bucket, an FSx for Lustre file system transparently presents S3 objects as files and allows you to write changed data back to S3. FSx for Lustre provides the ability to both process the 'hot data' in a parallel and distributed fashion as well as easily store the 'cold data' on Amazon S3. 
- FSx for Wondows File Server
  - supports SMP protocol & Windows NTFS
  - Microsoft Active Directory integration, ACLs, user quotas
  - Built on SSD scale up to 10s of GB/s
  - Can be configured to be multi-AZ
  - cant integrates with S3
- FSx for NetApp ONTAP
