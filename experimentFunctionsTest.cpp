#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "experimentFunctions.h"

TEST_CASE("Testing this class functionality") 
{
    SUBCASE("This function should do that")
    {
        CHECK(1==1);
    }
}