#include "../includes/npuzzle.hpp"
#include <vector>

Solver::Solver(int **grid, int puzzle_size)
{
    _grid = grid;
    // print_grid(grid);
    _puzzle_size = puzzle_size;
    soluce_grid();
}

Solver::~Solver()
{
}

void Solver::solve(){
    struct node Base = {_grid, manhattan_heuristic(_grid), NULL};
    int **tmp;
    int g = 0;
    int f = 0;
    int index = 0;
    std::vector<node> queue;
    queue.push_back(Base);

    while (!queue.empty()) {
        std::vector<node> first = queue;
        f = g + first.front().heuristic;

        for (std::vector<node>::iterator elem = first.begin(); elem < first.end(); elem++){
            if (elem->heuristic == 0) {std::cout << "Soluce" << std::endl;return ;}
            print_grid(elem->grid);
            for (int i = 0; i < 4; i++) {
                if (can_move(elem->grid, i)) {
                    tmp = elem->grid;
                    tmp = move(tmp, i);
                    struct node New = {tmp, manhattan_heuristic(tmp), &queue.front()};
                    queue.push_back(New);
                }
            }
            queue.erase(queue.begin());
        }
        g++;
        index = 0;
        // for (std::vector<node>::iterator elem = queue.begin(); elem < queue.end(); elem++){
        //     std::cout << elem->heuristic<< std::endl;
        // }

        for (std::vector<node>::iterator elem = queue.begin(); elem < queue.end(); elem++){
            if (f < elem->heuristic + g)
                queue.erase(queue.begin() + index);
            else {
                f = elem->heuristic + g;
                // elem = queue.begin();
            }
            index++;
        }
        for (std::vector<node>::iterator elem = queue.begin(); elem < queue.end(); elem++){
            // print_grid(elem->grid);
            // std::cout << elem->grid<< std::endl;
        }
        break ;
    }

}

int Solver::manhattan_heuristic(int **grid){ // Opti
    int heuristic = 0;

    for(int i = 0; i < _puzzle_size; ++i) {
        for(int j = 0; j < _puzzle_size; ++j) {
            for(int y = 0; y < _puzzle_size; ++y) {
                for(int x = 0; x < _puzzle_size; ++x) {
                    if (grid[i][j] == _soluce_grid[y][x] && grid[i][j] != 0) {
                        heuristic += abs(i - y) + abs(j - x);
                    }   
                }
            }
        }
    }
    return (heuristic);
}
void Solver::soluce_grid(){ // A FAIRE PLUS TARD
    _soluce_grid = new int*[_puzzle_size];
    for(int i = 0; i < _puzzle_size; ++i) {
        _soluce_grid[i] = new int[_puzzle_size];
    }
    // 3 * 3
    _soluce_grid[0][0] = 1;
    _soluce_grid[0][1] = 2;
    _soluce_grid[0][2] = 3;

    _soluce_grid[1][0] = 8;
    _soluce_grid[1][1] = 0;
    _soluce_grid[1][2] = 4;

    _soluce_grid[2][0] = 7;
    _soluce_grid[2][1] = 6;
    _soluce_grid[2][2] = 5;
    // int w = 0, h = 0;
    // for (int i = 0; i < _puzzle_size * _puzzle_size - 1; i++) {}
}

// int **Solver::move(int **grid, int mov){ // MERGE CAN_MOVE AND MOVE
//     int j = 0, i = 0, token = 0;
//     while (++i < _puzzle_size && token == 0){
//         j = 0;
//         while (++j < _puzzle_size){
//             if (grid[i][j] == 0){
//                 token = 1;
//             }  
//         }
//     }
//     if (mov == 0) { // Up
//         printf("Up\n");
//         grid[i][j] = grid[i - 1][j];
//         grid[i - 1][j] = 0;
//     }
//     if (mov == 1) { // Down
//         printf("Down\n");
//         grid[i][j] = grid[i + 1][j];
//         grid[i + 1][j] = 0;
//     }
//     if (mov == 2) { // Left
//         printf("Left\n");
//         grid[i][j] = grid[i][j- 1];
//         grid[i][j- 1] = 0;
//     }
//     if (mov == 3) { // Right
//         printf("Right\n");
//         grid[i][j] = grid[i][j + 1];
//         grid[i][j + 1] = 0;
//     }
//     return grid;
// }

// int Solver::can_move(int **grid, int mov){
//     int j = 0, i = 0, token = 0;
//     while (++i < _puzzle_size && token == 0){
//         j = 0;
//         while (++j < _puzzle_size){
//             if (grid[i][j] == 0){
//                 token = 1;
//             }  
//         }
//     }
//     printf("coord i,j : %d,%d -> ", i, j);
//     std::cout << grid[i][j] << std::endl;
//     if (mov == 0) { // Up
//         if (i - 1 < 0)
//             return 0;
//     }
//     if (mov == 1) { // Down
//         if (i + 1 >= _puzzle_size)
//             // std::cout << "i = " << i << ", puzzleSize = " << _puzzle_size << std::endl;
//             return 0;
//     }
//     if (mov == 2) { // Left
//         if (j - 1 < 0){
//             return 0;
//         }
//     }
//     if (mov == 3) { // Right
//         if (j + 1 >= _puzzle_size)
//             return 0;
//     }
//     return 1;
// }

// void Solver::print_grid(int **grid){
//     int i = 0;
//     int j;
//     while (i < _puzzle_size){
//         j = 0;
//         while (j < _puzzle_size){
//             std::cout << grid[i][j] << " ";
//             j++;
//         }
//         std::cout << "\n";
//         i++;
//     }
//     std::cout << "\n";
// }

// void Solver::cpy_grid(int **grid, int **cpy){
//     int i = 0;
//     int j;

//     while (i < _puzzle_size){
//         j = 0;
//         while (j < _puzzle_size){
//             cpy[i][j] = grid[i][j];
//             j++;
//         }
//         i++;
//     }
// }