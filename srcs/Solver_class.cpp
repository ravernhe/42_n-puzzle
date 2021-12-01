#include "../includes/npuzzle.hpp"
#include <vector>

Solver::Solver(int **grid, int puzzle_size)
{
    _grid = grid;
    _puzzle_size = puzzle_size;
    soluce_grid();
    _Base = (node){_grid, manhattan_heuristic(_grid), 0, NULL};
    solve();
}

Solver::~Solver()
{
        for(int i = 0; i < _puzzle_size; ++i) {
        delete[] _soluce_grid[i];
    }
    delete[] _soluce_grid;
}

node Solver::get_next_grid(std::vector<node> opened, int *index) { // Opti F && H
    // int f_expect;
    // int **grid_ret;
    node cmp;
    cmp = opened.front();

    for (std::vector<node>::iterator elem = opened.begin(); elem < opened.end(); elem++){
        if (elem->heuristic < cmp.heuristic) {
            cmp = (node){elem->grid,elem->heuristic,elem->cost,elem->parent};
        }
        *index = *index + 1;
    }
    return cmp;
}

bool is_grid(node current, int ** grid){
    return (current.grid == grid);
}

int Solver::is_opened_and_close(std::vector<node> opened, std::vector<node> closed, node current_move) {
    unsigned int size = opened.size();
    unsigned int c = -1;
    int tok = 0;

    while (++c < size && tok == 0) {
    if (opened[c].grid == current_move.grid)
        tok++;
    }
    size = closed.size();
    c = -1;
    int cpy = tok;
    while (++c < size && tok == cpy) {
    if (closed[c].grid == current_move.grid)
        cpy++;
    }
    if (cpy == 2)
        return 0;
    return 1;
}

int Solver::is_close(std::vector<node> closed, node current_move, int *c) {
    unsigned int size = closed.size();
    int tok = 0;

    while (*c < size && tok == 0) {
        if (closed[*c].grid == current_move.grid)
            tok++;
        *c = *c + 1;
    }
    if (tok == 1)
        return 0;
    return 1;
}

int    Solver::solve(){
    // struct node 
    // int **tmp;
    int     g = 0, f = 0, index = 0, c;
    bool    succes = false;
    node    e_grid;
    node current_move;

    std::vector<node>    opened;
    std::vector<node>    closed;

    opened.push_back(_Base);
    f = opened.front().cost + opened.front().heuristic;
    while (!opened.empty() && !succes) {
        e_grid = get_next_grid(opened, &index); // Lowest F opened &7 Get int *Index in opened
        print_grid(e_grid);
        printf("Flemme de debug\n");
        if (e_grid.grid == _soluce_grid) {
           succes = true;
        }
        else {
            opened.erase(opened.begin() + index); // Index of e in opened
            closed.push_back(e_grid);

            for (int i = 0; i < 4; i++) {
                // if move actually move
                current_move = e_grid;
                current_move.parent = &e_grid;
                current_move.cost += 1;
                if (move(i, &current_move)) {

                    if (is_opened_and_close(opened, closed, current_move) == 0) {
                        opened.push_back(current_move);
                    }
                }
                else {
                    if (f > current_move.heuristic + current_move.cost) {
                        f = current_move.heuristic + current_move.cost;
                        opened.push_back(current_move); // ? Here we had node
                        c = 0;
                        if (is_close(closed, current_move, &c) == 0) {
                            closed.erase(closed.begin() + c); // index current_move
                            opened.push_back(current_move); 
                        }
                    }
                }
        }

    }
    }
    if (succes)
        return 1;
    return 0;

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

void Solver::soluce_grid(){
    _soluce_grid = new int*[_puzzle_size];
    for(int i = 0; i < _puzzle_size; ++i) {
        _soluce_grid[i] = new int[_puzzle_size];
    }

    int w = 0, h = 0, i = 1, loop = 0;
    while (i < _puzzle_size * _puzzle_size) {
        while (w < _puzzle_size - 1 - loop) {
            _soluce_grid[h][w] = i;
            w++;
            i++;
        }
        while (h < _puzzle_size - 1 - loop) {
            _soluce_grid[h][w] = i;
            h++;
            i++;
        }
        while (w > _puzzle_size - _puzzle_size + loop) {
            _soluce_grid[h][w] = i;
            w--;
            i++;
        }
        loop++;
        while (h > _puzzle_size - _puzzle_size + loop) {
            _soluce_grid[h][w] = i;
            h--;
            i++;
        }
    }
    _soluce_grid[h][w] = 0;
}



bool    Solver::move(int mov, node *next_move){
    int j = 0, i = 0, token = 0; // Function get_empty ?
    while (++i < _puzzle_size && token == 0){
        j = 0;
        while (++j < _puzzle_size){
            if (next_move->grid[i][j] == 0){
                token = 1;
            }  
        }
    }
    // En vrai ouais
    if (mov == 0) { // Up
        printf("Up\n");
        if (i - 1 < 0)
            return true;
        next_move->grid[i][j] = next_move->grid[i - 1][j];
        next_move->grid[i - 1][j] = 0;
    }
    if (mov == 1) { // Down
        printf("Down\n");
        if (i + 1 >= _puzzle_size)
            return true;
        next_move->grid[i][j] = next_move->grid[i + 1][j];
        next_move->grid[i + 1][j] = 0;
    }
    if (mov == 2) { // Left
        printf("Left\n");
        if (j - 1 < 0)
            return true;
        next_move->grid[i][j] = next_move->grid[i][j- 1];
        next_move->grid[i][j- 1] = 0;
    }
    if (mov == 3) { // Right
        printf("Right\n");
        if (j + 1 >= _puzzle_size)
            return true;
        next_move->grid[i][j] = next_move->grid[i][j + 1];
        next_move->grid[i][j + 1] = 0;
    }
    return false;
}

void Solver::print_grid(int **grid){
    int i = 0;
    int j;
    while (i < _puzzle_size){
        j = 0;
        while (j < _puzzle_size){
            std::cout << grid[i][j] << " ";
            j++;
        }
        std::cout << "\n";
        i++;
    }
    std::cout << "\n";
}

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