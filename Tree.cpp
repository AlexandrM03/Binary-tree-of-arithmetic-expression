#include"Tree.h"

Tree* makeTree(std::stringstream& expression) {
	Tree* tree = new Tree;

	if (expression) {
		std::string node;
		expression >> node;

		tree->token = node;
		if (std::isalnum(node[0]) ||
			(node[0] == '-' && std::isalnum(node[1]))) {
			tree->left = nullptr;
			tree->right = nullptr;
		}
		else {
			tree->left = makeTree(expression);
			tree->right = makeTree(expression);
		}
		return tree;
	}
	else {
		return nullptr;
	}
}

void show(Tree* tree, int space) {
	if (tree) {
		show(tree->right, space + 5);
		for (int i = 0; i < space; i++) {
			std::cout << " ";
		}
		std::cout << tree->token << std::endl;
		show(tree->left, space + 5);
	}
}

void printBT(const std::wstring& prefix, const Tree* node, bool isLeft) {
	if (node != nullptr) {
		std::wstring wprefix(prefix.begin(), prefix.end());
		std::wcout << wprefix;

		std::wcout << (isLeft ? L"├──" : L"└──");

		std::wstring token(node->token.begin(), node->token.end());
		std::wcout << L" " << token << std::endl;

		printBT(prefix + (isLeft ? L"│   " : L"    "), node->left, true);
		printBT(prefix + (isLeft ? L"│   " : L"    "), node->right, false);
	}
}

void printBT(const Tree* node) {
	printBT(L"", node, false);
}

double calculate(Tree* tree) {
	if (std::isalpha(tree->token[0])) throw L"\nНевозможно вычислить выражение!";
	if (tree) {
		if (std::isdigit(tree->token[0]) || (tree->token[0] == '-' && std::isdigit(tree->token[1]))) {
			std::stringstream token(tree->token);
			double number;
			token >> number;
			return number;
		}
		std::string token = tree->token;

		if (token == "+") return calculate(tree->left) + calculate(tree->right);
		if (token == "-") return calculate(tree->left) - calculate(tree->right);
		if (token == "*") return calculate(tree->left) * calculate(tree->right);
		if (token == "/") return calculate(tree->left) / calculate(tree->right);
		if (token == "%") return fmod(calculate(tree->left), calculate(tree->right));
		if (token == "^") return pow(calculate(tree->left), calculate(tree->right));
	}
}