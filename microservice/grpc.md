# gRPC

Protocol: build on HTTP/2 protocol

Message Format: Protocol buffers

## setup

1. Install protobuf

   ```bash
   brew install protobuf
   protoc --version
   ```

2. **Go plugins** for the protocol compiler(if using go)

   ```bash
   go install google.golang.org/protobuf/cmd/protoc-gen-go@v1.28
   protoc-gen-go --version
   go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@v1.2
   protoc-gen-go-grpc --version
   ```

   

## gRPC types

Unary gRPC

Client streaming gRPC

Server streaming gRPC

Bidirectional streaming gRPC



