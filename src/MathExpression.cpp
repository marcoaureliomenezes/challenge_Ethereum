#include "../include/MathExpression.h"
#include <vector>
#include <stack>
#include <iostream>
#include "windows.h"
std::string op = "+-*/";
int MathExpression::operation(int a, int b, char c) {
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
	std::vector<char> v1; std::vector<char> v2;
	// this first loop puts the string in a vector eliminating spaces
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != ' ') {
			v1.push_back(input[i]);
		}
	}
	// Format 1: Simplifies consecutive signals of '-' and '+'
	// Example: '1--1' is converted in '1+1' and '1+-+-+-1'
	// is converted in '1-1'.
	int i = 0;
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
void MathExpression::solveOperation(std::stack<int>& numStack, std::stack<char>& opStack) 
{
	int val1, val2, conta; char op;
	val1 = numStack.top();	numStack.pop();
	op = opStack.top();		opStack.pop();
	val2 = numStack.top();	numStack.pop();
	conta = MathExpression::operation(val2, val1, op);
	numStack.push(conta);
}
int MathExpression::solveExpression(std::vector<char> v1) 
{
	std::stack<int> numStack; std::stack<char> opStack;
	std::stack<int>* ptNumStack; std::stack<char>* ptOpStack;
	ptNumStack = &numStack; ptOpStack = &opStack;
	// Charging the stacks Operator and number with data from the vector v1
	for (int i = 0; i < v1.size(); i++) {
		// If the element v1[i] is one of these operators, it's stacked in the opStack
		if (v1[i] == '(' || v1[i] == '-' || v1[i] == '+' || v1[i] == '*' || v1[i] == '/') { opStack.push(v1[i]); }
		// If the element v1[i] is a number (0-9), it's transformed to an integer.
		else if (isdigit(v1[i])) {
			int number = int(v1[i]) - int('0');
			// The operation of subtraction is transformed in sum of a positive
			// and negative number. Example: '1-1' is transformed on '1+(-1)'
			// and the number (-1) is stacked.
			if (opStack.size() != 0 && opStack.top() == '-') {
				
				number = -number;
				numStack.push(number);
				opStack.pop(); opStack.push('+');
			}
			else if ((opStack.size() != 0) && (opStack.top() == '*' || opStack.top() == '/')) {
				numStack.push(number);
				MathExpression::solveOperation(*ptNumStack, *ptOpStack);
			}
			// Otherwise the number is just stacked.
			else {
				numStack.push(number);
			}
		}
		// If a parenthesis is closed...
		else if (v1[i] == ')') {
			// and the last operator is the parenthesis being open, they are
			// just removed and it's tested if it's possible to solve a operation.
			// Example: '3+3*(2)' is transformed in '3+3*2' and then '3+6'.
			if (opStack.top() == '(') {
				opStack.pop();
				if ((opStack.size() != 0) && (opStack.top() == '*' || opStack.top() == '/' || opStack.top() == '-' )) {
					MathExpression::solveOperation(*ptNumStack, *ptOpStack);	
				}
			}
			// If the parenthesis is just closed, all the operations, till the software
			// reachs the parenthesis being open, are solved.
			// Example: '4*(2+4-1)' becomes '4*5'.
			else {
				while (opStack.top() != '(') {
					MathExpression::solveOperation(*ptNumStack, *ptOpStack);
				}
				opStack.pop();
			}
		}
	}
		// after all the operations above there's no more high priority
		// operations. Just simple sums. Example: 3+4+(-3)+13. There's also
		// no parenthesis. The one used is just to represent that a subtraction
		// was transformed in a sum of a positive with a negative number.
		// Then, the last stage of the soluction of the expression is made and
		// the result is the only number that is on top of the numStack.
	while (!opStack.empty() && numStack.size() > 1) {
		MathExpression::solveOperation(*ptNumStack, *ptOpStack);
	}
	return(numStack.top());
}
int MathExpression::readLine(std::string input) {
	std::vector<char> v1;
	v1 = MathExpression::formatInput(input);
	bool check = MathExpression::checkLine(v1);
	// If the integrity of the equation are violated, return -1.
	if (check == false) { return(-1); }
	// Otherwise returns the result of the expression.
	else { return (MathExpression::solveExpression(v1)); }
}