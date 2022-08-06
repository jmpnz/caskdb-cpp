/**
 * @file storage.cpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief This file contains the implementation of DiskStorage which abstracts
 * an on-disk Log-Structured hashmap.
 * @version 0.1
 * @date 2022-08-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "storage.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "entry.hpp"
#include "header.hpp"
#include "serde.hpp"
#include "utils.hpp"

namespace caskdb {

/**
 * @brief Construct a new Disk Storage:: Disk Storage object
 *
 * @param file_name
 */
DiskStorage::DiskStorage(const std::string& file_name)
    : file_name_(file_name), fm_(file_name), index_() {}

/**
 * @brief Put a key, value pair onto the on-disk log-structured hash table.
 *
 * @param key
 * @param value
 */
void DiskStorage::Put(const std::string& key, const std::string& value) {
  // Build header metadata.
  auto [ts, k_size, v_size] = std::make_tuple(TimestampNow(), key.length(), value.length());
  // Build the index Entry
  Entry entry = Entry(ts, fm_.WriteCursorOffset(), kHeaderSize + k_size + v_size);
  // Store the entry in the index
  index_.Put(key, entry);
  // Build the value header
  Header hdr = Header(ts, k_size, v_size);
  // Buffer
  Buffer buf(kHeaderSize + k_size + v_size);
  buf.Append(hdr.Serialize());
  buf.Append(key.data(), key.size());
  buf.Append(value.data(), value.size());
  // Write the buffer.
  fm_.Write(buf.Data());
}

/**
 * @brief Fetch a value from the on-disk log-structured hash table given its
 * key, if the key is not in the database return the empty string.
 *
 * @param key
 * @return std::string
 */
std::string DiskStorage::Get(const std::string& key) {
  auto maybe_entry = index_.Get(key);
  if (!maybe_entry.has_value()) {
    return "" ;
  }
  auto entry = maybe_entry.value();
  auto bytes = fm_.Read(entry.Position(), entry.Size());
  auto header_bytes = std::vector<uint8_t>(bytes.begin(), bytes.begin() + kHeaderSize);
  auto hdr = Header().Deserialize(header_bytes);
  auto val_bytes = std::vector<uint8_t>(bytes.begin() + kHeaderSize + hdr.keySize, bytes.end());
  std::string val(val_bytes.begin(), val_bytes.end());
  return val;
}

/**
 * @brief Close underlying files.
 *
 */
void DiskStorage::Close() { fm_.Close(); }
}  // namespace caskdb
