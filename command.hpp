#if !defined(COMMAND_HPP_)
#define COMMAND_HPP_

struct Command {
  char action;
  char fileName[16];
  int blockNum;
};

#endif // COMMAND_HPP_

