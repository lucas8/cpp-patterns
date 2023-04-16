#include "Command.hpp"
#include "CommandCounter.hpp"
#include "DoubleBuffer.hpp"
#include "Flyweight.hpp"
#include "Observer.hpp"
#include "Prototype.hpp"
#include "Singleton.hpp"
#include "State.hpp"
#include <iostream>

int main() {
  // Command
  Command::test();
  CommandCounter::test();

  // Flyweight
  Flyweight::test();

  // Observer
  Observer::test();

  // Prototype
  Prototype::test();

  // Singleton
  Singleton::test();

  // State
  State::test();

  // State
  DoubleBuffer::test();

  return 0;
}
