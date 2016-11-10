#include <vk/client.hpp>
#include "catch.hpp"

SCENARIO("checking connection")
{
    GIVEN("wrong token")
    {
        std::map<std::string, std::string> wrong_settings{{"token", "123"}};

        WHEN("client")
        {
            vk::Client client(wrong_settings);

            THEN("connection failed")
            {
                REQUIRE(!client.check_connection());
            }
        }
    }
}
