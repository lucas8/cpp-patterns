#include "Flyweight.hpp"
#include <iostream>
#include <random>
#include <stdint.h>

/*
 * Flyweight pattern
 * effiency pattern, used to render a lotta stuff
 */

namespace Flyweight {

constexpr int WIDTH = 10;
constexpr int HEIGHT = 10;

// not sure what a texture type is yet...
struct Texture {};
const Texture GRASS_TEXTURE;
const Texture HILL_TEXTURE;
const Texture RIVER_TEXTURE;

class Terrain {
public:
  Terrain(int moveCost, bool isWater, Texture texture)
      : moveCost_{moveCost}, isWater_{isWater}, texture_(texture) {}

  // const indicates that this fn does not modify the underlying Terrian
  int getMoveCost() const { return moveCost_; }
  bool isWater() const { return isWater_; }
  const Texture &getTexture() const { return texture_; }

private:
  int moveCost_;
  bool isWater_;
  Texture texture_;
};

class World {
public:
  // we should really use unique pointers for this to ensure
  // the texture isn't created 2x
  World()
      : grassTerrain_{1, false, GRASS_TEXTURE},
        hillTerrain_{2, false, HILL_TEXTURE},
        riverTerrain_{3, true, RIVER_TEXTURE} {};

  void generateTerrain() {
    for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
        // make everything grass lol
        // this should be a more fleshed out terrain generator
        tiles_[x][y] = &grassTerrain_;
      }
    }
  }

  // we can expose the terrain ref object directly (clean)
  const Terrain &getTile(int x, int y) const { return *tiles_[x][y]; }

private:
  Terrain grassTerrain_;
  Terrain hillTerrain_;
  Terrain riverTerrain_;

  // c++ 2d array init
  Terrain *tiles_[WIDTH][HEIGHT];
};

void test() {
  World world;
  world.generateTerrain();

  auto tile = world.getTile(2, 4);

  std::cout << "Flyweight: tile move cost is " << tile.getMoveCost() << '\n';
}

} // namespace Flyweight
