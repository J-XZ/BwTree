#include "../src/bwtree.h"
#include "iostream"
#include <string>
#include <vector>

int main() {
  wangziqi2013::bwtree::print_flag = true;

  auto tree = new wangziqi2013::bwtree::BwTree<std::string, std::string>{true};

  // tree->RegisterThread();
  tree->UpdateThreadLocal(1);
  tree->AssignGCID(0);

  tree->Insert("hello", "world");
  std::string value;

  std::vector<std::string> values;
  tree->GetValue("hello", values);

  for (const auto &val : values) {
    std::cout << "Key: hello, Value: " << val << std::endl;
  }

  delete tree;

  return 0;
}