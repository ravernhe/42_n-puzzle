#include "../includes/npuzzle.hpp"

Parser::Parser(std::string puzzle)
{
    _puzzle = puzzle;
    _puzzle_size = 0;
}

Parser::~Parser()
{
    for(int i = 0; i < _puzzle_size; ++i) {
        delete[] _grid[i];
    }
    delete[] _grid;

}

void Parser::content_file() {
    _file.open(_puzzle);

    if (_file.is_open()) {
        while (getline (_file,_line))
        {
            int i = 0;
            while (i < (int)_line.length()) {

                if (_line[i] == '#')
                    break;
                if (_puzzle_size == 0) {
                    _puzzle_size = stoi(_line);
                    // if puzzlesize == 0, ERR
                }
                else {
                        _value.push_back(_line[i]);
                }
                i++;
            }
            _value.push_back(' ');
        }
    }
    set_grid();
}

void Parser::set_grid(){
    _grid = new int*[_puzzle_size];
    for(int i = 0; i < _puzzle_size; ++i) {
        _grid[i] = new int[_puzzle_size];
    }
    int i = 0, w = 0, h = 0;
    char value_cpy[_value.length() + 1];
    strcpy(value_cpy, _value.c_str());

    while (i < (int)_value.length() + 1){
        while (value_cpy[i] == ' '){i++;}
        if (h == _puzzle_size) {
            h = 0;
            w++;            
        }
        if (w >= _puzzle_size) {
                break ;
        }
        _grid[w][h] = ft_atoi(&value_cpy[i]);
        h++;
        while (value_cpy[i] >= '0' && value_cpy[i] <= '9'){i++;}
    }
}

// void Parser::print_grid(){
//     int i = 0;
//     int j;
//     while (i < _puzzle_size){
//         j = 0;
//         while (j < _puzzle_size){
//             std::cout << _grid[i][j] << " ";
//             j++;
//         }
//         std::cout << "\n";
//         i++;
//     }
// }

int	Parser::ft_atoi(const char *str)
{
	int i;
	int n;
	int r;

	r = 0;
	n = 1;
	i = 0;
	while ((str[i] >= '\a' && str[i] <= '\r') || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * n);
}

int Parser::get_puzzle_size() {
    return(_puzzle_size);
}

int **Parser::get_grid() {
    return(_grid);
}