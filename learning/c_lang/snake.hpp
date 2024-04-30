#pragma once
#include "primitives.hpp"
#include <SDL2/SDL.h>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <time.h>
#include <vector>

namespace snake {
enum Direction { Up, Down, Left, Right };

class Food {
public:
  Food(void);
  Point pos;
  void render(SDL_Renderer *);
  void new_pos(void);
};

class Snake {
public:
  Snake(void);

  void draw(SDL_Renderer *renderer);
  void move(Direction d);
  bool check_game_over(void);
  bool eats(const std::shared_ptr<Food> food);
  void set_agent(std::function<Direction(void)>, std::function<void(void)>);
  void reset();

  Direction dir;
  std::vector<Point> body;
  std::function<Direction()> next_move;

private:
  bool grow;
  static constexpr int x_margin = 5;
  static constexpr int y_margin = 5;
  static constexpr int width = 10;
  static constexpr int height = 10;
};

class GameState {
public:
  GameState(void);
  GameState(std::shared_ptr<Snake>, std::shared_ptr<Food>);
  std::shared_ptr<Snake> snake;
  std::shared_ptr<Food> food;
  const int width;
  const int height;
  uint score = 0;

  void reset();
  std::string to_string(void);
  void display(void);
};

int draw(GameState &game);

} // namespace snake
