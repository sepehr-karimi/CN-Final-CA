#ifndef _SocketTool_hpp_
#define _SocketTool_hpp_

#include "IncludesAndDefines.hpp"

class SocketTools
{
	public:
		int creat_socket();
		void bind_socket(int new_socket, unsigned short port);
		void listen_socket(int new_socket);
		void set_socket_options(int new_socket);
		struct sockaddr_in init_socaddr_in(unsigned short port);
		int connect_to_server(unsigned short port);
};

#endif