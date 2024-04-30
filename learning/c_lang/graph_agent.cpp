#include "graph_agent.hpp"
#include "snake.hpp"

namespace graph_agent {

GraphAgent::GraphAgent(snake::GameState *game) : gameState(game) {
  auto head = game->snake->body[0];
  auto body = game->snake->body[1];

  go_right = head.y == 0 && body.x > head.x;
  go_up = head.y < body.y;
  predict = [this] {
    auto head = gameState->snake->body[0];
    snake::Direction next;
    head.print();
    const int max_y = this->gameState->height - 1;
    const int max_x = this->gameState->width - 1;
    if (head.x == 0 && head.y != max_y) {
      next = snake::Down;
    } else if (head.y % 2 == 1 && head.x != max_x) {
      next = snake::Right;
    } else if (head.y % 2 == 0 && head.x != 1) {
      next = snake::Left;
    } else {
      next = snake::Up;
    }
    return next;
  };

  update = [] {};
}
} // namespace graph_agent
