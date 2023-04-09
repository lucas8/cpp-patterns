#include "Command.hpp"
#include <iostream>

/*
 * The Command Pattern
 * See a more complete usage in todo
 */

namespace Command {

// Sample of a player object
struct Player {
  void jump() { std::cout << "Command: player jumped!" << '\n'; };
};

class Command {
public:
  virtual ~Command() {}
  // pure virtual function
  virtual void execute(Player &p) = 0;
};

class JumpCommand : public Command {
public:
  virtual void execute(Player &p) { p.jump(); }
};

/*
 * Implementation
 */

// We have a madeup input handler...
class InputHandler {
public:
  // just for testing: we create the jump command here
  // would likely be passed from something else
  InputHandler() : buttonX_{new JumpCommand()} {}
  ~InputHandler() { delete buttonX_; }

  Command *handleInput(char i);

private:
  Command *buttonX_;
};

// now we can allow the character to switch their binds
// because now the command controls which action is taken
// instead of this input handler
Command *InputHandler::handleInput(char i) {
  // some madeup function to check what button was pressed
  if (i == 'x')
    return buttonX_;

  return nullptr;
}

// somewhere in the render loop
void test() {
  InputHandler inputHandler;
  Player player;

  Command *command = inputHandler.handleInput('x');
  if (command) {
    command->execute(player);
  }
}

} // namespace Command
