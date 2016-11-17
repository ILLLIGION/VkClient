#include "../include/vk/client.hpp"
#include <iostream>

int main()
{
    std::string token;
    std::cout << "Follow the link below to get access token" << std::endl;
    std::cout << "https://oauth.vk.com/authorize?client_id=5721051&display=page&redirect_uri=https://oauth.vk.com/blank.html&scope=friends&response_type=token&v=5.59" << std::endl;
    std::cout << "Token:";
    std::cin >> token;
    Vk::Client vk_cl({{"token", token}});

    if (vk_cl.check_connection())
        std::cout << "Connected." << std::endl;

    vk_cl.get_friends();

    return 0;
}
