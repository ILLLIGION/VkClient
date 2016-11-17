#include <string>
#include <map>
#include "json.hpp"

namespace Vk
{
    class Client
    {
    public:
	using json = nlohmann::json;
        using dict_t = std::map<std::string, std::string>;
        Client(dict_t settings) : _settings(settings) {}
        auto check_connection() -> bool;
        auto get_friends() -> json;

    private:
        dict_t _settings;
        static auto write_callback(char *data, size_t size, size_t nmemb, std::string &buff) -> size_t;
    };
}
