#include <iostream>

#include "server.h"

using namespace tcp_client_serever;

int main(int argc, char *argv[]) {
  if (argc == 2) {
    std::mutex mutex;
    Server server(argv);

    server.Exec(mutex);
  } else {
    std::cout << "Сервер должен получить из командной строки 1 параметр:\n 1) "
                 "Номер порта сервера\n";
  }

  return 0;
}
