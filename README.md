# Cask-db

Caskdb is a C++ implementation of [bitcask](https://riak.com/assets/bitcask-intro.pdf)
with iterative improvements.

## How it works

Caskdb is an on-disk log-structured hash table, log-structured means the underlying file
is an append-only log while hash table points to the data storage interface (keys and values).

When a key, value pair is stored the key is indexed in an in-memory hashmap, the entries stored
in-memory store all metadata that allows fetching the serialized on-disk bytes representing the
value.
