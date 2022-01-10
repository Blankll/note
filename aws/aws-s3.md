S3 reaplication

- Must enable versioning in source and destination
- Cross region replication
- Same region replication
- Buckets can be in different accounts
- Copying is asynchronous

S3 pr-signed URLs

- Can generate pre-signed URLs using sdk or cli

  - for downloads (easy can use cli)
  - for uploads (hader, must use sdk)

- Valid for a default of 3600 seconds can change temout with --expires-in

- example

   allow only logged-in users to download a premium video on your s3



## S3 Storage Classes

- Amazon S3 standard - General Purpose
- Amazon S3 Standard -Infrequent Access(IA)
- Amazon S3 One Zone-Infrequent Access
- Amazon S3 Intelligent Tiering
  - auto move between s3-standard and ia
- Amazon S3 Glacier
  - Expedited 1-5minutes
  - Standard 3 - 5 hours
  - Bulk 5 - 12 hours
  - Minimum storage duration 90 days
- Amazon S3 Glacier Deep Archive
  - standard 12 hours
  - Bulk 48 hours
  - Minimum storage duration 180days
- Amazon S3 Reduced Redundancy Storage(deprecated)



Amazon Athena

- serverless query service to perform analytics against S3 objects
- uses standard sql language to query files
- Support CSV JSON, ORC Avro and Parquet

## data consistency model for s3

- Read after write consistency for puts of new Objects
- Eventual consistency for overwrite PUTS and DELETEs(can take some time to propagate)



S3 standard

99.99% availability

99.999999999% durability

stored redundently across multiple facilities, and is designed to sustain the loss 2 facilities concurrently



### storage Gateway

#### File Gateway

- File Gateway - for flat files, stored directly on S3

Hardware Appliance -
Storage Gateway is available as a hardware appliance, adding to the existing support for VMware ESXi, Microsoft Hyper-V, and Amazon EC2. This means that you can now make use of Storage Gateway in situations where you do not have a virtualized environment, server-class hardware or IT staff with the specialized skills that are needed to manage them. You can order appliances from Amazon.com for delivery to branch offices, warehouses, and ג€outpostג€ offices that lack dedicated IT resources. Setup (as you will see in a minute) is quick and easy, and gives you access to three storage solutions:
File Gateway ג€" A file interface to Amazon S3, accessible via NFS or SMB. The files are stored as S3 objects, allowing you to make use of specialized S3 features such as lifecycle management and cross-region replication. You can trigger AWS Lambda functions, run Amazon Athena queries, and use Amazon Macie to discover and classify sensitive data.

#### Volume Gateway

- Stored volumes - Entire dataset is stored on site and is asynchronously backup to S3
- Cached volumes - Entire dataset is stored on S3 and the most frequently accessed is cached on site

#### Gateway Virtual Tape Library

