#include "../include/MathExpression.h"
#include <vector>
#include <stack>
#include <iostream>
#include "windows.h"
std::string op = "+-*/";

// Public method where the private method are called.
int MathExpression::readLine(std::string input) {
	std::vector<char> v1;
	// First, the string is formatted.
	v1 = MathExpression::formatInput(input);
	// Second, it is tested if the entry is valid.
	bool check = MathExpression::checkLine(v1);
	// If not, the method returns -1.
	if (check == false) { return(-1); }
	// Otherwise, it returns the result of the expression.
	else { return (MathExpression::solveExpression(v1)); }
}
int MathExpression::operation(int a, int b, char c) 
{
	switch (c) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		try {
			if (b == 0) { throw 10; }
		}
		catch (int x) {
			std::cout << "Error " << x << "! Division by 0." << std::endl;
			return -1;
		}
		return a / b;
	default:
		std::cout << "This operator is invalid" << std::endl;
		return -1;
	}
}
std::vector<char> MathExpression::formatInput(std::string input)
{	
	// First spaces are eliminated from the string.
	std::vector<char> v1; std::vector<char> v2;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != ' ') {
			v2.push_back(input[i]);
		}
	}
	// Second, consecultive operator of '+' and '-' are simplified.
	// For example, the sequence '+-+----+++-' is converted in '+'.
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
	// Lastly, the useless operators of '+' are eliminated.
	// For example '+5+(+2)' is converted in '5+(2)'
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
// The solveOperation method makes a simple operation using the stack of numbers and
// stack of operators. In the end stack the result in the stack of numbers.
void MathExpression::solveOperation(std::stack<int>& numStack, std::stack<char>& opStack)
{
	int val1, val2, result; char op;
	val1 = numStack.top();	numStack.pop();
	op = opStack.top();		opStack.pop();
	val2 = numStack.top();	numStack.pop();
	result = MathExpression::operation(val2, val1, op);
	numStack.push(result);
}
// The solveExpression method solves an expression passed by a vector
// and returns an interger.
int MathExpression::solveExpression(std::vector<char> v1)
{
	std::stack<int> numStack; std::stack<char> opStack;
	std::stack<int>* ptNumStack; std::stack<char>* ptOpStack;
	ptNumStack = &numStack; ptOpStack = &opStack;
	// while it runs through the vector elements:
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < op.size(); j++) {
			// If it's an operator this operator is stacked on
			// opStack
			if (v1[i] == op[j]) {
				opStack.push(v1[i]);
				break;
			}
		}
		// If it's a parenthesis being opened this is stacked
		// on opStack too.
		if (v1[i] == '(') { opStack.push(v1[i]); }
		// If it's a literal, it's converted to an integer
		if (isdigit(v1[i])) {
			int number = int(v1[i]) - int('0');
			numStack.push(number);
			// If the last operator is '*' or '/' the operation is solved.
			if ((opStack.size() != 0) && (opStack.top() == '*' || opStack.top() == '/')) {
				MathExpression::solveOperation(*ptNumStack, *ptOpStack);
			}
		}
		// If the vector element is a parenthesis being closed:
		else if (v1[i] == ')') {
			// If the operator on top of the opStack is diferent of "("
			// the operations are resolved till it reaches the "(".
			if (opStack.top() != '(') {
				while (opStack.top() != '(') {
					solveOperation(*ptNumStack, *ptOpStack);
				}
			}
			opStack.pop(); // It removes the operator "(" from the opStack.
			// If the operator on top of opStack is "*" or "/" the operation is solved.
			if ((opStack.size() != 0) && (opStack.top() == '*' || opStack.top() == '/')) {
				solveOperation(*ptNumStack, *ptOpStack);
			}
		}
		// After it solves an expression into a parenthesis, if the operator on top
		// of opStack is "-", and the text operator is "+" or -", the operation is solved.
		if (opStack.size() != 0 && opStack.top() == '-') {
			if (i < v1.size() - 1 && (v1[i + 1] == '+' || v1[i + 1] == '-')) {
				MathExpression::solveOperation(*ptNumStack, *ptOpStack);
			}
		}
	}
	// Finally the values and operators into the stacks are unstacked and
	// the result of the expression is on top of numStack.
	while (!opStack.empty() && numStack.size() > 1) {
		solveOperation(*ptNumStack, *ptOpStack);
	}
	return(numStack.top());
}

bool MathExpression::checkLine(std::vector<char> v1) 
{
	std::vector<char> vCheck; 
	int checkPar = 0, errorSignal = 0;
	try {
		for (int i = 0; i < v1.size(); i++) {
			if (v1[i] != '(' && v1[i] != ')') {
				vCheck.push_back(v1[i]);
			}
			if (v1[i] == '(') { checkPar++; }
			if (v1[i] == ')') { checkPar--; }
			// It checks if there's a parenthesis closed without
			// that one has opened it. Example: '1*(1))'.
			if (checkPar < 0) { throw 1; }
		}
		// It checks if all parenthesis opened were closed
		// Example: '1+(1+(1)'
		if (checkPar != 0) { throw 2; }
		for (int i = 0; i < v1.size() - 1; i++) {
			for (int j = 0; j < op.size(); j++) {
				// It checks if a parenthesis being closed after
				// an operator. Example: '(1+)1'
				if (v1[i] == op[j] && v1[i + 1] == ')') { throw 3; }
			}
			// It Checks if a perenthesis being opened after
			// a number. Example: '1(1+1)'
			if (isdigit(v1[i]) && v1[i + 1] == '(') { throw 4; }
			// Example: '(1+1)1
			if (v1[i] == ')' && isdigit(v1[i + 1])) { throw 5; }
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Irregular use of parenthesis!" << std::endl;
		errorSignal++;
	}
	try {
		for (int i = 0; i < vCheck.size(); i++) {
			// It checks if there's characteres of the expression are valid.
			// The input can jus contains numbers, the operators '+-*/' and '()'.
			if (!isdigit(vCheck[i])) {
				if (vCheck[i] != '+' && vCheck[i] != '-' && vCheck[i] != '*' && vCheck[i] != '/') {
					throw 0;
				}
			}
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Irregular charactere!" << std::endl;
		errorSignal++;;
	}
	// It checks if there's some literal integer bigger than 9.
	try {
		for (int i = 0; i < v1.size() - 1; i++) {
			if (isdigit(v1[i]) && isdigit(v1[i + 1])) { throw 6; }
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - literal is too large!" << std::endl;
		errorSignal++;
	}	 
	try {
		// It checks if the first value is a negative number.
		// Example: '((-1)+1)'
		if (vCheck[0] == '-') { throw 7; }
		for (int i = 0; i < v1.size() - 1; i++) {
			if (v1[i] == '(' && v1[i + 1] == '-') { throw 8; }
		}
		for (int i = 0; i < vCheck.size() - 1; i++) {
			if (vCheck[i] == '*' || vCheck[i] == '/') {
				// It checks if there's a negative number after
				// a '*' or '/' operation. Example: '1*(-1)'
				if (vCheck[i + 1] == '-') { throw 8; }
			}		
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - negative literal!" << std::endl;
		errorSignal++;
	}
	try {
		// It checks if in first position there's operators '*' or '/'
		// Example: '*1+1'
		if (vCheck[0] == '*' || vCheck[0] == '/') { throw 9; }
		for (int i = 0; i < op.size(); i++) {
			// It checks if the last position contains any operator,
			// Example: '1+1+'
			if (vCheck[vCheck.size() - 1] == op[i]) { throw 10; }
			// It checks consecultive operators.
			for (int j = 0; j < vCheck.size() - 1; j++) {
				if (vCheck[j] == op[i]) {
					// Any operator followed by '*' or '/'. Example: '1+(/1)'
					if (vCheck[j + 1] == '*' || vCheck[j + 1] == '/') { throw 11; }
				}
			}
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Operation makes no sense!" << std::endl;
		errorSignal++;
	}
	if (errorSignal > 0) { return false; } 
	else				 { return(true); }
}