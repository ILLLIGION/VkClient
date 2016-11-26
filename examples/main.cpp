#include <vk/client.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    std::string token;
    std::cout << "Follow the link below to get access token" << std::endl;
    std::cout << "https://oauth.vk.com/authorize?client_id=5721051&display=page&redirect_uri=https://oauth.vk.com/blank.html&scope=friends&response_type=token&v=5.59" << std::endl;
    std::cout << "Token:";
    std::cin >> token;
	if (!std::cin) throw std::invalid_argument("incorrect arguement");

    Vk::Client client({{"token", token}});

    if (client.check_connection())
        std::cout << "Connected." << std::endl;
    bool flag = (argc > 1 && argv[1] == "-v");

    int num_of_threads;
    std::cout << "Enter the number of threads:";
    std::cin >> num_of_threads;
	if (!std::cin) throw std::invalid_argument("incorect argument");
	else client.print_friends_using_threads(num_of_threads, flag);
    return 0;
}
