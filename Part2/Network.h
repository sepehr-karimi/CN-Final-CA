#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h> 
#include <dirent.h>
#include <fcntl.h> 

#include "../include/Utilities.h"

class Network
{
public:
    Network();
    ~Network() = default;

    void start();
    void handle_message(std::string message);

private:
    std::string network_pipe_read;
    std::string network_pipe_write;
};
