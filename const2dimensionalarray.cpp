#include <array>

int main(void)
{
  const std::array<std::array<int, 4>, 4> matrix {std::array<int, 4>{0,0,0,0},
                                                  std::array<int, 4>{1,1,1,1},
                                                  std::array<int, 4>{2,2,2,2},
                                                  std::array<int, 4>{3,3,3,3}};

  // std::array<int, 4> & row0 = matrix[0]; // compile error
  const std::array<int, 4> & row0 = matrix[0];

  // int & pos0_0 = row0[0]; //compile error
  const int & pos0_0 = row0[0];

  // pos0_0 = 5; //compile error

  int copy_of_pos0_0 = row0[0];
  copy_of_pos0_0 = 5;

  // matrix[0][0] = 5; compile error
  
  return 0;
}
