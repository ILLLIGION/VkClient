#include "../include/vk/client.hpp"
#include "validInit.hpp"
#include "catch.hpp"
#include "vector"

SCENARIO("client must check connection using a token")
{
    GIVEN("an invalid token")
    {
        std::map<std::string, std::string> invalid_settings{{"token", "123"}};

        WHEN("initialize client")
        {
            Vk::Client client(invalid_settings);

            THEN("check_connection() must return false")
            {
                REQUIRE(!client.check_connection());
            }
        }
    }

    GIVEN("a valid token")
    {
        std::map<std::string, std::string> valid_settings(gettingtoken());

        WHEN("initialize client")
        {
            Vk::Client client(valid_settings);

            THEN("check_connection() must return true")
            {
                REQUIRE(client.check_connection());
            }
        }
    }
}

SCENARIO("client must get friendlist")
{
        GIVEN("a wrong friendlist, an authorised client")
        {
		std::vector<VkFriend> wrong_friend_list(0);
                Vk::Client::json j_wrong_friend_list = R"([{"bdate":"1.2.3456","first_name":"Никита","id":123456789,"last_name":"Дацук","online":1}])"_json;
		for (Vk::Client::json::iterator it = j_wrong_friend_list.begin(); it !=j_wrong_friend_list.end(); ++it)
                {
                    Vk::Client::json jsn_id = it.value()["id"];
                    Vk::Client::json jsn_fname = it.value()["first_name"];
                    Vk::Client::json jsn_lname = it.value()["last_name"];
                    Vk::Client::json jsn_bdate = it.value()["bdate"];
                    Vk::Client::json jsn_online = it.value()["online"];

                    if (!jsn_id.is_null() && !jsn_fname.is_null() && !jsn_lname.is_null() && !jsn_bdate.is_null() && !jsn_online.is_null())
                        {
                        VkFriend vkfriend(jsn_id, jsn_fname, jsn_lname, jsn_bdate, jsn_online);
                        wrong_friend_list.push_back(vkfriend);
                        }

                }

		std::map<std::string, std::string> valid_settings(gettingtoken());
                Vk::Client client(valid_settings);
                WHEN("get friends")
                {
                        std::vector<VkFriend> friend_list = client.get_friends();
                        THEN("")
                        {
                                REQUIRE(!(friend_list == wrong_friend_list));
                        }
                }
        }
}

