//
// Created by Cesar Valdez on 09/02/2023.
//

#include <catch2/catch_test_macros.hpp>
#include "../lib/scanner.h"
#include "catch2/matchers/catch_matchers_vector.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE("Testing tokenizer"){
    auto split = tokenizer("a b c");
    REQUIRE_THAT(split, Catch::Matchers::UnorderedEquals(std::vector<std::string>{ "a", "b", "c" }));

    auto split2 = tokenizer("hello world");
    REQUIRE_THAT(split2, Catch::Matchers::UnorderedEquals(std::vector<std::string>{ "hello", "world" }));

    auto split3 = tokenizer("hello,world", ',');
    REQUIRE_THAT(split3, Catch::Matchers::UnorderedEquals(std::vector<std::string>{ "hello", "world" }));


}