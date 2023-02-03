#include "../Includes/Router.hpp"

#define LEN_PACKET 2048

std::mutex mtx;

Router::Router(int len_input)
{
	len_queue = len_input;

	router_fd = socket_tools.creat_socket();
	socket_tools.bind_socket(router_fd, PORT);
	socket_tools.listen_socket(router_fd);
	socket_tools.set_socket_options(router_fd);
}

int Router::find_host(byte host_name)
{
	for(int i = 0; i < hosts.size(); i++)
	{
		if(name_host[i] == host_name)
		{
			return hosts[i];
		}
	}
	return -1;
}

void Router::run_send_thread()
{
	while(true)
	{
		mtx.lock();
		if(router_queue.size())
		{
			Packet packet = router_queue.front();
			router_queue.pop();

			int fd_need = find_host(packet.reciver);
			Msg msg(packet);
			send(fd_need, msg.msg, msg.len, 0);
		}
		mtx.unlock();
	}	
}

int Router::accept_new_request(int master_socket)
{
	struct sockaddr_in caddr;
	int len = sizeof(caddr);
	int* caddrlen = &len;

	int new_socket;
	if((new_socket = accept(master_socket, (struct sockaddr *) &caddr, (unsigned int *) caddrlen)) < 0){
		std::cout << "New Host connection failed." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Host accepted" << std::endl;
	}	

	return new_socket;
}

void Router::add_new_packets(std::vector<Packet> new_packets)
{
	for(auto packet : new_packets)
	{
		mtx.lock();
		int tmp = rand() % 10;
		if (tmp)
		{
			if (router_queue.size() < len_queue)
			{
				Msg msg(packet);
				router_queue.push(packet);
			}
		}
		mtx.unlock();
	}
}



void Router::run_recv_thread()
{
	fd_set master_set, working_set;

	int max_fd = router_fd;

	FD_ZERO(&master_set);
	FD_SET(router_fd, &master_set);

	while(true)
	{
		char buf[MAX_DATA_SIZE];
		working_set = master_set;
		if (select(max_fd + 1, &working_set, NULL, NULL, NULL) == -1)
		{
			std::cout << "Select failed" << std::endl;
			exit(-1);
		}

		if (FD_ISSET(router_fd, &working_set))
		{
			int new_fd = accept_new_request(router_fd);

			hosts.push_back(new_fd);
			number_messages_from_host.push_back(0);
			max_fd = std::max(max_fd, new_fd);
			FD_SET(new_fd, &master_set);
		}
		else
		{
			int len = hosts.size();
			for (int i = 0; i < len; i++)
			{
				if (!FD_ISSET(hosts[i], &working_set))
					continue;
				mtx.lock();
				int msg_size = recv(hosts[i], buf, LEN_PACKET, 0);
				mtx.unlock();
				if(msg_size <= 0)
				{
					if(msg_size < 0)
						std::cout << "Message is broken" << std::endl;
					else if(msg_size == 0)
					{
						std::cout << "A client quits" << std::endl;
						FD_CLR(hosts[i], &master_set);
						number_messages_from_host[i] = 0;
						close(hosts[i]);
						hosts.pop_back();
					}
				}
				else{
					buf[msg_size] = '\0';

					if(!number_messages_from_host[i])
					{
						name_host[i] = buf[0];
						std::cout << "New Host name is " << buf[0] << std::endl;
					}
					else 
					{
						std:: vector<Packet> new_packets = PacketTool::parse_packet(buf, msg_size);
						add_new_packets(new_packets);
					}
					number_messages_from_host[i]++;
				}
			}
		}
	}
}

void Router::run_all()
{
	pthread_t threads[2];
	int ret_code;

	std::thread thread1(&Router::run_recv_thread, this);
	std::thread thread2(&Router::run_send_thread, this);
	thread1.join();
	thread2.join();
}

Router::~Router ()
{
	for(int i = 0; i < hosts.size(); i++)
	{
		close(hosts[i]);
	}
	close(router_fd);
}


int main(int argc, char* argv[])
{
	srand(time(0));
	if (argc != 3)
	{
		std::cout << "Wrong number of Argumants for running Router" << std::endl;
		return 0;
	}
	std::string queue_size(argv[1]);
	if(argv[2][0] == '0')
	{
		Router* router = new Router(stoi(queue_size));
		router->run_all();
		delete router;
	}
/* 	else 
	{
		RouterRed* router_red = new RouterRed(stoi(queue_size));
		router_red->run_red();
		delete router_red;
	} */

}