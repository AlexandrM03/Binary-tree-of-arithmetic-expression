#include"Parser.h"

int getPriority(std::string binary_operation) {
	if (binary_operation == "+") return 1;
	if (binary_operation == "-") return 1;
	if (binary_operation == "*") return 2;
	if (binary_operation == "/") return 2;
	if (binary_operation == "%") return 2;
	if (binary_operation == "^") return 3;

	return 0;
}

std::string Parser::parse() {
	return parseBinaryExpression();
}

std::string Parser::parseToken() {
	while (isspace(*input)) ++input; // Пропускаем пробелы

	if (isalnum(*input)) { // Достаем число из строки
		std::string number;
		while (isalnum(*input) || *input == '.') number.push_back(*input++);
		return number;
	}

	std::string tokens[] =
	{ "+", "-", "*", "^", "/", "%", "(", ")" }; // Достаем операцию из строки
	for (std::string& t : tokens) {
		if (strncmp(input, t.c_str(), t.size()) == 0) {
			input += t.size();
			return t;
		}
	}

	return "";
}

std::string Parser::parseSimpleExpression() {
	std::string token = parseToken();

	if (token == "(") {
		std::string result = parse(); // Парсим выражение в скобках
		parseToken();
		return result;
	}

	if (isalnum(token[0])) return token; // Если число - сразу заносим в строку
	return token + parseSimpleExpression();
}

std::string Parser::parseBinaryExpression(int min_priority) {
	std::string left_expr = parseSimpleExpression();

	while (true) {
		std::string operation = parseToken();
		int priority = getPriority(operation);
		if (priority <= min_priority) {
			input -= operation.size();
			return left_expr;
		}

		std::string right_expr = parseBinaryExpression(priority);
		left_expr = operation + " " + left_expr + " " + right_expr;
	}
}