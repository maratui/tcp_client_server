#include "client.h"

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
        SetClientString();
        send(socket_, client_string_.c_str(), client_string_.length(), 0);
      }

      close(socket_);
    }

    sleep(server_connect_time_);
  }
}

void Client::SetClientString() {
  const std::size_t kBufferSize = 256;
  std::size_t written_bytes{};
  char buf[kBufferSize]{};
  struct timeval tv {};

  gettimeofday(&tv, NULL);
  written_bytes =
      std::strftime(buf, sizeof(buf), "[%F %T", localtime(&tv.tv_sec));
  written_bytes += snprintf(buf + written_bytes, sizeof(buf) - written_bytes,
                            ".%06ld] ", tv.tv_usec);

  client_string_.clear();
  client_string_.append(buf, written_bytes);
  client_string_.append(client_name_, (int)std::strlen(client_name_));
}
