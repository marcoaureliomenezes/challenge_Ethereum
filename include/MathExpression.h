#pragma once
#include <vector>
#include <stack>
#include <iostream>

class MathExpression{
public:
	int readLine(std::string input);

private:
	int operation(int a, int b, char c);
	std::vector<char> formatInput(std::string);
	bool checkLine(std::vector<char> v1);
	void solveOperation(std::stack<int>& numStack, std::stack<char>& opStack);
	int solveExpression(std::vector<char> v1);
};