#include "../Includes/SocketTool.hpp"


int SocketTools::creat_socket()
{
	int new_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (new_socket < 0)
	{
		std::cerr << "Fail to create socket" << std::endl;
		exit(1);
	}
	else
		std::cout << "socket created" << std::endl;
	return new_socket;
}

struct sockaddr_in SocketTools::init_socaddr_in(unsigned short port)
{
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	sock_addr.sin_port = htons(port);
	memset(sock_addr.sin_zero, '\0', sizeof(sock_addr.sin_zero));
	return sock_addr;
}

void SocketTools::bind_socket(int new_socket, unsigned short port)
{
	struct sockaddr_in sock_addr = init_socaddr_in(port);

	if (bind(new_socket, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0)
	{
		std::cerr << "Error while binding" << std::endl;
		exit(1);
	}
	else
		std::cout << "Socket binded" << std::endl;
}

void SocketTools::listen_socket(int new_socket)
{
	if(listen(new_socket, MAX_CONNECTIONS) < 0)
	{
		std::cerr << "Error in listening." << std::endl;;
		exit(1);
	}
	else
		std::cout << "Server is listening." << std::endl;
}

void SocketTools::set_socket_options(int new_socket)
{
	int opts = 1;
    if(setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, (char*) &opts, sizeof(opts)) < 0)
	{
        std::cerr << "Error in options" << std::endl;
        exit(1);
    }
}

int SocketTools::connect_to_server(unsigned short port)
{
	int new_socket = creat_socket();
	
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	sock_addr.sin_port = htons(port);
	memset(sock_addr.sin_zero, '\0', sizeof(sock_addr.sin_zero));

	if(connect(new_socket, (struct sockaddr*) &sock_addr, sizeof(sock_addr)) < 0)
	{
        std::cerr << "Error in connecting to Router" << std::endl;
		exit(1);
	}
    else
    	std::cout << "connected to Router" << std::endl;

    return new_socket;
}