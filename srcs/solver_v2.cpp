struct node Base = {grid, manhattan_heuristic(grid), NULL};

int     **get_next_grid() {
    // move(grid, 1);
    // move(grid, 2);
    // move(grid, 3);
    // move(grid, 4);

    // return all smallest f value

    // !!! GET SMALLER F VALUE, LOWEST H VALUE
}

void    solve() {
    std::vector<node>    opened;
    std::vector<node>    closed;

    opened.push_back(_Base);

    bool succes = False;
    int **e_grid;
    int     **current_move = nullptr;

    while (!opened.empty() && !succes) {
        e_grid = get_next_grid(); // Lowest F opened &7 Get int *Index in opened
        // f(e_grid); On calcule
        if (e_grid == soluce_grid) {
           succes = True;
        }
        else {
            opened.erase(opened.begin() + index); // Index of e in opened
            closed.push_back(e_grid);

            for (int i = 0; i < 4; i++) {
                // if move actually move
                current_move = move(i);
                if (std::find(opened.begin(), opened.end(), current_move) == opened.end() && \
                std::find(closed.begin(), closed.end(), current_move) == closed.end()) {
                    opened.push_back(current_move);
                    // cost = cost_parent+1
                    // On save le cost && le parent
                }
                else {
                    if (f(e_grid) > f(current_move)) {
                        f(e_grid) = f(current_move);
                        opened.push_back(current_move); // ? Here we had node
                        if (std::find(closed.begin(), closed.end(), current_move) != closed.end()) {
                            closed.erase(closed.begin() + index); // index current_move
                            opened.push_back(current_move); 
                        }
                    }
                }
                // Get a copy of each Movable possible
            }
        }
    }
    // if (succes == True)
    //     return Path;
    // else
    //     return Unsolvable;
}