#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>
#include <iomanip>

#include "command.hpp"
#include "inode.hpp"
#include "MyFileSystem.hpp"

using std::cout;
using std::endl;
using std::fstream;
using std::getline;
using std::ifstream;
using std::left;
using std::setfill;
using std::setprecision;
using std::setw;
using std::stoi;
using std::strcpy;
using std::string;
using std::vector;

size_t findNextNumber(string s, size_t pos = 0)
{
  while (pos < s.length() && !isdigit(s[pos]))
  {
    pos++;
  }
  return pos;
}

size_t findNextSpace(string s, size_t pos = 0)
{
  while (pos < s.length() && !isspace(s[pos]))
  {
    pos++;
  }
  return pos;
}

string getFileName(string commandStr)
{
  auto lastFilenameCharPos = findNextSpace(commandStr, 2UL);
  return commandStr.substr(2UL, lastFilenameCharPos - 2UL);
}

int getBlockSize(string commandStr)
{
  size_t endPos = commandStr.length() - 1;
  size_t pos = endPos;
  while (!isspace(commandStr[pos]))
  {
    pos--;
  }
  return stoi(commandStr.substr(pos + 1, endPos - pos));
}



int main(int argc, char *argv[])
{
  MyFileSystem fileSystem = MyFileSystem("diskderp");
  fileSystem.create("newFile.txttttt", 8);
  fileSystem.create("hi.txt", 2);

  // const char *inputFilePath = argv[1];
  // const char *diskFilePath = argv[2];
  // ifstream inputFile;
  // fstream diskFile;

  // INode node = INode();

  // vector<Command *> commandVector = vector<Command *>();

  // // Check argument validity
  // if (argc != 3)
  // {
  //   printf("Invalid arguments. Usage: filesim [input file] [diskfile]\n");
  //   exit(1);
  // }

  // // Open files
  // inputFile.open(inputFilePath);
  // if (inputFile.bad())
  // {
  //   printf("Error opening input file.\n");
  //   exit(1);
  // }

  // // Extract file data from inputFile
  // string diskName = "";
  // getline(inputFile, diskName);

  // string commandStr;
  // while (getline(inputFile, commandStr))
  // {
  //   Command *newCommand = new Command();

  //   newCommand->action = tolower(commandStr[0]);

  //   switch (newCommand->action)
  //   {
  //   case 'R':
  //   case 'W':
  //   case 'C':
  //     newCommand->blockNum = getBlockSize(commandStr);
  //   case 'D':
  //     strcpy(newCommand->fileName, getFileName(commandStr).c_str());
  //     break;
  //   default:
  //     break;
  //   }

  //   commandVector.push_back(newCommand);
  // }

  // cout << "Number of commands: " << commandVector.size() << endl;
  // for (auto command : commandVector)
  // {
  //   // cout << command->action << " " << command->fileName << " " << command->blockNum << endl;
  //   delete command;
  // }

  // inputFile.close();
  return 0;
}
