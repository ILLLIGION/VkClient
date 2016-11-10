#include <../include/vk/client.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	std::string token;
	std::cout << "Follow the link:" << std::endl;
	std::cout << "https://oauth.vk.com/authorize?client_id=5721051&display=page&redirect_uri=https://github.com&scope=friends&response_type=token&v=5.60" << std::endl;
	std::cout << "Token: ";
	std::cin >> token;
	vk::Client client({{"token", token}});

	if (client.check_connection())
		std::cout << "Connected" << std::endl;

	system("pause");
	return 0;
}
