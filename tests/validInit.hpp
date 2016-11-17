#include <string>
#include <map>
#include <iostream>

std::map<std::string, std::string> gettingtoken()
{
    std::string token;
    std::cout << "Follow the link to get access token" << std::endl;
    std::cout << "https://oauth.vk.com/authorize?client_id=5721051&display=page&redirect_uri=https://oauth.vk.com/blank.html&scope=friends&response_type=token&v=5.59" << std::endl;
    std::cout << "Token:";
    std::cin >> token;

    return std::map<std::string, std::string>({{"token", token}});
};
