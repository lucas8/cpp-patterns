#include "CommandCounter.hpp"
#include <iostream>
#include <memory>
#include <stack>

namespace CommandCounter {

class Command {
public:
  virtual ~Command(){};
  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual void redo() = 0;
};

class IncrementCommand : public Command {
public:
  IncrementCommand(std::unique_ptr<int> &count) : count_{count} {};

  virtual void execute() override {
    // increment the value at the pointer (not the pointer itself)
    ++*count_;
  };
  virtual void undo() override { --*count_; }
  virtual void redo() override { ++*count_; }

private:
  std::unique_ptr<int> &count_;
};

class CommandManager {
public:
  CommandManager(){};

  void run(std::shared_ptr<Command> cmd) {
    cmd->execute();
    cmdStack_.push(cmd);
    // clear redo stack
    redoStack_ = std::stack<std::shared_ptr<Command>>();
  }

  void undo() {
    if (!cmdStack_.empty()) {
      auto cmd = cmdStack_.top();
      cmd->undo();
      cmdStack_.pop();
      redoStack_.push(cmd);
    }
  }

  void redo() {
    if (!redoStack_.empty()) {
      auto cmd = redoStack_.top();
      cmd->redo();
      redoStack_.pop();
      cmdStack_.push(cmd);
    }
  }

private:
  std::stack<std::shared_ptr<Command>> cmdStack_;
  std::stack<std::shared_ptr<Command>> redoStack_;
};

void test() {
  auto count = std::make_unique<int>(0);
  CommandManager cmdManager;
  std::cout << "CommandCounter: initializing count at 0" << '\n';

  std::shared_ptr<Command> cmd(new IncrementCommand(count));
  cmdManager.run(cmd);
  std::cout << "CommandCounter: increment by 1, count is " << *count << '\n';

  cmdManager.undo();
  std::cout << "CommandCounter: undo, count is " << *count << '\n';

  cmdManager.redo();
  std::cout << "CommandCounter: redo, count is " << *count << '\n';
}

} // namespace CommandCounter
