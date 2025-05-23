#include <iostream>
#include <vector>
#include <algorithm>
#include "grid_data.h"
#include "puzzle_state.h"
#include "solver.h"
#include "printer.h"

using namespace std;

int main() {
    while (true) {
        cout << "Select grid (1-" << grids.size() << ") or 0 to exit:\n";
        int choice; cin >> choice;
        if (choice == 0) break;
        if (choice < 1 || choice > (int)grids.size()) {
            cout << "Invalid choice, please try again.\n";
            continue;
        }
        // ініціалізація
        grid = grids[choice-1].grid;
        grid_size = grids[choice-1].size;
        coverage.assign(grid_size, vector<int>(grid_size, 0));
        solution.assign(grid_size, vector<char>(grid_size, '.'));

        cout << "Solving...\n";
        vector<CellInfo> cells;
        for (int r = 0; r < grid_size; ++r)
            for (int c = 0; c < grid_size; ++c)
                if (grid[r][c] > 0)
                    cells.emplace_back(r, c, grid[r][c]);

        sort(cells.begin(), cells.end(), [](auto &a, auto &b) { return a.num > b.num; });

        if (solve_puzzle(cells, 0)) {
            cout << "Solution found!\n";
            print_state();
        } else {
            cout << "No solution exists!\n";
        }
        cout << "\n";
    }
    return 0;
}
