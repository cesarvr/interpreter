//
// Created by Cesar Valdez on 09/02/2023.
//

#include <catch2/catch_test_macros.hpp>
#include "../lib/parser/scanner.h"
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

TEST_CASE("Testing Scanner simple ()() input"){
    std::string code = "()()";
    Scanner scanner{code};
    auto tokens = scanner.scanTokens();

    REQUIRE( tokens.size() == 5 ); // () () + EOF == 5

    auto t1 = tokens[0];
    REQUIRE( t1.getLexeme() == "(" );

    auto t2 = tokens[1];
    REQUIRE( t2.getLexeme() == ")" );

    auto t3 = tokens[2];
    REQUIRE( t3.getLexeme() == "(" );

    auto t4 = tokens[3];
    REQUIRE( t4.getLexeme() == ")" );

    auto t5 = tokens[4];
    REQUIRE( t5.getLexeme() == "" );
}

TEST_CASE("Testing Scanner multiple operators !*+-/=<> with comments input"){
    std::string code = "!*+-/=<> <= == // operators";
    Scanner scanner{code};
    auto tokens = scanner.scanTokens();

    auto t1 = tokens[0];
    REQUIRE( t1.getLexeme() == "!" );

    auto t2 = tokens[1];
    REQUIRE( t2.getLexeme() == "*" );

    for(auto tk : tokens){

        if(tk.getType() == TokenType::_EOF)
            break;

        auto pos = code.find_first_of(tk.getLexeme());
        REQUIRE( pos != std::string::npos );
    }

    REQUIRE( tokens.size() == 11 );
}