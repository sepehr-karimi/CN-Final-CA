#include "../include/Network.h"

using namespace std;

int main() {
    Network network;
    network.start();
    return 0;
}

Network::Network()
: network_pipe_read(PIPE_ROOT_PATH + string(NETWORK_PIPE_NAME) + string(READ_PIPE))
, network_pipe_write(PIPE_ROOT_PATH + string(NETWORK_PIPE_NAME) + string(WRITE_PIPE)) {
    unlink(network_pipe_read.c_str());
	mkfifo(network_pipe_read.c_str(), READ_WRITE);
    unlink(network_pipe_write.c_str());
	mkfifo(network_pipe_write.c_str(), READ_WRITE);
}

void Network::start() {
    char received_message[] = {0};
    fd_set fds;
    int maxfd;

    int network_pipe_read_fd = open(network_pipe_read.c_str(), O_RDWR);
    printf("Network is starting ...\n");
    while (true) {
        maxfd = network_pipe_read_fd;
        FD_ZERO(&fds);
        FD_SET(network_pipe_read_fd, &fds);

        if (select(maxfd + 1, &fds, NULL, NULL, NULL) < 0)
            return;

        if (FD_ISSET(network_pipe_read_fd, &fds)) {
            memset(received_message, 0, sizeof received_message);
            //read(network_pipe_read_fd, received_message, MAX_MESSAGE_SIZE);
            handle_message(received_message);
            cout << "received network message: " << received_message << endl;
        }

        cout << "--------------- event ---------------" << endl;
    }
    close(network_pipe_read_fd);
}

void Network::handle_message(string message) {
    vector<string> message_parts = split(message, MESSAGE_DELIMITER);
    cout << message_parts[0] << endl;
}
