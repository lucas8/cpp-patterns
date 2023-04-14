#include "singleton.hpp"
#include "assert.h"
#include <iostream>
#include <string>

namespace Singleton {

// This is the traditional implementation of a singleton
class SimpleSingleton {
public:
  // using this message thing to prove that the initializer only gets called
  // once
  SimpleSingleton(const std::string &msg) {
    std::cout << "Singleton: creating new instance with msg: " << msg << '\n';
  }

  static SimpleSingleton &instance(const std::string &msg) {
    static SimpleSingleton *instance = new SimpleSingleton(msg);

    return *instance;
  }

private:
  SimpleSingleton() {}
};

// This is a better method using static class members
class StaticClassSingleton {
public:
  StaticClassSingleton() { assert(!instantiated_); }

  ~StaticClassSingleton() { instantiated_ = false; }

private:
  static bool instantiated_;
};

bool StaticClassSingleton::instantiated_ = false;

void test() {
  SimpleSingleton::instance("hello from lazy init");
  SimpleSingleton::instance("this message won't be shown");
}

} // namespace Singleton
