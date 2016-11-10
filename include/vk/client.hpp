#include <string>
#include <map>
#include <curl/curl.h>
#include <iostream>

namespace vk{
	class Client{
	public:
		using dict_t = std::map<std::string, std::string>;
		Client(dict_t settings) : settings_(settings) {};
		auto check_connection() -> bool
		{
			CURL *curl = curl_easy_init();
			if(curl)
			{
				std::string data = "access_token=" + settings_["token"] + "&v5.60";
				curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getProfileInfo?");
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
				if (curl_easy_perform(curl) == CURLE_OK) {
					std::cout << "Connection successful";
					curl_easy_cleanup(curl);
					return 1;
				}
				else {
					std::cout << "Connection problems";
					curl_easy_cleanup(curl);
					return 0;
				}
			};
		};
	private:
		dict_t settings_;
  	};
}
