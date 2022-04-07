#include "../includes/npuzzle.hpp"

Solver::Solver (int **grid, int puzzle_size)
{
    _grid = grid;
    _puzzle_size = puzzle_size;

    soluce_grid();
    // if (_soluce_grid == _grid)
    //     return 0
    // print_grid(_soluce_grid);
    // std::cout << is_solvable() << std::endl;
    solve();
}

Solver::~Solver()
{
    for(int i = 0; i < _puzzle_size; ++i) {
        delete[] _soluce_grid[i];
    }
    delete[] _soluce_grid;
}

int    Solver::solve()
{
    int         weight, zero, tmp_heur;
    bool        succes = false;
    struct Node *work_node;

    // Fonction solo ?
    int         **tmp;
    tmp = new int*[_puzzle_size];
    for(int i = 0; i < _puzzle_size; ++i) {
        tmp[i] = new int[_puzzle_size];
    }
    // Oui

    std::priority_queue<struct Node *, std::vector<struct Node *>, CompareWeight> opened;
    std::set<struct Node *> closed;

    opened.push(new Node(_grid, manhattan_heuristic(_grid), 0, NULL));
    // std::cout << opened.top()->heuristic << std::endl;
    // opened.push(new Node(_soluce_grid, manhattan_heuristic(_soluce_grid), opened.top()->cost + 1, opened.top()));
    // print_grid(opened.top()->grid);
    // std::cout << opened.top()->heuristic << std::endl;
    // std::cout << opened.top()->cost << std::endl;
    // std::cout << opened.top()->parent << std::endl;
    while (!opened.empty() && !succes) {
        work_node = opened.top();
        weight = work_node->heuristic + work_node->cost;
        
        // std::cout << work_node->heuristic << std::endl;
        if (work_node->heuristic == 0)
            succes = true;
        else {
            closed.insert(new Node(work_node->grid, work_node->heuristic, work_node->cost, work_node->parent));
            opened.pop();
            // std::cout << opened.top()->parent << std::endl;
            // Node *first (closed .begin());
            // std::set<struct Node *>::iterator it = closed.begin();
            // std::cout << (*it)->heuristic << std::endl;
            zero = find_empty(work_node->grid);
            // std::cout << "Real value : " << zero << " Calculated : " << zero / _puzzle_size << " " << zero % _puzzle_size << std::endl;
            for (int i = 0; i < 4; i++) { // i < 4
                // Make n moves possible, alloc n new grid, stock in open
                if (move(i, work_node->grid, tmp, zero)){
                    tmp_heur = manhattan_heuristic(tmp);
                    if () // ! Not in Open && Not in Close
                        opened.push(new Node(tmp, tmp_heur, work_node->cost + 1, work_node));
                    // print_grid(tmp);
                    else {
                        if (weight < tmp_heur + work_node->cost + 1) {
                            weight = tmp_heur + work_node->cost + 1;
                            if () { // ! Is in Close 
                                // ! Remove from Close
                                opened.push(new Node(tmp, tmp_heur, work_node->cost + 1, work_node));
                            }
                        }
                    }
                    succes = true;
                    // else {

                    // }
                }
            }
        }
    }
    // std::set<struct Node *>::iterator it = closed.begin();
    // delete (*it);
    return 0;
}


int     Solver::move(int mov, int **src, int **dest, int zero){
    int i = zero / _puzzle_size, j = zero % _puzzle_size;

    cpy_grid(src, dest);    
    if (mov == 0) { // Up
        if (i - 1 < 0){
            // std::cout << "Move" << std::endl;
            return 0;}
        else {
            dest[i][j] = dest[i - 1][j];
            dest[i - 1][j] = 0;
        }
    }
    if (mov == 1) { // Down
        if (i + 1 >= _puzzle_size)
            return 0;
        else {
            dest[i][j] = dest[i + 1][j];
            dest[i + 1][j] = 0;
        }
    }
    if (mov == 2) { // Left
        if (j - 1 < 0)
            return 0;
        else {
            dest[i][j] = dest[i][j - 1];
            dest[i][j - 1] = 0;
        }
    }
    if (mov == 3) { // Right
        if (j + 1 >= _puzzle_size)
            return 0;
        else {
            dest[i][j] = dest[i][j + 1];
            dest[i][j + 1] = 0;
        }
    }
    return 1;
}

// No Malloc here
void    Solver::cpy_grid(int **src, int **dest){
    int i = 0;
    int j;

    while (i < _puzzle_size){
        j = 0;
        while (j < _puzzle_size){
            dest[i][j] = src[i][j];
            j++;
        }
        i++;
    }
}

int Solver::find_empty(int **grid) {
    for (int i = 0; i < _puzzle_size * _puzzle_size; i++) {
        if (grid[i / _puzzle_size][i % _puzzle_size] == 0)
            return i;
    }
    return -1;
}

int Solver::linear_conflict(int **grid) {
    int nb_conflict = 0;

    for(int i = 0; i < _puzzle_size; ++i) {
        for(int j = 0; j < _puzzle_size; ++j) {
            if ((j+1 < _puzzle_size && grid[i][j] == _soluce_grid[i][j+1] && grid[i][j+1] == _soluce_grid[i][j]) \
            || (i+1 < _puzzle_size && grid[i][j] == _soluce_grid[i+1][j] && grid[i+1][j] == _soluce_grid[i][j]))
                nb_conflict++;
        }
    }
    return (nb_conflict);
}

// int Solver::manhattan_heuristic(int **grid){ // Opti
//     int heuristic = 0;

//     for(int i = 0; i < _puzzle_size; ++i) {
//         for(int j = 0; j < _puzzle_size; ++j) {
//             for(int y = 0; y < _puzzle_size; ++y) {
//                 for(int x = 0; x < _puzzle_size; ++x) {
//                     if (grid[i][j] == _soluce_grid[y][x] && grid[i][j] != 0) {
//                         heuristic += abs(i - y) + abs(j - x);
//                     }   
//                 }
//             }
//         }
//     }
//     return (heuristic + 2 * linear_conflict(grid));
// }

int Solver::manhattan_heuristic(int **grid){
    int heuristic = 0;

    for(int i = 0; i < _puzzle_size * _puzzle_size; ++i) {
        for(int y = 0; y < _puzzle_size * _puzzle_size; ++y) {
            if (grid[i / _puzzle_size][i % _puzzle_size] == _soluce_grid[y / _puzzle_size][y % _puzzle_size] && grid[i / _puzzle_size][i % _puzzle_size] != 0) {
                heuristic += abs(i / _puzzle_size - y / _puzzle_size) + abs(i % _puzzle_size - y % _puzzle_size);
            }
        }
    }
    return (heuristic + 2 * linear_conflict(grid));
}

void Solver::soluce_grid()
{
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

void Solver::print_grid(int **grid)
{
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

bool Solver::is_solvable() // Maybe Working, Not working for fucking snail
{
    int count = 0, a = 0, b = 0, empty_Y;
    int board_size = _puzzle_size * _puzzle_size;

    for (int i = 0; i < board_size; i++)
	{
        if (_grid[i / _puzzle_size][i % _puzzle_size] == 0)
            empty_Y = i / _puzzle_size;
		a = _grid[i / _puzzle_size][i % _puzzle_size];
		for (int j = i + 1; j < board_size; j++)
		{
			b = _grid[j / _puzzle_size][j % _puzzle_size];
			if (a != 0 && b != 0 && a > b)
				count++;
		}
	}

    if (board_size % 2 == 1)
		return (count % 2 == 0);
	if ((board_size - empty_Y) % 2 == 0)
		return (count % 2 == 1);
	else
		return (count % 2 == 0);
}