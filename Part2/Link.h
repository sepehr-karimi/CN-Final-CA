#include <iostream>
#include <vector>
#include <string>

class Link
{
public:
    Link(std::string name, std::string read_pipe, std::string write_pipe);

    std::string get_write_pipe();
    std::string get_read_pipe();
    void change_cost(double new_cost);
private:
    double cost;
    std::string name;
    std::string read_pipe;
    std::string write_pipe;
};

