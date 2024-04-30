#include "snake.hpp"
#include <cassert>
#include <functional>

#define WIDTH 680
#define HEIGHT 490
#define SNAKESIZE 10
#define XMARGIN 5
#define YMARGIN 5

#define STARTPOS                                                               \
  { Point(0, 4), Point(0, 3), Point(0, 2) }

namespace snake {
void handle_events(bool &);
std::function<void(void)> update_agent;

GameState::GameState()
    : width((WIDTH - 5) / SNAKESIZE), height((HEIGHT - 5) / SNAKESIZE) {
  std::cout << "Width: " << width << ", Height: " << height << "\n";
  this->snake = std::make_shared<Snake>();
  this->food = std::make_shared<Food>();
}

GameState::GameState(std::shared_ptr<Snake> snake, std::shared_ptr<Food> food)
    : snake(snake), food(food), width((WIDTH - 5) / SNAKESIZE),
      height((HEIGHT - 5) / SNAKESIZE) {}

void GameState::reset() {
  score = 0;
  snake->reset();
}

std::string GameState::to_string() {
  std::string board;
  for (int i = 0; i < this->width * this->height; i++) {
    board.append("0");
  }
  // for (auto pos : this->snake->body) {
  //   board[pos.x + (this->width * pos.y)] = '1';
  // }
  board[snake->body[0].x + (this->width * snake->body[0].y)] = '1';
  board[this->food->pos.x + (this->width * this->food->pos.y)] = '2';
  return board;
}

void GameState::display() {
  std::string board = this->to_string();
  for (int j = 0; j < this->height; j++) {
    for (int i = 0; i < this->width; i++) {
      std::cout << board[i + (j * this->width)];
    }
    std::cout << " " << j << "\n";
  }
}

Snake::Snake() { body = STARTPOS; }

void Snake::reset() { body = STARTPOS; }

void Snake::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 200, 10, 255);
  for (auto segment : this->body) {
    SDL_Rect segment_rect = {this->x_margin + segment.x * this->width + 1,
                             this->y_margin + segment.y * this->height + 1,
                             this->width - 1, this->height - 1};
    SDL_RenderFillRect(renderer, &segment_rect);
  }
}

void Snake::set_agent(std::function<Direction()> predict,
                      std::function<void(void)> update) {
  this->next_move = predict;
  update_agent = update;
}

void Snake::move(Direction d) {
  this->body.insert(this->body.begin() + 1, this->body[0]);
  if (!this->grow)
    this->body.pop_back();
  this->dir = d;
  switch (d) {
  case Up:
    this->body[0] = this->body[0] + Point(0, -1);
    break;
  case Down:
    this->body[0] = this->body[0] + Point(0, 1);
    break;
  case Left:
    this->body[0] = this->body[0] + Point(-1, 0);
    break;
  case Right:
    this->body[0] = this->body[0] + Point(1, 0);
    break;
  default:
    this->dir = Left;
    this->body[0] = this->body[0] + Point(-1, 0);
    break;
  }
}

bool Snake::check_game_over() {
  std::map<std::string, bool> seen;
  for (auto p : this->body) {
    if (p.x < 0 || p.x > (WIDTH - XMARGIN) / SNAKESIZE - 1 || p.y < 0 ||
        p.y > (HEIGHT - YMARGIN) / SNAKESIZE - 1)
      return true;
    auto key = std::to_string(p.x) + std::to_string(p.y);
    if (seen.contains(key))
      return true;
    seen[key] = true;
  }
  return false;
}

bool Snake::eats(const std::shared_ptr<Food> food) {
  this->grow = this->body[0] == food->pos;
  return this->grow;
}

Food::Food() {
  static int init = 0;
  if (!init) {
    srand(time(NULL));
    init = 1;
  }
  pos = Point(rand() % (WIDTH - XMARGIN) / SNAKESIZE,
              rand() % ((HEIGHT - YMARGIN) / SNAKESIZE));
}

void Food::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect rect = {XMARGIN + pos.x * SNAKESIZE + 1,
                   YMARGIN + pos.y * SNAKESIZE + 1, SNAKESIZE - 1,
                   SNAKESIZE - 1};

  SDL_RenderFillRect(renderer, &rect);
}

void Food::new_pos() {
  this->pos = Point(rand() % (WIDTH - XMARGIN) / SNAKESIZE,
                    rand() % ((HEIGHT - YMARGIN) / SNAKESIZE));
}

int draw(GameState &game) {
  constexpr int dim = ((WIDTH - 5) * (HEIGHT - 5)) / (SNAKESIZE * SNAKESIZE);
  std::cout << "Width: " << (WIDTH - 5) / SNAKESIZE << "\n";
  std::cout << "Height: " << (HEIGHT - 5) / SNAKESIZE << "\n";
  std::cout << "Dim: " << dim << "\n";
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to init SDL2!\n";
    return -1;
  }

  SDL_Window *window =
      SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WIDTH, HEIGHT, 0);
  if (!window) {
    std::cout << "Failed to create window!\n";
    return -1;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);

  if (!renderer) {
    std::cout << "Failed to get window surface!\n";
    return -1;
  }
  bool running = true;

  auto snake = game.snake;
  auto food = game.food;
  std::cout << snake->body[0] << "\n";

  food->pos.x = 50;
  food->pos.y = 5;

  while (running) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    handle_events(running);
    snake->move(snake->next_move());

    if (snake->check_game_over()) {
      std::cout << snake->body[0] << "\n";
      std::cout << "GameOver\n";
      game.reset();
    }
    if (snake->eats(food)) {
      game.score++;
      food->new_pos();
    }
    update_agent();

    snake->draw(renderer);
    food->render(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }
  return 0;
}

void handle_events(bool &running) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYUP:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        running = false;
      }
      break;
    }
  }
}
} // namespace snake
