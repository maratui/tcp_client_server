#ifndef TCP_CLIENT_SERVER_SERVER_SERVER_H_
#define TCP_CLIENT_SERVER_SERVER_SERVER_H_

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <mutex>
#include <sstream>
#include <thread>

namespace tcp_client_serever {

class Server {
 public:
  Server() = delete;
  explicit Server(char *argv[]);

  void Exec(std::mutex &mutex);

 private:
  void static Recv(int socket, std::mutex &mutex);
  void ProcessClient(std::mutex &mutex);

  char *client_name_ = nullptr;
  int server_port_number_{};
  int server_connect_time_{};

  int socket_ = -1;
  int listen_ = -1;
  struct sockaddr_in sockaddr_in_ {};

  std::ofstream fout_;
};

}  // namespace tcp_client_serever

#endif  // TCP_CLIENT_SERVER_SERVER_SERVER_H_
