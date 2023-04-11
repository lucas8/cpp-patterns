#include "Prototype.hpp"
#include <iostream>

/*
 * Prototype
 * here we implement a template based prototype
 * we can also use callbacks, or just simple clone hirerarchy
 */

namespace Prototype {

class IMonster {};

class Ghost : public IMonster {
public:
  Ghost() : health_{100} { std::cout << "Prototype: initialized ghost\n"; }

private:
  int health_;
};

class Spawner {
public:
  virtual ~Spawner() {}
  virtual IMonster *spawnMonster() = 0;
};

template <class T> class SpawnerFor : public Spawner {
public:
  virtual IMonster *spawnMonster() { return new T(); }
};

void test() {
  Spawner *ghostSpawner = new SpawnerFor<Ghost>();
  ghostSpawner->spawnMonster();
  ghostSpawner->spawnMonster();

  delete ghostSpawner;
}

} // namespace Prototype
