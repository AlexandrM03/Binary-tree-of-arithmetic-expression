#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<math.h> // Äëÿ fmod
#include<fcntl.h>
#include<io.h>

struct Tree {
	std::string token;
	Tree* left, * right;
};

Tree* makeTree(std::stringstream& expression);
void show(Tree* tree, int space = 0);
double calculate(Tree* tree);

void printBT(const std::wstring& prefix, const Tree* node, bool isLeft);
void printBT(const Tree* node);