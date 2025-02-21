#include <string>
#include <functional>
#include <memory>

namespace cumton::network
{

    class IServer
    {

        public:

        virtual ~IServer() = default;

        virtual void SetHandler() = 0;

        virtual void Process() = 0;

        
    };

    std::unique_ptr<IServer> CreateServer(std::string ip, int port);

}