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