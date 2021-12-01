#ifndef __SOLVER_CLASS_HPP
# define __SOLVER_CLASS_HPP

struct node {
    int **grid;
    int     heuristic;
    int     cost;
    node    *parent;
};

class Solver
{
private:
    int         **_grid;
    int         **_soluce_grid;
    int         _puzzle_size;
    struct node _Base;

public:
    Solver(int **grid, int puzzle_size);
    ~Solver();
    int    solve();
    void    soluce_grid();
    int     manhattan_heuristic(int **grid);
    node    get_next_grid(std::vector<node> opened, int *index);
    int     is_opened_and_close(std::vector<node> opened, std::vector<node> closed, node current_move);
    int     is_close(std::vector<node> closed, node current_move, int *c);
    bool    move(int mov, node *next_move);
    void print_grid(int **grid);
    // void cpy_grid(int **grid, int **cpy);
};

#endif