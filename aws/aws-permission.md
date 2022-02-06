# aws permission

group

user

role

Inline policy => the policy which avialable that role

policy 



SCP: 

- whitelist or blacklist IAM actions
- Applied at the OU or account level
- Does not apply to the master Account
- SCP is applied to all the Users and Roles of the Account including Root
- SCP does not affect service-linked roles(service-linked roles enable other AWS services to integrate with AWS Organizations and cant be restricted by SCPs)
- SCP must have an explicit Allow(does not allow anything by default)





- The web application calls on a Lambda function to perform some business logic 

- Resource-based policies allow other AWS resources / accounts to access the Lambda function 
- Execution roles allow the Lambda function to access other AWS resources (not relevant here