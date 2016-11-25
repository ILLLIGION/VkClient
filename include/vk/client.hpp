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
        Client(dict_t settings) : _settings(settings) {};
        auto check_connection() -> bool;
        auto get_friends() -> std::vector<VkFriend>;
	auto print_friends_using_threads(int num_of_threads) -> void;
	auto friend_printer(int n) -> bool;  
    private:
        dict_t _settings;
        static auto write_callback(char *data, size_t size, size_t nmemb, void* buff) -> size_t;
    };
}
