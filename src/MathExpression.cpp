#include "../include/MathExpression.h"
#include <vector>
#include <stack>
#include <iostream>
std::string op = "+-*/";

int MathExpression::readLine(std::string input)  {
	std::vector<char> v1;
	v1 = MathExpression::formatInput(input);
	bool check = MathExpression::checkLine(v1);
	if (check == false) { 
		return(-1); 
	}
	else { 
		return (MathExpression::solveExpression(v1)); 
	}
}
int MathExpression::operation(int a, int b, char c)  {
	switch (c) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		try {
			if (b == 0) { throw 0; }
		}
		catch (int x) {
			std::cout << "Error " << x << "  - Division by 0." << std::endl;
			return -1;
		}
		return a / b;
	default:
		std::cout << "This operator is invalid" << std::endl;
		return -1;
	}
}
std::vector<char> MathExpression::formatInput(std::string input)  {	
	// Eliminates spaces from the string.
	std::vector<char> v1; std::vector<char> v2;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != ' ') {
			v2.push_back(input[i]);
		}
	}
	// Simplifies consecultive operators of '+' and '-'.
	int i = 0, k = v2.size() - 1;
	while (v2[k] == '+' || v2[k] == '-') {
		k--;
	}
	for (int i = 0; i < k + 1; i++) {
		v1.push_back(v2[i]);
	}
	v2.clear();
	while (i < v1.size()) {
		if (v1[i] == '+' || v1[i] == '-') {
			int count = 0;
			int j = 0;
			while (v1[i + j] == '+' || v1[i + j] == '-') {
				if (v1[j + i] == '-') { count++; }
				j++;
			}
			i = i + j;
			if (count % 2 == 0) { v2.push_back('+'); }
			else if (count % 2 != 0) { v2.push_back('-'); }
		}
		else { v2.push_back(v1[i]); i++; }
	}
	v1.clear();
	// Removes useless operators of '+'.
	for (int i = 0; i < v2.size(); i++) {
		if (v2[i] == '+') {
			if ((i == 0 || i == v2.size())) {}
			else if (isdigit(v2[i - 1]) && (isdigit(v2[i + 1]) || v2[i + 1] == '(')) {
				v1.push_back('+');
			}
		}
		else { v1.push_back(v2[i]); }
	}
	return v1;
}
void MathExpression::solveOperation(std::stack<int>& numStack, std::stack<char>& opStack)  {
	int val1, val2, result; char op;
	val1 = numStack.top();	numStack.pop();
	op = opStack.top();		opStack.pop();
	val2 = numStack.top();	numStack.pop();
	result = MathExpression::operation(val2, val1, op);
	numStack.push(result);
}
int MathExpression::solveExpression(std::vector<char> v1)  {
	std::stack<int> numStack; std::stack<char> opStack;
	std::stack<int>* ptNumStack; std::stack<char>* ptOpStack;
	ptNumStack = &numStack; ptOpStack = &opStack;
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < op.size(); j++) {
			if (v1[i] == op[j]) {
				opStack.push(v1[i]);
				break;
			}
		}
		if (v1[i] == '(') { opStack.push(v1[i]); }
		if (isdigit(v1[i])) {
			int number = int(v1[i]) - int('0');
			numStack.push(number);
			if ((opStack.size() != 0) && (opStack.top() == '*' || opStack.top() == '/')) {
				MathExpression::solveOperation(*ptNumStack, *ptOpStack);
			}
		}
		else if (v1[i] == ')') {
			if (opStack.top() != '(') {
				while (opStack.top() != '(') {
					solveOperation(*ptNumStack, *ptOpStack);
				}
			}
			opStack.pop(); 
			if ((opStack.size() != 0) && (opStack.top() == '*' || opStack.top() == '/')) {
				solveOperation(*ptNumStack, *ptOpStack);
			}
		}
		if (opStack.size() != 0 && opStack.top() == '-') {
			if (i < v1.size() - 1 && (v1[i + 1] == '+' || v1[i + 1] == '-')) {
				MathExpression::solveOperation(*ptNumStack, *ptOpStack);
			}
		}
	}
	while (!opStack.empty() && numStack.size() > 1) {
		solveOperation(*ptNumStack, *ptOpStack);
	}
	return(numStack.top());
}
bool MathExpression::checkLine(std::vector<char> v1)  {
	std::vector<char> vCheck; 
	int checkPar = 0, errorSignal = 0;
	try {
		for (int i = 0; i < v1.size(); i++) {
			if (v1[i] != '(' && v1[i] != ')') {
				vCheck.push_back(v1[i]);
			}
			if (v1[i] == '(') { checkPar++; }
			if (v1[i] == ')') { checkPar--; }
			// Parenthesis being closed without that one has been opened.
			if (checkPar < 0) { throw 1; }
		}
		// If all parenthes were closed.
		if (checkPar != 0) { throw 2; }
		for (int i = 0; i < v1.size() - 1; i++) {
			for (int j = 0; j < op.size(); j++) {
				// Operator before parenthesis being closed
				if (v1[i] == op[j] && v1[i + 1] == ')') { throw 3; }
			}
			// Number before parenthesis being opened.
			if (isdigit(v1[i]) && v1[i + 1] == '(') { throw 4; }
			// Number after parenthesis being closed.
			if (v1[i] == ')' && isdigit(v1[i + 1])) { throw 5; }
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Irregular use of parenthesis!" << std::endl;
		errorSignal++;
	}
	try {
		for (int i = 0; i < vCheck.size(); i++) {
			// Invalid operators.
			if (!isdigit(vCheck[i])) {
				if (vCheck[i] != '+' && vCheck[i] != '-' && vCheck[i] != '*' && vCheck[i] != '/') {
					throw 6;
				}
			}
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Irregular charactere!" << std::endl;
		errorSignal++;
	}
	// Literal integer bigger than 9.
	try {
		for (int i = 0; i < v1.size() - 1; i++) {
			if (isdigit(v1[i]) && isdigit(v1[i + 1])) { throw 7; }
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Literal is too large!" << std::endl;
		errorSignal++;
	}	 
	try {
		if (vCheck[0] == '-') { throw 8; }
		for (int i = 0; i < v1.size() - 1; i++) {
			if (v1[i] == '(' || v1[i] == '*' || v1[i] == '/') {
				if (v1[i + 1] == '-') { throw 9; }
			}
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Negative literal!" << std::endl;
		errorSignal++;
	}
	try {
		// Operators '*' or '/' in first position.
		if (vCheck[0] == '*' || vCheck[0] == '/') { throw 10; }
		for (int i = 0; i < op.size(); i++) {
			// Any operator in last position.
			if (vCheck[vCheck.size() - 1] == op[i]) { throw 11; }
			// Operators '*' or '/' after any operator.
			for (int j = 0; j < vCheck.size() - 1; j++) {
				if (vCheck[j] == op[i]) {
					if (vCheck[j + 1] == '*' || vCheck[j + 1] == '/') { throw 12; }
				}
			}
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Operation makes no sense!" << std::endl;
		errorSignal++;
	}
	// If at least one exception has been executed, returns false.
	if (errorSignal > 0) { return false; } 
	else				 { return(true); }
}