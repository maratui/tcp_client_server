#include "client.h"

#include <iostream>

using namespace tcp_client_serever;

Client::Client(char *argv[]) : client_name_(argv[1]) {
  server_port_number_ = ArgToNumber(argv[2]);
  server_connect_time_ = ArgToNumber(argv[3]);

  sockaddr_in_.sin_family = AF_INET;
  sockaddr_in_.sin_port = htons(server_port_number_);
  sockaddr_in_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

int Client::ArgToNumber(char *arg) {
  std::istringstream str_iss(arg);
  int num{};

  str_iss >> num;

  return num;
}

void Client::Exec() {
  while (true) {
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0) {
      perror("client socket");
    } else {
      if (connect(socket_, (struct sockaddr *)&sockaddr_in_,
                  sizeof(sockaddr_in_)) < 0) {
        perror("client connect");
      } else {
        std::string a = client_name_;
        std::cout << "client_name_ = " << a << "; sizeof(a) = " << sizeof(a)
                  << "\n";
        send(socket_, client_name_, 23, 0);
      }

      close(socket_);
    }

    sleep(server_connect_time_);
  }
}