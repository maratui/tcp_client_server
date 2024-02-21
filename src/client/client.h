#ifndef TCP_CLIENT_SERVER_CLIENT_CLIENT_H_
#define TCP_CLIENT_SERVER_CLIENT_CLIENT_H_

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <ctime>
#include <sstream>

namespace tcp_client_serever {

class Client {
 public:
  Client() = delete;
  explicit Client(char *argv[]);

  void Exec();

 private:
  int ArgToNumber(char *arg);
  void SetClientString();

  char *client_name_ = nullptr;
  int server_port_number_{};
  int server_connect_time_{};

  int socket_ = -1;
  struct sockaddr_in sockaddr_in_ {};

  std::string client_string_ = "";
};

}  // namespace tcp_client_serever

#endif  // TCP_CLIENT_SERVER_CLIENT_CLIENT_H_
