#include "ClientDownloadConnection.hpp"

namespace network {
ClientDownloadConnection::ClientDownloadConnection(RawSocket* rawSocket, const std::string& videoName)
    : Connection{rawSocket} {
  this->lastSequence = 0;
  this->videoName = videoName;
};

void ClientDownloadConnection::run() {
  if (this->videoName.length() > MAX_DATA_SIZE) {
    std::cout << "Nome excedeu os limites!" << std::endl;
    return;
  }

  this->rawSocket->activateTimeout();
  bool running{true};

  try {
    const uint8_t* data{reinterpret_cast<const uint8_t*>(this->videoName.c_str())};
    Package initialPackage{Constants::INIT_MARKER, static_cast<uint8_t>(this->videoName.length()), 0,
                           PackageTypeEnum::DOWNLOAD, data};
    this->rawSocket->sendPackage(initialPackage);
    this->wait_ack(initialPackage);

    // Waiting header
    running = true;
    uintmax_t fileSize{0};
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (package.checkCrc()) {
        Package ack{Constants::INIT_MARKER, 0, package.getSequence(), PackageTypeEnum::ACK};

        if (package.getType() == PackageTypeEnum::FILE_HEADER) {
          for (size_t i = 0; i < package.getDataSize(); ++i)
            fileSize |= static_cast<uintmax_t>(package.getData()[i]) << ((7 - i) * 8);

          this->rawSocket->sendPackage(ack);
          this->lastSequence = package.getSequence();

          running = false;
        } else {
          std::cout << "Arquivo inexistente!" << std::endl;
          this->rawSocket->sendPackage(ack);
          this->rawSocket->inactivateTimeout();

          return;
        }
      } else {
        Package nack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::NACK};
        this->rawSocket->sendPackage(nack);
      }
    }

    // @TODO CHECAR SE TEMOS ESPACO E SE NAO TIVER MANDAR UM ERRO.

    std::cout << "\nRecebendo arquivo - " << this->videoName << std::endl;
    uintmax_t totalPackages{static_cast<uintmax_t>(std::ceil(static_cast<double>(fileSize) / MAX_DATA_SIZE))};

    // Receive packages
    bool crcFailed{false};
    size_t windowCount{0};
    uintmax_t recvPackages{0};
    std::vector<Package> packages;
    std::array<Package, WINDOW_SIZE> windowPackages;
    while (recvPackages < totalPackages) {
      Package package{this->rawSocket->recvPackage()};

      if (package.checkCrc()) {
        if (this->lastSequence != package.getSequence()) {
          windowPackages[windowCount] = package;
          ++windowCount;
          ++recvPackages;
          this->lastSequence = package.getSequence();
        }
      } else
        crcFailed = true;

      if ((windowCount % WINDOW_SIZE) == 0 || recvPackages == totalPackages) {
        Package ack{Constants::INIT_MARKER, 0, windowPackages[WINDOW_SIZE - 1].getSequence(), PackageTypeEnum::ACK};
        Package nack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::NACK};

        if (!crcFailed) {
          size_t range{recvPackages != totalPackages ? WINDOW_SIZE : windowCount};
          for (size_t i = 0; i < range; ++i) packages.push_back(windowPackages[i]);
          this->rawSocket->sendPackage(ack);

          this->showProgress(recvPackages, totalPackages);
        } else {
          recvPackages -= recvPackages != totalPackages ? WINDOW_SIZE : windowCount;
          this->rawSocket->sendPackage(nack);
        }

        crcFailed = false;
        windowCount = 0;
      }
    }

    // wait for end trasmition
    running = true;
    while (running) {
      Package package{this->rawSocket->recvPackage()};

      if (package.checkCrc()) {
        Package ack{Constants::INIT_MARKER, 0, package.getSequence(), PackageTypeEnum::ACK};
        this->rawSocket->sendPackage(ack);

        std::cout << "\n" << std::endl;
        running = false;

      } else {
        Package nack{Constants::INIT_MARKER, 0, this->lastSequence, PackageTypeEnum::NACK};
        this->rawSocket->sendPackage(nack);
      }
    }

    // Writing file
    std::string path{std::string{Constants::DOWNLOADS_PATH} + "/" + this->videoName};
    std::vector<Package>::iterator it_package{packages.begin()};
    std::ofstream outFile(path);

    std::cout << "Salvando arquivo em " << path << std::endl;

    if (outFile) {
      while (it_package != packages.end()) {
        for (size_t i = 0; i < (*it_package).getDataSize(); ++i) outFile << (*it_package).getData()[i];
        ++it_package;
      }
    }
    outFile.close();

    // Opening video
    std::string command{"xdg-open "};
    command += path;

    if (system(command.c_str()) == -1) std::cout << "Impossibilitado de abrir o player padrao!\n" << std::endl;

    packages.clear();
  } catch (exceptions::TimeoutException& e) {
    std::cerr << "Connection Timeout - closing" << std::endl;
    this->rawSocket->inactivateTimeout();
  }

  this->rawSocket->inactivateTimeout();
}

void ClientDownloadConnection::showProgress(const uintmax_t recvPackages, const uintmax_t totalPackages) const {
  const int barWidth = 50;
  double progress = static_cast<double>(recvPackages) / totalPackages;

  std::cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      std::cout << "=";
    else if (i == pos)
      std::cout << ">";
    else
      std::cout << " ";
  }
  std::cout << "] " << int(progress * 100.0) << " % (" << recvPackages << "/" << totalPackages << ")\r";
}
}  // namespace network
