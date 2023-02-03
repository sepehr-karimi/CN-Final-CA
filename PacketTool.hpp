#ifndef _PacketTool_hpp_
#define _PacketTool_hpp_

#include "IncludesAndDefines.hpp"

struct Packet
{
	Packet(byte reciver, byte type, byte sender, byte seq_num);
	Packet();
	byte reciver;
	byte type;
	byte sender;
	byte seq_num;
	int data_size;
	char data[MAX_DATA_SIZE];
};

class Msg
{
	public:
		int len;
		char* msg;
		Msg (Packet packet);
		~Msg ();
};

class PacketTool
{
	public:
		static Packet get_top_packet(char msg[], int& cur_index, int len);
		static std::vector<Packet> parse_packet(char msg[], int len);
		static std::vector<Packet> parse_packet(std::string);
		static std::vector<Packet> creat_packets(char data[], int len, int packet_size, byte reciver, byte type,
				byte sender);
		static std::vector<Packet> creat_packets(std::string data, int packet_size, byte reciver, byte type,
				byte sender);
		static Packet creat_packet(char data[], int l, int r, byte reciver, byte type, byte sender, byte seq_num);
};

#endif