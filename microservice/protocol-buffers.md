# Protocol buffers 

Protocol buffers provide a language-neutral, platform-neutral, extensible mechanism for serializing structured data in a forward-compatible and backward-compatible way(like json)

Protocol buffer *messages* and *services* are described by engineer-authored `.proto` files

```protobuf
message Person {
  optional string name = 1;
  optional int32 id = 2;
  optional string email = 3;
}
```

The scenarios that fit for protocol buffers:

- Compact data storage
- Fast parsing
- Availability in many programming languages
- Optimized functionality through automatically-generated classes

## Protocol buffers workflow

![protocol buffers](https://developers.google.com/static/protocol-buffers/docs/images/protocol-buffers-concepts.png)

## Protocol Buffers Definition Syntax

field attribute:

- optional
- repeated
- singular(proto3)
- required (absent & strongly discouraged)

field data type:

- double/float
- Integer
- bytes
- bool
- string

See more in https://developers.google.com/protocol-buffers/docs/proto#scalar

- message
- enum
- oneof
- map

example

```protobuf
syntax = "proto3";

package todoPackage;

service TodoService {
    rpc createTodo(Todo) returns (Todo);
    rpc readTodos(void) returns (Todos);
}

message Todo {
    int32 id = 1;
    string text = 2;
}

message Todos {
    repeated Todo items = 1;
}
```

