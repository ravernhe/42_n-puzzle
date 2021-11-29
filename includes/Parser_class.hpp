#ifndef __PARSER_CLASS_HPP
# define __PARSER_CLASS_HPP

class Parser
{
private:
    std::string _puzzle;
    std::ifstream _file;
    std::string _line;
    std::string _value;
    int _puzzle_size;
    int **_grid;

public:
    Parser(std::string puzzle);
    ~Parser();
    void content_file();
    void set_grid();
    // void print_grid();
    int	ft_atoi(const char *str);
    // int get_puzzle_size();
    // int **get_grid();
};

#endif