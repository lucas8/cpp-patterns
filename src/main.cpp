#include "Blah.h"
#include <iostream>

int main() {
  A::B::Blah blah;

  std::cout << blah.foo() << '\n';

  return 0;
}
