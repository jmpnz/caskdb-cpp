// @file store.hpp
// @author jmpnz
// @desc class and method definitions for storage layer.
#include<vector>
#include<chrono>
#include<cstdint>
#include<iostream>

#include "serde.hpp"

// Header size in bytes.
const int kHeaderSize = 12;

class Header {
  public:
  Header(int32_t ts, int32_t key_size, int32_t value_size):timestamp_(ts),key_sz_(key_size),value_sz_(value_size){}
  Header():timestamp_(0), key_sz_(0),value_sz_(0){}
  
  std::vector<uint8_t> Serialize(){
    std::vector<uint8_t> bytes;
    bytes.reserve(12);
    auto ts = serialize_int32(timestamp_);
    auto ks = serialize_int32(key_sz_);
    auto vs = serialize_int32(value_sz_);
    bytes.insert(bytes.end(),ts.begin(),ts.end());
    bytes.insert(bytes.end(),ks.begin(),ks.end());
    bytes.insert(bytes.end(),vs.begin(),vs.end());

    return bytes;
  }
  void Deserialize(std::vector<uint8_t> bytes) {
    assert(bytes.size() == 12);
    std::vector<uint8_t> ts_(bytes.begin(),bytes.begin()+4);
    std::vector<uint8_t> ks_(bytes.begin()+4,bytes.begin()+8);
    std::vector<uint8_t> vs_(bytes.begin()+8,bytes.end());
    timestamp_ = deserialize_int32(ts_);
    key_sz_ = deserialize_int32(ks_);
    value_sz_ = deserialize_int32(vs_);
  }
  void Debug() {
    std::cout << "Timestamp :" << timestamp_ << '\n';
    std::cout << "Key Size: " << key_sz_ << '\n';
    std::cout << "Value Size: " << value_sz_ << '\n';
  }
  private:
  int32_t timestamp_;
  int32_t key_sz_;
  int32_t value_sz_;
};

template<typename K, typename V>
class NaiveMapStorage {
  public:
  NaiveMapStorage():store() {}
  V get(K key){
    return store[key];
  }
  void set(K key, V value){
    store[key] = value;
  }
  private:
    std::unordered_map<K,V> store;
};

template<typename K, typename V>
class DiskStorage {
  public:
  DiskStorage():filename_("cask.db"), write_pos_(0) {
    f_.open(filename_, std::ios::binary | std::ios::in | std::ios::app | std::ios::out);
  }
  void Set(std::string key, std::string value) {
    auto ts = std::chrono::system_clock::now();
    auto tsz = std::chrono::duration_cast<std::chrono::seconds>(ts.time_since_epoch()).count();

    auto header = Header(tsz,key.size(),value.size()).Serialize(); 
    std::vector<uint8_t> bytes;
    bytes.insert(bytes.end(), header.begin(), header.end());
    bytes.insert(bytes.end(),key.begin(),key.end());
    bytes.insert(bytes.end(),value.begin(),value.end());

    this->write(bytes);
  }
  std::string Get(std::string key) {
    return "";
  }
  void write(std::vector<uint8_t> data) {
    f_.seekp(write_pos_);
    f_.write((const char*)data.data(), data.size());
    f_.flush();
    write_pos_ += data.size();
  }
  void Close() {
    // Flush any buffered data.
    f_.flush();
    f_.close();
  }
  private:
    std::string filename_;
    int32_t write_pos_;
    std::fstream f_;

};
