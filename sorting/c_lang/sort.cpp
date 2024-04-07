#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <ranges>

constexpr unsigned int MAX = 100;
constexpr unsigned int INPUT_LENGTH = 1000;

std::vector<int> merge_sort(const std::vector<int>& array);
std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right);
std::vector<int> make_random_vec(int length);
void display(std::vector<int> vec);

void display(std::vector<int> vec) {
  std::cout << "{ ";
  for (auto e : vec) {
    std::cout << e << " "; 
  }
  std::cout << "}\n";
}

std::vector<int> make_random_vec(int length) {
  std::vector<int> result;
  result.reserve(length);
  for (auto __attribute__((unused)) i: std::ranges::views::iota(0, length)) {
    result.push_back(rand() % MAX);
  } 
  return result;
}

void test(std::vector<int> (*algorithm)(const std::vector<int>&)) {
  auto v = make_random_vec(INPUT_LENGTH);
  std::cout << "Unsorted:\n";
  display(v);
  v = algorithm(v);
  std::cout << "Sorted:\n";
  display(v);
}

int main(void) {
  srand(time(NULL));
  test(merge_sort);
  return 0;
}

std::vector<int> merge_sort(const std::vector<int>& array) {
  int n = array.size();
  if (n <= 1) {
    return std::vector<int>(array.begin(), array.end());
  }
  std::vector<int> left(array.begin(), array.begin() + (n+1)/2);
  std::vector<int> right(array.begin() + (n+1)/2, array.end());
  left = merge_sort(left);
  right = merge_sort(right);
  return merge(left, right);
}

std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
  int n = left.size() + right.size();
  std::vector<int> merged;
  merged.reserve(n);
  unsigned int i = 0, j = 0;
  for (int k = 0; k < n; ++k) {
    if (j >= right.size() || (i < left.size() && left[i] < right[j])) {
      merged.push_back(left[i++]);
    }
    else {
      merged.push_back(right[j++]);
    }
  }
  return merged;
}
