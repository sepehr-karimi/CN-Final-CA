#ifndef _DataReciver_hpp_ 
#define _DataReciver_hpp_

#include "PacketTool.hpp"

class DataReciver
{
	private:
		byte recivers_name;
		byte senders_name;
		std::string recived_data;
		int seq_num;
		int file_number;
		
	public:
		DataReciver(byte recivers_name, byte senders_name);
		int add_packet(Packet packet);
		void creat_file();
		byte get_senders_name();
};

#endif