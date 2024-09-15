#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE

#include <catch2/catch.hpp>
#include "../lab1.h"
#include <cstring> //only for strcmp()

using namespace lab1;

TEST_CASE("getType") {
    std::string s = "null";
    REQUIRE(getType(s) == jsonVoid);

    s = "true";
    REQUIRE(getType(s) == jsonBool);
    s = "false";
    REQUIRE(getType(s) == jsonBool);

    s = "\"abc\"";
    REQUIRE(getType(s) == jsonString);
    s = "\"123\"";
    REQUIRE(getType(s) == jsonString);
    s = "\"123.456\"";
    REQUIRE(getType(s) == jsonString);
    s = "\"true\"";
    REQUIRE(getType(s) == jsonString);
    s = "\"null\"";
    REQUIRE(getType(s) == jsonString);
    s = "\"false\"";
    REQUIRE(getType(s) == jsonString);

    s = "123";
    REQUIRE(getType(s) == jsonLong);
    s = "0";
    REQUIRE(getType(s) == jsonLong);
    s = "69420";
    REQUIRE(getType(s) == jsonLong);
    s = "123";
    REQUIRE(getType(s) == jsonLong);

    s = "0.777";
    REQUIRE(getType(s) == jsonDouble);
    s = "56.78";
    REQUIRE(getType(s) == jsonDouble);

    s = "128,5";
    REQUIRE_THROWS(getType(s));
    s = "some text";
    REQUIRE_THROWS(getType(s));
}
TEST_CASE("parse") {
    REQUIRE_THROWS(parse("abc", "abc"));
    REQUIRE_THROWS(parse("abc", "{{}"));
    REQUIRE_THROWS(parse("abc", "}"));

    REQUIRE(strcmp(parse("abc", "{}"), "struct abc {\n};") == 0);
    REQUIRE(strcmp(parse("abc",
        "{\"s\"    :\"abc\",\n\"l\":123,\"d\":12.     778,\"b1\":   true,\n\n\n\"b2\":false,\"v\":   null}"),
        "struct abc { \n\tchar* s;\n\tlong l;\n\tdouble d;\n\tbool b1;\n\tbool b2;\n\tvoid* v\n};") == 0);

    REQUIRE_THROWS(parse("abc", "{\"s\":\"abc\"\"l\":123,\"d\":12.778,\"b1\":true,\"b2\":false,\"v\":null}"));
    REQUIRE_THROWS(parse("abc", "\"s\":\"abc\",\"l\":123,\"d\":12.778,\"b1\":true,\"b2\":false,\"v\":null}"));
}