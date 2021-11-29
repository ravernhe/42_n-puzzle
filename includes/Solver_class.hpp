#ifndef __SOLVER_CLASS_HPP
# define __SOLVER_CLASS_HPP

struct node {
    int **grid; int heuristic;
    node *parent;
};

class Solver
{
private:
    int **_grid;
    int **_soluce_grid;
    int _puzzle_size;

public:
    Solver(int **grid, int puzzle_size);
    ~Solver();
    void solve();
    void soluce_grid();
    int manhattan_heuristic(int **grid);
    // int **move(int **grid, int i);
    // int can_move(int **grid, int i);
    // void print_grid(int **grid);
    // void cpy_grid(int **grid, int **cpy);
};

#endif