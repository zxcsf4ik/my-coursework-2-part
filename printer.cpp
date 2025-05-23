
#include "printer.h"
#include "puzzle_state.h"
#include <iostream>

void print_state() {
    std::cout << "\nFinal solution:\n";
    for (int r = 0; r < grid_size; ++r) {
        for (int c = 0; c < grid_size; ++c) {
            if (grid[r][c] > 0)
                std::cout << grid[r][c] << " ";
            else
                std::cout << solution[r][c] << " ";
        }
        std::cout << "\n";
    }
}
