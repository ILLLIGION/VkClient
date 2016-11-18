#include <string>
#include <map>
#include <vector>
#include "json.hpp"
#include "friend.hpp"

namespace Vk
{
    class Client
    {
    public:
	using json = nlohmann::json;
        using dict_t = std::map<std::string, std::string>;
        Client(dict_t settings) : _settings(settings) {}
        auto check_connection() -> bool;
        auto get_friends() -> std::vector<VkFriend>;

    private:
        dict_t _settings;
        static auto write_callback(char *data, size_t size, size_t nmemb, std::string &buff) -> size_t;
    };
}
