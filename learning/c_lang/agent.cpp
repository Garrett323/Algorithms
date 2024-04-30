#include "agent.hpp"
#include "snake.hpp"
#include <random>

namespace agent {

float Agent::estimate(snake::GameState game) {
  // check for terminal state
  auto snake = *game.snake;
  auto food = game.food;
  if (snake.eats(food))
    return 1.0;
  if (snake.check_game_over())
    return 0;
  auto board = game.to_string();
  if (!this->lookup.contains(board)) {
    this->lookup[board] = 1.f / 3.f;
  }
  return this->lookup[board];
}

Agent::Agent(snake::GameState *game) : gameState(game) {
  dist = (gameState->snake->body[0] - gameState->food->pos).squared_norm();

  this->predict = [game, this]() {
    std::shared_ptr<snake::Snake> sneks[4] = {
        std::make_shared<snake::Snake>(*game->snake),
        std::make_shared<snake::Snake>(*game->snake),
        std::make_shared<snake::Snake>(*game->snake),
        std::make_shared<snake::Snake>(*game->snake)};
    snake::Direction directions[] = {snake::Left, snake::Right, snake::Up,
                                     snake::Down};
    uint8_t i = 0;
    for (auto dir : directions) {
      sneks[i++]->move(dir);
    }
    auto food = game->food;
    i = 0;
    std::vector<float> probabilities;
    for (auto snek : sneks) {
      probabilities.push_back(estimate(snake::GameState(snek, food)));
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::discrete_distribution<> d(probabilities.begin(), probabilities.end());
    return directions[d(gen)];
  };

  this->update = [this]() {
    auto current_dist =
        (gameState->snake->body[0] - gameState->food->pos).squared_norm();
    auto q_old = lookup[gameState->to_string()];
    auto snake = *this->gameState->snake;
    float reward = 0;
    if (this->gameState->snake->check_game_over())
      reward = -1;
    if (snake.eats(gameState->food))
      reward = 1;
    if (current_dist < dist) {
      reward += 0.1;
    }
    this->lookup[this->gameState->to_string()] =
        (1 - learning_rate) * q_old + learning_rate * reward;
    dist = current_dist;
  };
}
} // namespace agent
