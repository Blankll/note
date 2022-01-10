A function can use up to 5 layers at a time.

The total unzipped size of the function and all layers can't exceed the unzipped deployment package size limit of 250 MB.



## limitation

- Memory allocation: 128MB ~ 10GB(1MB increments)
- Maximum execution time: 15 minutes
- Environment variables: 4kb
- Disk capacity in the "function container"(in /tmp): 512MB
- Concurrency executions: 1000 (can be increased)
- Function deployment size(compressed .zip): 50MB
- size of uncompressed deployment(code + dependencies): 25MB