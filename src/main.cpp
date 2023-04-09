#include "Command.hpp"
#include "CommandCounter.hpp"
#include "Flywheel.hpp"
#include <iostream>

int main() {
  // Command
  Command::test();
  CommandCounter::test();

  // Flywheel
  Flywheel::test();

  return 0;
}
