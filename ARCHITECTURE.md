# CaskDB Architecture

CaskDB follows closely the [Bitcask](https://riak.com/assets/bitcask-intro.pdf) design with a few changes.

## Log File

Log files are append-only files where all an entire storage entry is written, a *storage entry* can be seen as :

```
[CRC32][Timestamp][KeySize][ValueSize][Key][Value]
```

The file header is composed of an 32-byte header

```
[MAGIC][SEGMENT_ID][FILE_ID]
```

The **magic** is used to ensure file-format compatibility and the **segment id** is how we represent files internally
while **file id** is used to name the actual log file on disk.

## Key Dir

The *KeyDir* is an in-memory index that stores direct offsets to the values on disks, the index maps a sequency of bytes (key)
to an *entry* represented as :

```
[Key] => [SegmentID][ValueSize][ValueOffset][Timestamp]
```
Writes to the index will always overwrite the older value, but since the log file is append only, the newly written value is appended
to the end and the old one is marked using a **tombstone**.

All new reads will read the latest value, since the *KeyDir* is considered as the source of truth.

## Recovery and Startup

Recovery is done by a sequential read of the log files, during this process the CRC32 checksum is checked against
the checksum of the *storage entry* to protect against data corruption.

During the recovery process, the index is rebuilt from scratch and can optionally ignore *tombstones*, *corrupt entries*...

## Tombstones

The tombstone value is defined as the following 16-byte sequence.

```
%<!(T|O|M|B)!>%_
```

## Performance

As of now, using a non-indicative benchmark (Write 1 million keys in a loop) is done in 12 seconds
which can be translated as 80,000 Writes/Sec.
