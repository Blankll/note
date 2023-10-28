# OpenSearch Serverless

Easy to administer

> No sizing, scaling, and auto tuning of cluster, and no shared and index lifecycle management

Fast

> automatically scale resources to maintain consistently fast data ingestion rates and  query response time

Ecosystem

> Get started in seconds using the same OpenSearch clients, pipelines and APIs

Cost-effective

> pay only for resources consumed



## building blocks

Collection:

- Time series
- Search

Separate endpoints for opensearch and opensearch Dashboard



OCUs(Opensearch Compute Units): used to index and search collections

- 6GB RAM increments 1vCPU
- minimum 4 OCU per account
- Max OCUs can be set to controll costs
- Automaticlly provisioned for the workload
- Shared across collections

## technical innovations

Storage and compute decoupled 

seperate index and search pipeline(scale search and indexing pipe individually)

Built-in hot-warm tier

active-stanby data nodes

secure service mesh