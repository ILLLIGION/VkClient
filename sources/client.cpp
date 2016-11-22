#include <curl/curl.h>
#include <iostream>
#include "../include/vk/client.hpp"
#include <exception>

namespace Vk
{

    auto Client::check_connection() -> bool
    {
        CURL *curl = curl_easy_init();

        if (curl)
        {
            std::string fields = "access_token=" + _settings["token"] + "&v=5.59";
            std::string buffer = "";

            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getProfileInfo?");
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fields.length());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

            if (curl_easy_perform(curl) == CURLE_OK)
            {
                Vk::Client::json jsn_obj = json::parse(buffer);
                Vk::Client::json jsn_response = jsn_obj["response"];

                if (!jsn_response.is_null())
                {
                    curl_easy_cleanup(curl);
                    return true;
                }
            }
        }

        curl_easy_cleanup(curl);
        return false;
    }

    auto Client::get_friends() -> std::vector<VkFriend>
    {
	std::vector<VkFriend> friend_list(0);

        CURL *curl = curl_easy_init();

        if (curl)
        {
            std::string fields = "fields=bdate&access_token=" + _settings["token"] + "&v=5.59";
            std::string buffer = "";

            curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/friends.get?");
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fields.length());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

            if (curl_easy_perform(curl) == CURLE_OK)
	    try
            {
                Vk::Client::json jsn_obj = json::parse(buffer);
                Vk::Client::json jsn_response = jsn_obj["response"];
                Vk::Client::json jsn_items = jsn_response["items"];

                for (json::iterator it = jsn_items.begin(); it != jsn_items.end(); ++it)
                {
                    Vk::Client::json jsn_id = it.value()["id"];
                    Vk::Client::json jsn_fname = it.value()["first_name"];
                    Vk::Client::json jsn_lname = it.value()["last_name"];
                    Vk::Client::json jsn_bdate = it.value()["bdate"];
                    Vk::Client::json jsn_online = it.value()["online"];

                    if (!jsn_id.is_null() && !jsn_fname.is_null() && !jsn_lname.is_null() && !jsn_bdate.is_null() && !jsn_online.is_null())
			{
			VkFriend vkfriend(jsn_id, jsn_fname, jsn_lname, jsn_bdate, jsn_online);
			friend_list.push_back(vkfriend);	
			}
		
                }
            }
	    catch(std::exception&)
	    {
		std::cout << "Not json objects" << std::endl;
	    }
        }
        curl_easy_cleanup(curl);
	for (int i=0; i<friend_list.size(); ++i)
	friend_list[i].PrintFriend();
	return friend_list;
    }

    auto Client::write_callback(char* data, size_t size, size_t nmemb, void* buff) -> size_t
    {
        int result = 0;

        if (buff.c_str())
        {
            buff.append(data, size * nmemb);
            result = size * nmemb;
        }

        return result;
    }
}
