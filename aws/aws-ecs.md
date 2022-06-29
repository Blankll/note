# AWS ECS

Elastic contianer service

ECS with ec2 lunch type: config ec2 type and autoscaling policy by ourself

ECS with Fargate - server less offering

IAM Roles for ECS

EC2 instance profile

- used by the ECS agent
- Makes API calls to ECS service
- send container logs to cloudWtach logs
- Pull docker image from ECR
- Reference sensitive data in secrets Manager or SSM parameter Store

ECS Task Role

- Allow each task to have a specific role
- Use different roles for the different ECS service
- Task role is defined in the task definition



Fix for Lustre is not  supported 

S3 cannot be munted as a file system
