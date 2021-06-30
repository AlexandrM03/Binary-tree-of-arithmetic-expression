#pragma once
#include <iostream>

class Parser {
public:
	explicit Parser(char* input) : input(input) {};
	std::string parse();

private:
	std::string parseToken();
	std::string parseSimpleExpression();
	std::string parseBinaryExpression(int min_priority = 0);

	char* input;
};