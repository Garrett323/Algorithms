#pragma once
#include "snake.hpp"
#include <functional>
#include <random>

namespace agent {

class Agent {
public:
  Agent(snake::GameState *);

  std::function<snake::Direction(void)> predict = nullptr;
  std::function<void(void)> update = nullptr;

private:
  snake::GameState *gameState = nullptr;
  std::map<std::string, float> lookup;
  float learning_rate = 0.1;
  int dist;

  float estimate(snake::GameState);
};

} // namespace agent
