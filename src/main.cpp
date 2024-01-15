#include <cassert>
#include <iostream>

#include "matrix.hpp"
#include "project.h"

int
main(int argc, char const *argv[]) {
    struct ProjectInfo info = {};
    std::cout << info.nameString << "\t" << info.versionString << '\n';

    using namespace otus;
    Matrix<int, 0> matrix;

    // заполнить главную диагональ матрицы (от [0,0] до [9,9]) значениями от 0
    // до 9.
    for (size_t i = 1; i <= 9; ++i) {
        matrix[i][i] = i;
    }

    // Второстепенную диагональ (от [0,9] до [9,0]) значениями от 9 до 0.
    for (size_t i = 1; i <= 9; ++i) {
        matrix[i][9 - i] = 9 - i;
    }

    //  вывести фрагмент матрицы от [1,1] до [8,8]
    for (size_t i = 1; i < 9; ++i) {
        for (size_t j = 1; j < 9; ++j) {
            std::cout << matrix[i][j] << ' ';
        }

        std::cout << '\n';
    }

    // Вывести количество занятых ячеек
    std::cout << matrix.size() << '\n';

    // Вывести все занятые ячейки вместе со своими позициями.
    for (auto &&element : matrix) {
        int x, y, value;
        std::tie(x, y, value) = element;
        std::cout << x << '\t' << y << '\t' << value << '\n';
    }

    // Опционально реализовать каноническую форму оператора `=`
    ((matrix[100][100] = 314) = 0) = 217;
    std::cout << matrix[100][100] << std::endl;

    (void) argc;
    (void) argv;
    return 0;
}
