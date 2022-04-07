#include "../includes/npuzzle.hpp"
#include <vector>
// #include <iomanip>
#include <memory>

Solver::Solver(int **grid, int puzzle_size)
{
    _grid = grid;
    _puzzle_size = puzzle_size;

    soluce_grid();
    // is_solvable();
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
    int count = 0;
    for (std::vector<node>::iterator elem = opened.begin(); elem < opened.end(); elem++){
        if (elem->heuristic + elem->cost  <= cmp.heuristic + cmp.cost) {
            cmp = (node){elem->grid,elem->heuristic,elem->cost,elem->parent};
            *index = count;
        }
        count++;
    }
    return cmp;
}

bool is_grid(node current, int ** grid){
    return (current.grid == grid);
}

// ! LES PROBLEMES
int Solver::is_not_opened_or_close(std::vector<node> opened, std::vector<node> closed, node current_move) {
    unsigned int size = opened.size();
    unsigned int c = -1;
    int tok = 0;

    while (++c < size && tok == 0) {
        if (!cmp_grid(opened[c].grid, current_move.grid))
            tok++;
    }
    size = closed.size();
    c = -1;
    
    int cpy = tok;
    while (++c < size && tok == cpy) {
        if (!cmp_grid(closed[c].grid, current_move.grid))
            cpy++;
    }
    if (cpy == 0)
        return 0;
    return 1;
}

int Solver::is_close(std::vector<node> closed, node current_move, int *c) {
    unsigned int size = closed.size();
    int tok = 0;

    while ((unsigned int)*c < size && tok == 0) {
        if (!cmp_grid(closed[*c].grid, current_move.grid))
            return 0;
        *c = *c + 1;
    }
    return 1;
}

int    Solver::solve(){
    // struct node 
    // int **tmp;
    int     f = 0, index, c;
    bool    succes = false;
    node    e_grid;
    node current_move;

    current_move.grid = nullptr;
    std::vector<node>    opened;
    std::vector<node>    closed;
    opened.push_back(_Base);
    // f = opened.front().cost + opened.front().heuristic;

    int loop = 0;
    while (!opened.empty() && !succes) {
        // printf("Iteration : %d\n", loop);
        index = 0;
        e_grid = get_next_grid(opened, &index); // Lowest F opened &7 Get int *Index in opened
        f = e_grid.cost + e_grid.heuristic;

        if (e_grid.heuristic == 0) {
            print_grid(e_grid.grid);
           succes = true;
        }
        // else if(_Base.heuristic % 2 != _puzzle_size % 2) {
        //     printf("unsolve\n");
        //     exit(0);
        // }
        else {
            opened.erase(opened.begin() + index);
            closed.push_back(e_grid);
            print_grid(e_grid.grid);
            for (int i = 0; i < 4; i++) { // Tmp test
                current_move.grid = cpy_grid(e_grid.grid);
                current_move.parent = &e_grid;
                // printf("Addr : %p\n", &e_grid);
                current_move.cost = e_grid.cost + 1;
                if (move(i, &current_move)) {

                    current_move.heuristic = manhattan_heuristic(current_move.grid);
                    if (is_not_opened_or_close(opened, closed, current_move) == 0) {
                        opened.push_back(current_move);
                    }
                    else {
                        // printf("Weight cmp : %d\n", f);
                        if (f > current_move.heuristic + current_move.cost) {
                            f = current_move.heuristic + current_move.cost;
                            opened.push_back(current_move);
                            c = 0;
                            if (is_close(closed, current_move, &c) == 0) {
                                closed.erase(closed.begin() + c);
                                opened.push_back(current_move); 
                            }
                        }
                    }
                }
            }
        }
        // if (loop == 1000) {
        //     // printf("Opened\n");
        //     // for (std::vector<node>::iterator elem = opened.begin(); elem < opened.end(); elem++){
        //     //     printf("F value : %d\n", elem->heuristic + elem->cost);
        //     //     print_grid(elem->grid);
        //     // }
        //     // printf("f : %d\n", f);
        //     break ;
        // }

        // printf("Opened\n");
        // for (std::vector<node>::iterator elem = opened.begin(); elem < opened.end(); elem++){
        //     printf("F value : %d\n", elem->heuristic + elem->cost);
        //     print_grid(elem->grid);
        // }
        // printf("Closed\n");
        // for (std::vector<node>::iterator elem = closed.begin(); elem < closed.end(); elem++){
        //     printf("F value : %d\n", elem->heuristic + elem->cost);
        //     print_grid(elem->grid);
        // }
        // !
        // if (loop == 50)
        //     exit(0);
        std::cout << loop << std::endl;
        loop++;
        // !
    }
    if (current_move.grid) {
        for(int i = 0; i < _puzzle_size; ++i) {
            delete[] current_move.grid[i];
        }
        delete[] current_move.grid;
    }
    if (e_grid.grid) {
        for(int i = 0; i < _puzzle_size; ++i) {
            delete[] e_grid.grid[i];
        }
        delete[] e_grid.grid;
    }

    if (succes) {        
        // printf("Current : %p - Parent : %p\n", &e_grid, e_grid.parent);
        printf("Win\n");
        return 1;
    }
    printf("Loose\n");
    return 0;

}

int Solver::linear_conflict(int **grid) {
    int nb_conflict = 0;

    // printf("Linear\n"); // ! Bug quelque soit la grille, prob memorie acces
    // printf("Bug : %d /n", _soluce_grid[2][0]);
    // printf("?\n");
    for(int i = 0; i < _puzzle_size; ++i) {
        for(int j = 0; j < _puzzle_size; ++j) {
            if ((j+1 < _puzzle_size && grid[i][j] == _soluce_grid[i][j+1] && grid[i][j+1] == _soluce_grid[i][j]) \
            || (i+1 < _puzzle_size && grid[i][j] == _soluce_grid[i+i][j] && grid[i+1][j] == _soluce_grid[i][j]))
                nb_conflict++;
        }
    }
    return (nb_conflict);
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
    return (heuristic + 2 * linear_conflict(grid));
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
    int j, i = 0, token = 0; // Function get_empty ?
    while (i < _puzzle_size && token == 0){
        j = 0;
        while (j < _puzzle_size && token == 0){
            if (next_move->grid[i][j] == 0){
                token = 1;
            }
            j++;
        }
        i++;
    }
    i--;
    j--;
    if (mov == 0) { // Up
        // printf("Up\n");
        if (i - 1 < 0)
            return false;
        next_move->grid[i][j] = next_move->grid[i - 1][j];
        next_move->grid[i - 1][j] = 0;
    }
    if (mov == 1) { // Down
        // printf("Down\n");
        if (i + 1 >= _puzzle_size)
            return false;
        next_move->grid[i][j] = next_move->grid[i + 1][j];
        next_move->grid[i + 1][j] = 0;
    }
    if (mov == 2) { // Left
        // printf("Left\n");
        if (j - 1 < 0)
            return false;
        next_move->grid[i][j] = next_move->grid[i][j - 1];
        next_move->grid[i][j - 1] = 0;
    }
    if (mov == 3) { // Right
        // printf("Right\n");
        if (j + 1 >= _puzzle_size)
            return false;
        next_move->grid[i][j] = next_move->grid[i][j + 1];
        next_move->grid[i][j + 1] = 0;
    }
    return true;
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

int **Solver::cpy_grid(int **grid){
    int i = 0;
    int j;

    int **cpy;

    cpy = new int*[_puzzle_size];
    for(int i = 0; i < _puzzle_size; ++i) {
        cpy[i] = new int[_puzzle_size];
    }

    while (i < _puzzle_size){
        j = 0;
        while (j < _puzzle_size){
            cpy[i][j] = grid[i][j];
            j++;
        }
        i++;
    }
    return cpy;
}

int Solver::cmp_grid(int **grid, int **grid2){
    int i = 0;
    int j;

    while (i < _puzzle_size){
        j = 0;
        while (j < _puzzle_size){
            if (!(grid[i][j] == grid2[i][j]))
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}

// bool Solver::is_solvable(){
    // Translate
    // int i, j, n = nC*nL - 1, np, copie[MaxDim*MaxDim];
    // for (i = 0; i <= n; ++i)
    //     if ((copie[i] = jeu[i]) == 0) j = i; // copie et j = case vide
    // for (np = (n-j)%nC + (n-j)/nC; n > 0; --n) {
    //     if (n != j) {copie[j] = copie[n]; j = n; ++np;} // permutation
    //     while (copie[--j] != n) ; // j = prochaine case à (dé)placer
    // }
    // return 1&np;
    // Translate

//     int i = 0, j = 0;

//     for (i = 0; i < _puzzle_size; ++i) {
//         for (j = 0; j < _puzzle_size; ++i) {

//         }
//     }

//     return true;
// }