/**
 * @file storage.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief Header file for the storage engine.
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "file_manager.hpp"
#include "index_mem.hpp"

namespace caskdb {
/**
 * @brief DiskStorage implements the caskdb storage engine using FileManager as
 * an I/O backend and MemIndexMap as an in-memory index.
 *
 */
class DiskStorage {
  // Filename
  std::string file_name_;
  // File manager
  FileManager fm_;
  // In-memory index
  MemIndexMap index_;

 public:
  /**
   * @brief Construct a new Disk Storage object
   *
   * @param file
   */
  explicit DiskStorage(const std::string& file);

  ~DiskStorage() = default;

  /**
   * @brief Prevent copying DiskStorage.
   *
   */
  DiskStorage(const DiskStorage& other) = delete;
  DiskStorage operator=(const DiskStorage& other) = delete;

  /**
   * @brief Enforce the default move constructor for DiskStorage type.
   *
   */
  DiskStorage(DiskStorage&& other) = default;
  DiskStorage& operator=(DiskStorage&& other) = default;

  /**
   * @brief Store a key-value pair on the on-disk log structured hash-table.
   *
   * @param key
   * @param value
   */
  void Put(const std::string& key, const std::string& value);

  /**
   * @brief Get a value from the on-disk log structured hash-table given its
   * key.
   *
   * @param key
   * @return std::string
   */
  std::string Get(const std::string& key);

  /**
   * @brief Close and free undelying resource.
   *
   */
  void Close();
};

}  // namespace caskdb
