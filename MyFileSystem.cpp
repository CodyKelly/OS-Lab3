#include <unistd.h>
#include <iostream>
#include <string.h>

#include "MyFileSystem.hpp"
#include "inode.hpp"

using namespace std;

const char *NotEnoughFreeBlocksException::what()
{
  return "NotEnoughFreeBlocksException";
}

const char *NoFreeINodesException::what()
{
  return "NoFreeINodesException";
}

const char *FileNotFoundException::what()
{
  return "FileNotFoundException";
}

MyFileSystem::MyFileSystem(const MyFileSystem &) {}

MyFileSystem::MyFileSystem(const string name)
{
  diskfile = fstream();
  diskfile.open(name);
  if (diskfile.bad())
  {
    printf("Error opening disk file.\n");
    exit(1);
  }
}

int MyFileSystem::create(const string filename, int size)
{
  if (size > 8) {
    std::cerr << "Files cannot be more than 8 blocks in size.";
    return 0;
  }

  if (filename.length() > 15) {
    std::cerr << "Filenames must be less than 16 characters";
    return 0;
  }

  int *freeBlocks;
  int nodeIndex;
  INode *node = new INode();

  try
  {
    freeBlocks = getFreeBlocks(size);
  }
  catch (NotEnoughFreeBlocksException)
  {
    std::cerr << "Not enough space on disk to create file" << endl;
    return 0;
  }

  try
  {
    nodeIndex = getFreeINode();
  }
  catch(NoFreeINodesException)
  {
    std::cerr << "The maximum number of files has been reached" << endl;
    return 0;
  }
  
  filename.copy(node->name, 16);
  memcpy(node->blockPointers, freeBlocks, 8);
  node->used = 1;
  node->size = size;

  writeINodeToIndex(nodeIndex, node);

  for (int i = 0; i < size; i++) {
    diskfile.seekp(freeBlocks[i]);
    diskfile.put(1);
  }

  delete freeBlocks;
  delete node;

  return 1;
}

int MyFileSystem::del(char name[16])
{

  
  return 1;
}

int MyFileSystem::ls()
{
  return 1;
}

int MyFileSystem::read(char name[16], int blockNum, char buffer[1024])
{
  return 1;
}

int MyFileSystem::write(char name[16], int blockNum, char buffer[1024])
{
  return 1;
}

int *MyFileSystem::getFreeBlocks(int size)
{
  char bitArray[128];
  int *freeBlocks = new int[8];
  int currentIndex = 0;
  diskfile.seekg(0);
  diskfile.read(bitArray, 128);
  for (int i = 0; i < 128; i++)
  {
    if (bitArray[i] == 0)
    {
      freeBlocks[currentIndex] = i;
      currentIndex++;
      if (currentIndex == size)
      {
        for (int i2 = currentIndex; i2 < 8; i2++) {
          freeBlocks[i2] = -1;
        }
        return freeBlocks;
      }
    }
  }
  delete freeBlocks;
  throw NotEnoughFreeBlocksException();
}

int MyFileSystem::getFreeINode() {
  diskfile.seekg(128);
  char data[56];
  for (int i = 0; i < 16; i++) {
    diskfile.read(data, 56);
    int used = data[52];
    if (!used) {
      return i;
    }
  }
  throw NoFreeINodesException();
}

INode *MyFileSystem::getINode(int index) {
  diskfile.seekg(getINodeAddress(index));
  
}

int MyFileSystem::getINodeAddress(int index) {
  return 128 + index * 56;
}

void MyFileSystem::writeINodeToIndex(int index, const INode *node) {
  const size_t nodeSize = sizeof(INode);
  char nodeData[nodeSize];
  memcpy(nodeData, node, nodeSize);
  diskfile.seekp(getINodeAddress(index));
  diskfile.write(nodeData, nodeSize);
}

MyFileSystem::~MyFileSystem()
{
  diskfile.close();
}