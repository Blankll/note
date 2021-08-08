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

#### Volume Gateway

- Stored volumes - Entire dataset is stored on site and is asynchronously backup to S3
- Cached volumes - Entire dataset is stored on S3 and the most frequently accessed is cached on site

#### Gateway Virtual Tape Library

