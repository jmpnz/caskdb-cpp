# Cask-db

Caskdb is a C++17 implementation of [bitcask](https://riak.com/assets/bitcask-intro.pdf)
with iterative improvements.

## How it works

Caskdb is an on-disk log-structured hash table, log-structured means the underlying file
is an append-only log while hash table points to the data storage interface (keys and values).

When a key, value pair is stored the key is indexed in an in-memory hashmap, the entries stored
in-memory store all metadata that allows fetching the serialized on-disk bytes representing the
value.

## Usage

**Note** : Caskdb uses various C++17 features such as `std::optional` so you will need a C++17
compliant compiler.

```sh
$ mkdir build
$ cd build/
$ cmake ..
$ make
```
