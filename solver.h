#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "puzzle_state.h"

// структура для зберігання інформації про клітинку з числом
struct CellInfo {
    int row, col, num, remaining;
    CellInfo(int r, int c, int n);
};

int number_of_existing_lines(int row, int col);
void line_placement(int row, int col, int delta_row, int delta_col, int line_length, bool place);
bool possibility_to_place_line(int row, int col, int delta_row, int delta_col, int line_length);
bool check_final_solution();
bool solve_puzzle(std::vector<CellInfo>& cells, int cell_position);

#endif