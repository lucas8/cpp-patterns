#include "Observer.hpp"
#include <iostream>
#include <list>

/*
 * Observer pattern
 * here we implement a dynamicly alloced observer-subject list
 * we can also create an intrusive singly linked list
 * and the last implementation is a pool of list nodes which is a linked list
 * with a pointer to the observer
 */

namespace Observer {

class IObserver {
public:
  virtual ~IObserver() {}
  // these params will change, we should generally pass in an event
  virtual void onNotify(const std::string &message) = 0;
};

class ISubject {
public:
  void addObserver(IObserver *observer) { observers_.push_back(observer); }

  void removeObserver(IObserver *observer) { observers_.remove(observer); }

protected:
  // we only want the caller to notify observers
  void notify(const std::string &message) {
    for (auto observer : observers_) {
      observer->onNotify(message);
    }
  }

private:
  std::list<IObserver *> observers_;
};

class Observer : public IObserver {
public:
  Observer(ISubject &subject) : subject_{subject} {
    this->subject_.addObserver(this);
  };
  ~Observer() { this->subject_.removeObserver(this); }

  virtual void onNotify(const std::string &message) {
    std::cout << "Observer: received message " << message << '\n';
  };

private:
  ISubject &subject_;
};

class Subject : public ISubject {
public:
  void send(const std::string &message) { notify(message); };
};

void test() {
  // if we make the observer a singly linked list,
  // we dont need the dynamic alloc call here
  Subject subject;

  Observer observer{subject};
  Observer observer2{subject};

  // send a message
  subject.send("hello, world!");
}

} // namespace Observer
