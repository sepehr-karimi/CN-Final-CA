#ifndef _Host_hpp_
#define _Host_hpp_

#include "PacketTool.hpp"
#include "SocketTool.hpp"
#include "DataReciver.hpp"

class Host
{
	public:
		Host(byte name);
		void run();
		void recive(std::string data);
		void send_data(std::string command);
		void send_packets(const std::vector<Packet>& packets, int l, int window_size);
		void connect_to_router();
		void run_for_red();
		~Host();
	private:
		byte name;
		HostState state;
		int fd;
		std::vector<DataReciver> data_recivers;
		std::map<byte, int> has_reciver;
};

#endif