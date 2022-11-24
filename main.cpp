#include <iostream>
#include <string.h>

#include "inode.hpp"

int main(int argc, char *argv[]) {
  INode node = INode(); 
  strcpy(node.name, "hello");
  std::cout << node.name << std::endl;
  return 0;
}