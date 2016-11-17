#include "../include/vk/client.hpp"
#include "validInit.hpp"
#include "catch.hpp"

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
                Vk::Client::json friends = R"([{"bdate":"1.2.3456","first_name":"Никита","id":123456789,"last_name":"Дацук","online":1}])"_json;
                std::map<std::string, std::string> valid_settings(gettingtoken());
                Vk::Client client(valid_settings);
                WHEN("get friends")
                {
                        Vk::Client::json friend_list = client.get_friends();
                        THEN("")
                        {
                                REQUIRE(friends != friend_list);
                        }
                }
        }
}

