#include <curl/curl.h>
#include <iostream>
#include <vk/client.hpp>
#include <thread>
#include <mutex>

namespace Vk
{
    std::mutex my_mutex;
  
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
	return friend_list;
    }

  
    auto Client::print_friends_using_threads(int num_of_threads, bool flag) -> void
    {
	if (num_of_threads < 1 || num_of_threads > std::thread::hardware_concurrency())
        {
            std::cout << "Wrong number of threads." << std::endl;
            return;
        }

	std::vector<VkFriend> friend_list_for_print = Client::get_friends();
        auto friend_printer = [&friend_list_for_print, &num_of_threads, &flag]() 
        {
		std::lock_guard<std::mutex> lock(my_mutex);
		if (flag)
		{
			std::time_t timer = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::cout << "Start time:" << ctime(&timer) << std::endl;
		}
		for (int i=0; i<friend_list_for_print.size(); i+=num_of_threads)
			friend_list_for_print[i].PrintFriend();
		if(flag)
		{
			std::time_t timer = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::cout << "End time:" << ctime(&timer) << std::endl;
		}
        };
	std::vector<std::thread> vector_of_threads(num_of_threads);
	for (int i = 0; i<num_of_threads; ++i)
		vector_of_threads[i] = std::thread(friend_printer);
	for (int i = 0; i<num_of_threads; ++i)
	{
		if(vector_of_threads[i].joinable())
		vector_of_threads[i].join();
	};
    };


    auto Client::write_callback(char* data, size_t size, size_t nmemb, void* buff) -> size_t
    {
        int result = 0;

        if (buff)
        {
            result = size * nmemb;
            ((std::string*)buff)->append(data, 0, result);
        }

        return result;
    }
}
