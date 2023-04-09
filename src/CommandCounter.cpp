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
    } else {
      std::cout << "Nothing to undo!" << '\n';
    }
  }

  void redo() {
    if (!redoStack_.empty()) {
      auto cmd = redoStack_.top();
      cmd->redo();
      redoStack_.pop();
      cmdStack_.push(cmd);
    } else {
      std::cout << "Nothing to redo!" << '\n';
    }
  }

private:
  std::stack<std::shared_ptr<Command>> cmdStack_;
  std::stack<std::shared_ptr<Command>> redoStack_;
};

void test() {
  auto count = std::make_unique<int>(0);
  CommandManager cmdManager;

  // this is our "render loop"
  while (true) {
    std::cout << "Enter a counter command: ";

    // Get user input
    char i;
    std::cin >> i;

    if (i == 'i') {
      std::shared_ptr<Command> cmd(new IncrementCommand(count));
      cmdManager.run(cmd);
    } else if (i == 'u') {
      cmdManager.undo();
    } else if (i == 'r') {
      cmdManager.redo();
    }

    std::cout << "Count is now: " << *count << '\n';
  }
}

} // namespace CommandCounter
