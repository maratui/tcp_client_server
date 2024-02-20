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
  int bytes_read{};
  std::string recv_text = "";

  bytes_read = recv(socket, buf, sizeof(buf), 0);
  close(socket);
  recv_text.append(buf, bytes_read);

  std::lock_guard<std::mutex> lock(mutex);
  std::cout << recv_text << std::endl;
  WriteLog(recv_text);
}

void Server::WriteLog(const std::string &log_text) {
  std::ofstream out("log.txt", std::ios::app);

  if (out.is_open()) {
    out << log_text << std::endl;
    out.close();
  } else {
    ExitWithLog("Error occured when open log file");
  }
}

void Server::ExitWithLog(const std::string &log_text) {
  std::cerr << log_text;
  if (errno) {
    std::cerr << ": " << std::strerror(errno) << std::endl;
    exit(errno);
  } else {
    std::cerr << std::endl;
    exit(EXIT_FAILURE);
  }
}
