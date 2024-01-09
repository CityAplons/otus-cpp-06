#include <iostream>

#include "project.h"

int main(int argc, char const* argv[])
{
  struct ProjectInfo info = {};

  std::cout << info.nameString << "\t" << info.versionString << '\n';

  Matrix<int, -1> matrix;
  assert(matrix.size() == 0);

  auto a = matrix[0][0];
  assert(a == -1);
  assert(matrix.size() == 0);
  matrix[100][100] = 314;
  assert(matrix[100][100] == 314);
  assert(matrix.size() == 1);
  
  // выведется одна строка
  // 100100314
  for (auto c : matrix)
  {
    int x;
    int y;
    int v;
    std::tie(x, y, v) = c;
    std::cout << x << y << v << std::endl;
  }

  (void)argc;
  (void)argv;
  return 0;
}
