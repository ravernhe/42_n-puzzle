#include "../includes/npuzzle.hpp"

int main (int ac, char **av){

    if (ac != 2){
        std::cout << "Usage : ./n-puzlle \"n-puzzle_file.txt\"" << std::endl;
        return (1);
    }
    
    Parser parse(av[1]);
    Solver solve(parse.get_grid(), parse.get_puzzle_size());
    // while (1);
}