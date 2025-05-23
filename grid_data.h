#ifndef GRID_DATA_H
#define GRID_DATA_H

#include <vector>

// структура для зберіщення даних сітки
struct GridData {
    std::vector<std::vector<int>> grid;
    int size;
    GridData(std::vector<std::vector<int>> g);
};

// набір тестових сіток різного розміру
extern std::vector<GridData> grids;

#endif
