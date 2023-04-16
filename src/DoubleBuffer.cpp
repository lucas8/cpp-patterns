#include "DoubleBuffer.hpp"
#include <iostream>
#include <string>

namespace DoubleBuffer {

const static int WHITE = 0;
const static int BLACK = 1;

// This is a simple example of a how a double buffer is used in graphics
// programming to avoid screen tearing

class FrameBuffer {
public:
  void clear() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
      pixels_[i] = WHITE;
    }
  }

  void draw(int x, int y) { pixels_[(WIDTH * y) + x] = BLACK; }

  const char *getPixels() { return pixels_; }

private:
  static const int WIDTH = 160;
  static const int HEIGHT = 120;

  char pixels_[WIDTH * HEIGHT];
};

class Scene {
public:
  Scene() : current_(&buffers_[0]), next_(&buffers_[1]) {}

  void draw() {
    next_->clear();
    next_->draw(1, 1);
    next_->draw(4, 1);
    swap();
  }

  FrameBuffer &getBuffer() { return *current_; }

private:
  void swap() {
    FrameBuffer *temp = current_;
    current_ = next_;
    next_ = temp;
  }

  FrameBuffer buffers_[2];
  FrameBuffer *current_;
  FrameBuffer *next_;
};

// This is an example of how we can use double buffers when creating our ai

class Actor {
public:
  Actor() : currentSlapped_(false) {}

  virtual ~Actor() {}
  virtual void update() = 0;

  void swap() {
    // swapping the buffer
    currentSlapped_ = nextSlapped_;
    nextSlapped_ = false;
  }

  void slap() { nextSlapped_ = true; }
  bool wasSlapped() { return currentSlapped_; }

private:
  bool currentSlapped_;
  bool nextSlapped_;
};

class Stage {
public:
  void add(Actor *actor, int index) { actors_[index] = actor; }

  void update() {
    std::cout << "DoubleBuffer: updating actor buffers and swapping for next "
                 "frame \n";
    for (int i = 0; i < NUM_ACTORS; i++) {
      actors_[i]->update();
    }
    for (int i = 0; i < NUM_ACTORS; i++) {
      actors_[i]->swap();
    }
  }

private:
  static const int NUM_ACTORS = 3;

  Actor *actors_[NUM_ACTORS];
};

class Comedian : public Actor {
public:
  Comedian(const std::string &name) : name_{name} {}

  void face(Comedian *actor) { facing_ = actor; }

  virtual void update() {
    if (wasSlapped()) {
      std::cout << "DoubleBuffer: " << name_ << " was slapped, slapping "
                << facing_->name_ << '\n';
      facing_->slap();
    }
  }

private:
  const std::string &name_;
  Comedian *facing_;
};

void test() {
  Stage stage;

  Comedian *harry = new Comedian("harry");
  Comedian *baldy = new Comedian("baldy");
  Comedian *chump = new Comedian("chump");

  harry->face(baldy);
  baldy->face(chump);
  chump->face(harry);

  // now that we have added double buffer, the order in which
  // the actors are updates doesn't matter
  stage.add(harry, 2);
  stage.add(baldy, 1);
  stage.add(chump, 0);

  harry->slap();
  stage.update();
  stage.update();
}

} // namespace DoubleBuffer
