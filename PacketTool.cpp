#include "../Includes/PacketTool.hpp"

Packet::Packet(byte reciver, byte type, byte sender, byte seq_num)
: reciver(reciver),
type(type),
sender(sender),
seq_num(seq_num),
data_size(0)
{
}

Packet::Packet()
: data_size(0)
{
}

Msg::Msg (Packet packet)
{
	len = 4 + packet.data_size + 1;
	for (int i = 0 ; i < packet.data_size; i++)
		if (packet.data[i] == 0 || packet.data[i] == 1)
			len++;
	msg = new char[len];
	msg[0] = packet.reciver;
	msg[1] = packet.type;
	msg[2] = packet.sender;
	msg[3] = packet.seq_num;

	int cnt = 4;
	for (int i = 0; i < packet.data_size; i++)
	{
		if (packet.data[i] == 0 || packet.data[i] == 1)
			msg[cnt++] = 1;
		msg[cnt++] = packet.data[i];
	}
	msg[cnt] = 0;
	// std::cerr << msg << " BEBINAM " << std::endl;
}

Msg::~Msg ()
{
	// delete [] msg;
}

Packet PacketTool::get_top_packet(char msg[], int& cur_index, int len)
{
	Packet packet(msg[cur_index], msg[cur_index+1], msg[cur_index+2], msg[cur_index+3]);
	cur_index += 4;
	packet.data_size = 0;
	while(cur_index < len)
	{
		if (msg[cur_index] == 1)
		{
			cur_index++;
			packet.data[packet.data_size++] = msg[cur_index++];
		}
		else if (msg[cur_index] == 0)
		{
			cur_index++;
			break;
		}
		else
			packet.data[packet.data_size++] = msg[cur_index++];
	}
	packet.data[packet.data_size] = 0;
	return packet;
}

std::vector<Packet> PacketTool::parse_packet(char msg[], int len)
{
	int cur_index = 0;
	std::vector<Packet> packets;
	while (cur_index < len)
	{
		packets.push_back(get_top_packet(msg, cur_index, len));
	}
		
	return packets;
}

std::vector<Packet> PacketTool::creat_packets(std::string data, int packet_size, byte reciver,
		byte type, byte sender)
{
	int len = data.size() + 1;
	char chr[len];
	std::strcpy(chr, data.c_str());
	return creat_packets(chr, len, packet_size, reciver, type, sender);
}

std::vector<Packet> PacketTool::parse_packet(std::string data)
{
	int len = data.size();
	char chr[len];
	for (int i = 0; i < data.size(); i++)
		chr[i] = data[i];
	return parse_packet(chr, len);
}

std::vector<Packet> PacketTool::creat_packets(char data[], int len, int packet_size, byte reciver,
		byte type, byte sender)
{
	int last = 0;
	byte seq_num = 0;
	std::vector<Packet> packets;

	while (last < len)
	{
		packets.push_back(creat_packet(data, last, std::min(len, last + packet_size), reciver, type, sender, seq_num++));
		last = std::min(len, last + packet_size);
	}
	packets.push_back(Packet(reciver, type, sender, seq_num++));
	return packets;
}

Packet PacketTool::creat_packet(char data[], int l, int r, byte reciver, byte type, byte sender, byte seq_num)
{
	Packet packet(reciver, type, sender, seq_num);
	packet.data_size = 0;
	for (int i = l; i < r; i++)
		packet.data[packet.data_size++] = data[i];
	return packet;
}