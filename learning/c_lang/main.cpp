#include "agent.hpp"
#include "graph_agent.hpp"
#include "snake.hpp"
#include <iostream>
#include <memory>

std::shared_ptr<snake::Snake> snek;

snake::Direction simple_agent() {
  static snake::Direction vel = snake::Left;

  if (snek->body[0].x >= (680 - 5) / 10) {
    vel = snake::Left;
  } else if (snek->body[0].x <= 0) {
    vel = snake::Right;
  }
  return vel;
}

int main(void) {
  std::cout << "Snake\n";
  snake::GameState game;
  auto agent = agent::Agent(&game);
  auto graph_agent = graph_agent::GraphAgent(&game);
  snek = game.snake;
  snek->set_agent(graph_agent.predict, graph_agent.update);
  snake::draw(game);
  return 0;
}
