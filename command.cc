#include "command.h"

Command::Command() {}

void Command::addCommand(const string newCmd) {
  shared_ptr<CommandMap> elem = head;
  int len = newCmd.size();
  for (int i = 0; i < len; ++i) {
    if (elem->umap.count(newCmd[i]) == 0) {
      elem->umap[newCmd[i]] = make_shared<CommandMap>();
    }
    elem->commands.emplace_back(newCmd);
    elem = elem->umap[newCmd[i]];
  }
  elem->commands.emplace_back(newCmd);
}

string Command::getCommand(const string cmd) const {
  shared_ptr<CommandMap> elem = head;
  int len = cmd.size();
  for (int i = 0; i < len; ++i) {
    if (elem->umap.count(cmd[i]) == 0) { return ""; }
    else if (elem->commands.size() == 1) { return elem->commands[0]; }
    else { elem = elem->umap[cmd[i]]; }
  }
  if (elem->commands.size() == 1) { return elem->commands[0]; }
  return "";
}
