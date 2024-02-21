#include "server.h"

using namespace tcp_client_serever;

Server::Server(char *argv[]) {
  std::istringstream str_iss(argv[1]);

  str_iss >> server_port_number_;

  sockaddr_in_.sin_family = AF_INET;
  sockaddr_in_.sin_port = htons(server_port_number_);
  sockaddr_in_.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Server::Exec(std::mutex &mutex) {
  listener_ = socket(AF_INET, SOCK_STREAM, 0);
  if (listener_ < 0) {
    perror("server socket");
  } else {
    if (bind(listener_, (struct sockaddr *)&sockaddr_in_,
             sizeof(sockaddr_in_)) < 0) {
      perror("server bind");
    } else {
      listen(listener_, 1);
      do {
        socket_ = accept(listener_, NULL, NULL);
        if (socket_ < 0) {
          perror("server accept");
        } else {
          ProcessClient(mutex);
        }
      } while (socket_ >= 0);
    }

    close(listener_);
  }
}

void Server::ProcessClient(std::mutex &mutex) {
  std::thread thread(Recv, socket_, ref(mutex));
  thread.detach();
}

void Server::Recv(int socket, std::mutex &mutex) {
  const std::size_t kBufSize = 1024;
  std::size_t read_bytes{};
  char buf[kBufSize]{};
  std::string recv_string = "";

  read_bytes = recv(socket, buf, sizeof(buf), 0);
  close(socket);
  recv_string.append(buf, read_bytes);

  std::lock_guard<std::mutex> lock(mutex);
  WriteLog(recv_string);
}

void Server::WriteLog(const std::string &log_text) {
  std::ofstream out("log.txt", std::ios::app);

  if (out.is_open()) {
    out << log_text << std::endl;
    out.close();
  } else {
    perror("log.txt");
  }
}
