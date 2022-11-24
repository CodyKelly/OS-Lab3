#if !defined(INODE_HPP_)
#define INODE_HPP_

struct INode {
  char name[16];
  int size;
  int blockPointers[8];
  int used;
};

#endif // INODE_HPP_
