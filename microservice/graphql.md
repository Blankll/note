# graphQL

Issues:

1. same data need to adapt various customer needs
2. 





It is not simply a replacement from HTTP endpoint-based APIs or the “next REST”

it is a great solution to build APIs that need to tackle  challenge of building experience based APIs

A GraphQL schema must always define a Query Root

```gql
type Query {
	shop(id: ID): Shop!
}
```

Root types:

1. Query
2. Mutation
3. Subscription





What Makes an API Great?

> APIs should be easy to use and hard to misuse



## Gadence

**Design First**

> APIs, especially public ones, are incredibly hard to change once they have been exposed. Thinking of design initially, and making sure we have a great understanding of the concepts enables us to lower the risk of breaking changes down the line.

**Client First**

> Design GraphQL APIs with client use cases in mind first  before anything else.

YAGNI:  should provide just enough features for clients to achieve the use cases they’re interested in.

Naming

> conveys information on what the API probably does
>
> consistency is king of naming

# [GraphQL: Non-nullable array/list](https://stackoverflow.com/questions/46770501/graphql-non-nullable-array-list)

| declaration | null | []   | [null] | [{foo: 'BAR'}] |
| ----------- | ---- | ---- | ------ | -------------- |
| [Vote!]!    | no   | yes  | no     | yes            |
| [Vote]!     | no   | yes  | yes    | yes            |
| [Vote!]     | yes  | yes  | no     | yes            |
| [Vote]      | yes  | yes  | yes    | yes            |



### pagenation

Option 1: offset + page_size

```
query(limit:Int, page:Int)
```

Option 2: cursor

```
query(limit:Int, after:String)
```

