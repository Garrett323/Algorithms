#pragma once
#include "primitives.hpp"
#include "snake.hpp"
#include <functional>
#include <map>

namespace graph_agent {
class GraphAgent {
public:
  GraphAgent(snake::GameState *);
  snake::GameState *gameState = nullptr;
  std::function<snake::Direction(void)> predict = nullptr;
  std::function<void(void)> update = nullptr;

private:
  std::map<Point, snake::Direction> cycle;
  bool go_right, go_up;
};

} // namespace graph_agent
