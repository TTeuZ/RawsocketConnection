#include "ServerListConnection.hpp"

namespace network {
ServerListConnection::ServerListConnection(RawSocket* rawSocket) : Connection{rawSocket} { this->lastSequence = 0; };

void ServerListConnection::run() {
  this->rawSocket->activateTimeout();
  bool running{true};

  try {
    std::cout << "Iniciando conexao - LIST" << std::endl;

    Package ack{Constants::INIT_MARKER, 0, 0, PackageTypeEnum::ACK};
    this->rawSocket->sendPackage(ack);

    // Get all videos in directory
    std::cout << "Coletando dados..." << std::endl;

    std::vector<char> buffer;
    DIR* dir = opendir(Constants::VIDEOS_PATH);
    if (dir) {
      struct dirent* entry;

      while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        buffer.push_back('-');
        buffer.push_back(' ');
        buffer.insert(buffer.end(), entry->d_name, entry->d_name + strlen(entry->d_name));
        buffer.push_back('\n');
      }
      closedir(dir);
    } else {
      uint8_t errorCode[1] = {1};
      Package error{Constants::INIT_MARKER, 1, 0, PackageTypeEnum::ERROR, errorCode};
      this->rawSocket->sendPackage(error);
    }

    // Creating packages
    std::vector<char>::iterator buffer_it{buffer.begin()};
    std::vector<Package> packages;
    int current_size{0};
    int count{1};

    while (buffer_it != buffer.end()) {
      int batch_end{std::min(current_size + MAX_DATA_SIZE, static_cast<int>(buffer.size()))};
      uint8_t batch_size{static_cast<uint8_t>(batch_end - current_size)};

      uint8_t batch[MAX_DATA_SIZE];
      std::copy(buffer_it, buffer_it + batch_size, batch);

      packages.push_back(Package{Constants::INIT_MARKER, batch_size,
                                 static_cast<uint8_t>(count++ % Constants::MAX_SEQUENCE_SIZE), PackageTypeEnum::SHOW,
                                 batch});

      buffer_it += batch_size;
      current_size += batch_size;
    }

    // Sending packages
    std::vector<Package>::iterator it_package{packages.begin()};
    while (it_package != packages.end()) {
      std::cout << "Enviando pacote: " << (int)(*it_package).getSequence() << std::endl;

      this->rawSocket->sendPackage((*it_package));

      Package package{this->rawSocket->recvPackage()};
      if (package.getType() == PackageTypeEnum::ACK) ++it_package;
    }

    // End transmissian
    Package end_tx{Constants::INIT_MARKER, 0, static_cast<uint8_t>(count % Constants::MAX_SEQUENCE_SIZE),
                   PackageTypeEnum::END_TX};
    this->rawSocket->sendPackage(end_tx);

    std::cout << "Finalizando conexao - LIST\n" << std::endl;
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (package.getType() != PackageTypeEnum::ACK)
        this->rawSocket->sendPackage(end_tx);
      else
        running = false;
    }

    buffer.clear();
    packages.clear();
  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}
}  // namespace network