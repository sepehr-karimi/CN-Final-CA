#ifndef _IncludesAndDefines_hpp_
#define _IncludesAndDefines_hpp_

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <ctime>
#include <map>
#include <thread>
#include <algorithm>
#include <chrono>
#include <pthread.h>
#include <queue>
#include <stdlib.h>
#include <mutex>
#include <random>

#define SERVER_IP "127.0.0.1"
#define COMMAND_BUF_SIZE 256
#define DATA_BUF_SIZE 100000
#define MAX_DATA_SIZE 16384
#define MAX_CONNECTIONS 40
#define PORT 8016
#define ACK_TYPE 0
#define DATA_TYPE 1

enum HostState{waiting, reciving, sending};

typedef unsigned char byte;

#endif