#include "Observer.hpp"
#include <iostream>

/*
 * Observer pattern
 * here we implement a dynamicly alloced observer-subject list
 * we can also create an intrusive singly linked list
 * and the last implementation is a pool of list nodes which is a linked list
 * with a pointer to the observer
 */

namespace Observer {

constexpr int MAX_OBSERVERS = 10;

// some made up game entities to pass to our observer (achievement)
struct Entity {};
enum Event { EVENT_ENTITY_FELL };
enum Achievement { ACHIEVEMENT_FELL };

class Observer {
public:
  virtual ~Observer() {}
  // these patterns will change
  virtual void onNotify(const Entity &entity, Event event) = 0;
};

class Achievements : public Observer {
public:
  virtual void onNotify(const Entity &entity, Event event) {
    switch (event) {
    case EVENT_ENTITY_FELL:
      // do some work to check if the achievement has been unlocked
      unlock(ACHIEVEMENT_FELL);

      break;
    }
  };

private:
  void unlock(Achievement achievement) {
    // unlock the achievement / store it whatever
    std::cout << "Observer: unlocked an achievement!" << '\n';
  }
};

// we can now use this class
// an example would be attaching it to the "falling event" so observers
// could register themselves with physics.entityFell().addObserver(this)
class Subject {
public:
  void addObserver(Observer *observer) {
    // this is pretty unsafe, use a stack or vector
    observers_[numOfObservers_] = observer;
    ++numOfObservers_;
  }

  void removeObserver(Observer *observer) {
    // remove from array, decrement num
  }

  // we only want the caller (Physics) to notify observers
protected:
  void notify(const Entity &entity, Event event) {
    for (int i = 0; i < numOfObservers_; i++) {
      observers_[i]->onNotify(entity, event);
    }
  }

private:
  // in real code you would use a dynamicly sized collection
  Observer *observers_[MAX_OBSERVERS];
  int numOfObservers_ = 0;
};

// in real code this isn't good inheritence on the Physics engine
// subject should be an object on Physics
class Physics : public Subject {
public:
  void updateEntity(Entity &entity) {
    // some other physics math to calculate if the player is falling
    notify(entity, EVENT_ENTITY_FELL);
  };
};

void test() {
  Physics physics;

  // if we make the observer a singly linked list,
  // we dont need the dynamic alloc call here
  physics.addObserver(new Achievements());

  // pretend like we fell
  Entity entity;
  physics.updateEntity(entity);
}

} // namespace Observer
