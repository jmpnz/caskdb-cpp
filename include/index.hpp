/**
 * @file index.hpp
 * @author jmpnz (102270417+jmpnz@users.noreply.github.com)
 * @brief CaskDB Indexer supports an on-disk and in-memory index
 * @version 0.1
 * @date 2022-08-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

namespace caskdb {
/**
 * @brief Index supports an in-memory index using various caching strategies
 * accompanied by an on-disk index that is used for recovery and fast startups.
 * While the recovery process can always be done from a WAL file, index file
 * is used as a hint to speedup startup times.
 */
class Index {};
}  // namespace caskdb
