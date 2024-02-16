#include "server.h"

#include <iostream>

using namespace tcp_client_serever;

Server::Server(char *argv[]) {
  std::istringstream str_iss(argv[1]);

  str_iss >> server_port_number_;

  sockaddr_in_.sin_family = AF_INET;
  sockaddr_in_.sin_port = htons(server_port_number_);
  sockaddr_in_.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Server::Exec(std::mutex &mutex) {
  listen_ = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_ < 0) {
    perror("server socket");
  } else {
    if (bind(listen_, (struct sockaddr *)&sockaddr_in_, sizeof(sockaddr_in_)) <
        0) {
      perror("server bind");
    } else {
      listen(listen_, 1);
      do {
        socket_ = accept(listen_, NULL, NULL);
        if (socket_ < 0) {
          perror("server accept");
        } else {
          ProcessClient(mutex);
        }
      } while (socket_ >= 0);
    }

    close(listen_);
  }
}

void Server::ProcessClient(std::mutex &mutex) {
  std::thread thread(Recv, socket_, ref(mutex));
  thread.detach();
}

void Server::Recv(int socket, std::mutex &mutex) {
  char buf[1024]{};

  recv(socket, buf, sizeof(buf), 0);
  close(socket);

  std::lock_guard<std::mutex> lock(mutex);
}