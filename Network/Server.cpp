#include "Server.hpp"

std::unique_ptr<IServer> cumton::network::CreateServer(std::string ip, int port)
{
    return std::unique_ptr<IServer>();
}