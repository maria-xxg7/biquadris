#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct CommandMap {
  unordered_map<char, shared_ptr<CommandMap>> umap;
  vector<string> commands;
};

struct Command {
  Command();

  shared_ptr<CommandMap> head = make_shared<CommandMap>();
  void addCommand(const string newCmd);
  string getCommand(const string cmd) const;
};

#endif
