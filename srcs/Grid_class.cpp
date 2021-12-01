#include "../includes/npuzzle.hpp"

Grid::Grid(int size, int **grid)
{
    _puzzle_size = size;
    create();
    if (grid){ // Si grid non vide on cpy
        cpy_grid(grid);
    }
}

Grid::~Grid()
{
}

void    Grid::create(){
    _grid = new int*[_puzzle_size];
    for(int i = 0; i < _puzzle_size; ++i) {
        _grid[i] = new int[_puzzle_size];
    }
}

void    Grid::print_grid(){
    int i = 0;
    int j;
    while (i < _puzzle_size){
        j = 0;
        while (j < _puzzle_size){
            std::cout << _grid[i][j] << " ";
            j++;
        }
        std::cout << "\n";
        i++;
    }
    std::cout << "\n";
}

// Fonction Get_empty -> make_all move and if k save

int    Grid::move_grid(int mov){
    int j = 0, i = 0, token = 0; // Function get_empty ?
    while (++i < _puzzle_size && token == 0){
        j = 0;
        while (++j < _puzzle_size){
            if (_grid[i][j] == 0){
                token = 1;
            }  
        }
    }
    if (mov == 0) { // Up
        printf("Up\n");
        if (i - 1 < 0)
            return 1;
        _grid[i][j] = _grid[i - 1][j];
        _grid[i - 1][j] = 0;
    }
    if (mov == 1) { // Down
        printf("Down\n");
        if (i + 1 >= _puzzle_size)
            return 1;
        _grid[i][j] = _grid[i + 1][j];
        _grid[i + 1][j] = 0;
    }
    if (mov == 2) { // Left
        printf("Left\n");
        if (j - 1 < 0)
            return 1;
        _grid[i][j] = _grid[i][j- 1];
        _grid[i][j- 1] = 0;
    }
    if (mov == 3) { // Right
        printf("Right\n");
        if (j + 1 >= _puzzle_size)
            return 1;
        _grid[i][j] = _grid[i][j + 1];
        _grid[i][j + 1] = 0;
    }
    return 0;
}

void    Grid::cpy_grid(int **initial_grid){
    int i = 0;
    int j;

    while (i < _puzzle_size){
        j = 0;
        while (j < _puzzle_size){
            _grid[i][j] = initial_grid[i][j];
            j++;
        }
        i++;
    }
}

int     Grid::get_puzzle_size(){
    return(_puzzle_size);
}

int     **Grid::get_grid(){
    return(_grid);
}