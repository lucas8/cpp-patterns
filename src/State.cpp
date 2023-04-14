#include "State.hpp"
#include <iostream>

/**
 *
 * State Machines
 * here we implement a simple user input handler
 *
 */

namespace State {

constexpr int MAX_CHARGE = 10;
enum Input { INPUT_RELEASE_DOWN, INPUT_PRESS_B };

// Note: we can also use switches and enums for a simpler state machine

// this is a forward declaration so we can use it in PlayerState

class PlayerState {
public:
  virtual ~PlayerState(){};
  virtual PlayerState *handleInput(Player &player, Input input){};

  virtual void update(Player &player){};
  virtual void enter(Player &player){};

  // Note: static is usually better for perf
  // see how ducking STATIC is triggered inside of the standing state
  static StandingState standing;
  static DuckingState ducking;
};

class Player {
public:
  Player(PlayerState *initialState) {
    state_ = initialState;
    state_->enter(*this);
  }

  virtual void handleInput(Input input) {
    PlayerState *state = state_->handleInput(*this, input);
    if (state != NULL) {
      delete state_;
      state_ = state;

      state_->enter(*this);
    }
  }

  virtual void setGraphics(const std::string &msg) {
    std::cout << "State: msg recieved " << msg << '\n';
  };
  virtual void superBomb(){};

  PlayerState *state_;
};

class DuckingState : public PlayerState {
public:
  DuckingState() : chargeTime_{0} {}

  virtual void enter(Player &player) { player.setGraphics("ducking"); }

  virtual void update(Player &player) {
    chargeTime_++;
    if (chargeTime_ == MAX_CHARGE) {
      player.superBomb();
    }
  }

private:
  int chargeTime_;
};

class StandingState : public PlayerState {
public:
  virtual void enter(Player &player) { player.setGraphics("standing"); }

  virtual PlayerState *handleInput(Player &player, Input input) {
    if (input == INPUT_PRESS_B) {
      // this is another (faster) way to set the state using static elements
      /* player.state_ = &PlayerState::standing; */
      /* player.setGraphics("ducking"); */

      return new DuckingState();
    }

    // this isn't part of the pattern, just need it -_-
    return NULL;
  }
};

void test() {
  Player *p = new Player(new StandingState());
  p->handleInput(INPUT_PRESS_B);
}

} // namespace State
