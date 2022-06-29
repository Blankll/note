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





## Tools

### DataSync

- move largeg amount of data from on-premises to AWS
- Can synchronize to S3, EFS, Fsx
- Move data from your NAS or file system via NFS or SMB
- Replication tasks can be scheduled hourly, daily, weekly

### Storage Gateway

- Bridge between on-premises data and clouud data in s3
- Use cases: disaster recovery, backup, restore
- 3 types of Storage Gateway
  - File Gateway
  - Volume Gateway
  - Tape Gateway

**File Gateway**

- configured S3 buckets are accessiible using NFS/SMB protocol from on-premises server
- Support S3 standard S3 IA, S3 One Zone IA
- Bucket access control by IAM roles  for each File Gateway
- Most recently used data is cached in File Gateway, 
- File Gateway can be mounted on many servers
- support to integrate with Active Directory

![file gateway](https://d1.awsstatic.com/cloud-storage/Amazon%20S3%20File%20Gateway%20How%20It%20Works%20Diagram.96e9f7180c6ec8b6212b4d6fadc4a9ac4507b421.png)

**FSx File Gateway**

- Native access to Amazon FSx for windows File Server
- Local cache for frequently accessed data
- Windows native compatibility(SMB, NTFS, Active Directory)
- Useful for group file shares and home directories

![fsx file gateway](https://d1.awsstatic.com/cloud-storage/Amazon%20FSx%20File%20Gateway%20How%20It%20Works%20Diagram.edbf58e4917d47d04e5a5c22132d44bd92733bf5.png)

**Volume Gateway**

- Block storage using iSCSI protocol backed by S3
- able to copy volumes using AWS Backup to store data  as Amazon EBS snapshots, which benefits for data protection, recovery, migration ...

Cached Volumes: low latency access to most recent data

Stored Volumes: entire dataset iis on premise, scheduled backup to S3

![volume gateway](https://d1.awsstatic.com/cloud-storage/volume-gateway-diagram.eedd58ab3fb8a5dcae088622b5c1595dac21a04b.png)

**Tape Gateway**

- for the company who usingg paysical tapes to backup
- Company use same process but data  stored in S3

![tape gateway](https://d1.awsstatic.com/product-marketing/Product-Page-Diagram_Tape-Gateway_HIW%402x%20(2).5ba3326ea93003722acc487804a34971613ec3c1.png)



# AWS Transfer Family

- Fully-manaegd service for file transfer into and out of S3 or EFS using FTP protocol
- Supported protocols: FTP, FTPS, SFTP
- Managed infrastructure, Scalable, Reliable, Highly Available

![transfer family](https://d1.awsstatic.com/cloud-storage/product-page-diagram_AWS-Transfer-Family_HIW-Diagram.4af0b3b19477f22bc7e37995c43cf833b6db0ce9.png)
