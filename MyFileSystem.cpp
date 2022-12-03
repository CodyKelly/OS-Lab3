#include <unistd.h>

#include "MyFileSystem.hpp"

using namespace std;

MyFileSystem::MyFileSystem(char name[16]) {
  diskfile.open(name);
  if (diskfile.bad())
  {
    printf("Error opening disk file.\n");
    exit(1);
  }
}

int MyFileSystem::create(char name[16], int size) {

}

int MyFileSystem::del(char name[16]) {

}

int MyFileSystem::ls() {

}

int MyFileSystem::read(char name[16], int blockNum, char buffer[1024]) {

}

int MyFileSystem::write(char name[16], int blockNum, char buffer[1024]) {

}

bool MyFileSystem::checkForSufficientFreeBlocks() {
  diskfile.seekg
}