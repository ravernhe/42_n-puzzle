#ifndef __SOLVER_CLASS_HPP
# define __SOLVER_CLASS_HPP

#include <functional>
#include <queue>
#include <vector>
#include <set>

struct Node {
    int     **grid;
    int     heuristic;
    int     cost;
    struct  Node    *parent;

    Node(int **_grid, int _heuristic, int _cost, struct  Node *_parent)
    {
        grid = _grid;
        heuristic = _heuristic;
        cost = _cost;
        parent = _parent;
    }
};

struct CompareWeight {
    bool operator()(struct Node * w1, struct Node * w2)
    {
        return w1->heuristic + w1->cost > w2->heuristic + w2->cost;
    }
};

class Solver
{
private:
    int         **_grid;
    int         **_cpy;
    int         **_soluce_grid;
    int         _puzzle_size;
    // struct Node _Base;

public:
    Solver(int **grid, int puzzle_size);
    ~Solver();
    int    solve();
    void    soluce_grid();
    bool    is_solvable();
    int     manhattan_heuristic(int **grid);
    int     linear_conflict(int **grid);
    int     find_empty(int **grid);
    // node    get_next_grid(std::vector<node> opened, int *index);
    // int     is_not_opened_or_close(std::vector<node> opened, std::vector<node> closed, node current_move);
    // int     is_close(std::vector<node> closed, node current_move, int *c);
    int     move(int mov, int **src, int **dest, int zero);
    void    print_grid(int **grid);
    void    cpy_grid(int **src, int **dest);
    // int     cmp_grid(int **grid, int **grid2);
    // bool    is_solvable();
};

#endif