#include "Command.hpp"
#include "CommandCounter.hpp"
#include "Flywheel.hpp"
#include "Observer.hpp"
#include "Prototype.hpp"
#include <iostream>

int main() {
  // Command
  Command::test();
  CommandCounter::test();

  // Flywheel
  Flywheel::test();

  // Observer
  Observer::test();

  // Prototype
  Prototype::test();

  return 0;
}
