#include <iostream>

#include "file_manager.hpp"

int main() {
  auto fm = caskdb::FileManager("cask.db");
  std::cout << "Hello, caskdb " << fm.FileName() << std::endl;
}