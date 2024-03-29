//
// Created by Cesar Valdez on 09/02/2023.
//

#include <catch2/catch_test_macros.hpp>
#include "../lib/parser/scanner.h"
#include "catch2/matchers/catch_matchers_vector.hpp"

std::vector<Token> run_scanner(std::string code) {
    Scanner scanner{code};
    auto tokens = scanner.scanTokens();
    return tokens;
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

TEST_CASE("No Tokens") { 
    auto tokens = run_scanner("");
    REQUIRE(tokens[0].getType() == _EOF);
}

TEST_CASE("Testing inline /**/ comments") {
    std::string code = "/**/";
    auto tokens = run_scanner(code);
    REQUIRE(tokens[0].getType() == _EOF);
}

TEST_CASE("Testing multiline comments") {
    std::string code = "/* hello \n* world \n**/";
    Scanner scanner{code};
    auto tokens = scanner.scanTokens();
    
    REQUIRE(tokens[0].getType() == _EOF);
    REQUIRE(scanner.getCurrentLine() == 3);
}

TEST_CASE("Testing Scanner multiple operators !*+-/=<> with comments input"){
    std::string code = "!*+-/=<> <= == // operators";
    auto tokens = run_scanner(code);

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

TEST_CASE("Testing Scanner parsing string values") {
    std::string code = "\"hello world\"; // operators";
    auto tokens = run_scanner(code);

    for(auto token : tokens){
        if(token.getType() == STRING){
            REQUIRE( token.getLiteral().getString() == "hello world" );
        }
    }
}

TEST_CASE("Testing Scanner parsing integers values") {
    std::string code = "/* Reading an Integer */ 4";
    auto tokens = run_scanner(code);

    auto numberToken = tokens[0];
    REQUIRE( numberToken.getLiteral().getDouble() == 4 );
}

TEST_CASE("Testing Scanner parsing float values") {
    std::string code = "14.4 /* Float */";
    auto tokens = run_scanner(code);

    auto numberToken = tokens[0];
    REQUIRE( numberToken.getLiteral().getDouble() == 14.4 );
}

TEST_CASE("Testing Scanner parsing logic OR") {
    std::string code = "or //OR operator";
    auto or_tokens = run_scanner(code);

    auto orToken = or_tokens[0];
    REQUIRE( orToken.getType() == OR );

    std::string code2 = "\"or\" //Checking that or inside string are parsed correctly.";
    auto tokens = run_scanner(code2);

    auto orStrToken = tokens[0];
    REQUIRE( orStrToken.getLiteral().getString() == "or" );
    REQUIRE( orStrToken.getType() != OR );
}

