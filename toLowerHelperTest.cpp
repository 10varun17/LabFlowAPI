#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include "toLowerHelper.h"

using namespace std;
// using namespace toLowerHelper;

TEST_CASE("Testing functionalities of toLower") 
{
    CHECK("tolower"==toLower("toLower")); // convert all characters to lower case
    CHECK(""==toLower("")); // the empty string also works
    CHECK("12345"==toLower("12345")); // ignore all non-alphabets
}