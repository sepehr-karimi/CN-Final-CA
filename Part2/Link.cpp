
#include "../include/Link.h"

Link::Link(std::string name, std::string read_pipe, std::string write_pipe) {
    this->name = name;
    this->read_pipe = read_pipe;
    this->write_pipe = write_pipe; 
    this->cost = 0;
}

std::string Link::get_read_pipe() {
    return read_pipe;
}

std::string Link::get_write_pipe() {
    return write_pipe;
}

void Link::change_cost(double new_cost) {
    cost = new_cost;
}
