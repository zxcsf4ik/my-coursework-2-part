#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H

#include <vector>

// глобальні змінні для роботи з сіткою
extern std::vector<std::vector<int>> grid;
extern std::vector<std::vector<int>> coverage;
extern std::vector<std::vector<char>> solution;
extern int grid_size;

#endif
