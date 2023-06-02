# Protobuf_test
test protobuf library
# Reference
> https://www.jianshu.com/p/b33ca81b19b5

# Precondition
- ubuntu20.04
- install protobuf
```shell
sudo apt install libprotobuf17
```


# Run
## quick start
```shell
mkdir build
cd build
cmake ..
./protobuf_test pb.dat

```

## more
- modify addressbook.proto
- generate new code
```shell
protoc --cpp_out=src addressbook.proto

```

# Sumary
## ZigZag
## advantage
- Small and quick
- Easy to use. Provide setter getter serialize unserialize method
- Backword compatible
