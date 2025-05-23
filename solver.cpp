#include "solver.h"
#include <utility>

// реалізація CellInfo
CellInfo::CellInfo(int r, int c, int n)
    : row(r), col(c), num(n), remaining(n) {}

// рахуємо поточну кількість ліній
int number_of_existing_lines(int row, int col) {
    int current_count = 0, required_count = grid[row][col];
    // перевіряємо лінії вверх
    if (row > 0 && solution[row - 1][col] == '|') {
        if (++current_count >= required_count) return required_count;
        for (int r = row - 2; r >= 0 && solution[r][col] == '|'; --r)
            if (++current_count >= required_count) return required_count;
    }
    // перевіряємо лінії вниз
    if (current_count < required_count && row + 1 < grid_size && solution[row + 1][col] == '|') {
        if (++current_count >= required_count) return required_count;
        for (int r = row + 2; r < grid_size && solution[r][col] == '|'; ++r)
            if (++current_count >= required_count) return required_count;
    }
    // вправо
    if (current_count < required_count && col + 1 < grid_size && solution[row][col + 1] == '-') {
        if (++current_count >= required_count) return required_count;
        for (int c = col + 2; c < grid_size && solution[row][c] == '-'; ++c)
            if (++current_count >= required_count) return required_count;
    }
    // вліво
    if (current_count < required_count && col > 0 && solution[row][col - 1] == '-') {
        if (++current_count >= required_count) return required_count;
        for (int c = col - 2; c >= 0 && solution[row][c] == '-'; --c)
            if (++current_count >= required_count) return required_count;
    }
    return current_count;
}

// розміщуємо або видаляємо лінію
void line_placement(int row, int col, int delta_row, int delta_col, int line_length, bool place) {
    char symbol = (delta_row == 0) ? '-' : '|';
    for (int i = 1; i <= line_length; ++i) {
        int r = row + delta_row * i;
        int c = col + delta_col * i;
        coverage[r][c] = place ? 1 : 0;
        solution[r][c] = place ? symbol : '.';
    }
}

// перевіряємо чи можна поставити лінію
bool possibility_to_place_line(int row, int col, int delta_row, int delta_col, int line_length) {
    int current_lines = number_of_existing_lines(row, col);
    if (current_lines + line_length > grid[row][col]) return false;
    std::vector<std::pair<int,int>> affected;
    for (int i = 1; i <= line_length; ++i) {
        int r = row + delta_row * i;
        int c = col + delta_col * i;
        if (r < 0 || r >= grid_size || c < 0 || c >= grid_size) return false;
        if (coverage[r][c] || grid[r][c] > 0) return false;
        if (delta_row == 0) {
            if (r>0 && grid[r-1][c]>0) affected.emplace_back(r-1,c);
            if (r<grid_size-1 && grid[r+1][c]>0) affected.emplace_back(r+1,c);
        } else {
            if (c>0 && grid[r][c-1]>0) affected.emplace_back(r,c-1);
            if (c<grid_size-1 && grid[r][c+1]>0) affected.emplace_back(r,c+1);
        }
    }
    line_placement(row,col,delta_row,delta_col,line_length,true);
    bool valid = true;
    for (auto &p : affected)
        if (number_of_existing_lines(p.first,p.second) > grid[p.first][p.second]) { valid = false; break; }
    line_placement(row,col,delta_row,delta_col,line_length,false);
    return valid;
}

// перевіряємо кінцевий розв'язок
bool check_final_solution() {
    for (int r = 0; r < grid_size; ++r)
        for (int c = 0; c < grid_size; ++c) {
            if (grid[r][c] > 0) {
                int count = 0;
                // вверх
                if (r>0 && solution[r-1][c]=='|') { count++; int rr=r-2; while(rr>=0 && solution[rr][c]=='|'){count++; rr--;}};
                // вниз
                if (r<grid_size-1 && solution[r+1][c]=='|') { count++; int rr=r+2; while(rr<grid_size && solution[rr][c]=='|'){count++; rr++;}};
                // вліво
                if (c>0 && solution[r][c-1]=='-') { count++; int cc=c-2; while(cc>=0 && solution[r][cc]=='-'){count++; cc--;}};
                // вправо
                if (c<grid_size-1 && solution[r][c+1]=='-') { count++; int cc=c+2; while(cc<grid_size && solution[r][cc]=='-'){count++; cc++;}};
                if (count != grid[r][c]) return false;
            }
        }
    return true;
}

// рекурсивне рішення головоломки
bool solve_puzzle(std::vector<CellInfo>& cells, int pos) {
    if (pos >= (int)cells.size()) return check_final_solution();
    auto &cell = cells[pos];
    int existing = number_of_existing_lines(cell.row, cell.col);
    if (existing > cell.num) return false;
    if (existing == cell.num) return solve_puzzle(cells, pos+1);
    int needed = cell.num - existing;
    static const std::vector<std::pair<int,int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    for (auto [dr,dc] : dirs) {
        for (int len=1; len<=needed; ++len) {
            if (possibility_to_place_line(cell.row,cell.col,dr,dc,len)) {
                line_placement(cell.row,cell.col,dr,dc,len,true);
                if (solve_puzzle(cells,pos)) return true;
                line_placement(cell.row,cell.col,dr,dc,len,false);
            }
        }
    }
    return false;
}