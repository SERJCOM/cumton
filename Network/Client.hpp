#include <string>
#include <memory>

namespace cumton::network{

class IClient{
public:

    virtual ~IClient() = default;

    virtual void SendMessage() = 0;

};

std::unique_ptr<IClient> CreateClient(std::string ip, int port);

}