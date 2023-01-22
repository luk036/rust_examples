// file: hello.cpp
// Compile with:
// $ g++ -std=c++17 hello.cpp -lfmt

#include <array>
#include <fmt/ranges.h>

int main() {
  auto arr = std::array{2, 3, 5}; // c++17
  fmt::print("答案是 {}.\n", arr);
}
