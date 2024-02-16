#include <iostream>

#include "client.h"

using namespace tcp_client_serever;

int main(int argc, char *argv[]) {
  if (argc == 4) {
    Client client(argv);

    client.Exec();
  } else {
    std::cout << "Клиент должен получить из командной строки 3 параметра:\n 1) "
                 "Текстовое имя клиента\n 2) Номер порта сервера\n 3) Период "
                 "подключения к серверу в секундах\n";
  }

  return 0;
}
