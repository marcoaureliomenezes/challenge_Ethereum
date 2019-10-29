#include "../include/MathExpression.h"
#include <vector>
#include <stack>
#include <iostream>

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
bool MathExpression::checkLine(std::vector<char> v1) {

	std::vector<char> vCheck; int checkPar = 0;
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
		return false;
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
		return false;
	}
	// It checks if there's some literal integer bigger than 9.
	try {
		for (int i = 0; i < v1.size() - 1; i++) {
			if (isdigit(v1[i]) && isdigit(v1[i + 1])) { throw 6; }
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Literal integer bigger than 9!" << std::endl;
		return false;
	}	 
	try {
		// It checks if the first value is a negative number.
		// Example: '((-1)+1)'
		if (vCheck[0] == '-') { throw 7; }
		for (int i = 0; i < vCheck.size() - 1; i++) {
			if (vCheck[i] == '*' || vCheck[i] == '/') {
				// It checks if there's a negative number after
				// a '*' or '/' operation. Example: '1*(-1)'
				if (vCheck[i + 1] == '-') { throw 8; }
			}		
		}
	}
	catch (int x) {
		std::cout << "Error " << x << "  - Literal negative!" << std::endl;
		return false;
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
		return false;
	}
	// These consecultive oeprators are acceptables: (++; *+; /+; -+;--; +-)
	return(true);
}

void MathExpression::solveOperation(std::stack<int>& numStack, std::stack<char>& opStack) {
	int val1, val2, conta; char op;
	val1 = numStack.top();	numStack.pop();
	op = opStack.top();		opStack.pop();
	val2 = numStack.top();	numStack.pop();
	conta = MathExpression::operation(val2, val1, op);
	std::cout << val2 << " " << op << " " << val1 << " = " << conta << ", ";
	numStack.push(conta);
}

int MathExpression::solveExpression(std::vector<char> v1) {
	std::stack<int> numStack; std::stack<char> opStack;
	std::stack<int>* ptNumStack; std::stack<char>* ptOpStack;
	ptNumStack = &numStack; ptOpStack = &opStack;
	// Charging the stacks Operator and number with data from the vector v1
	for (int i = 0; i < v1.size(); i++) {
		// The first and second part are responsible to convert consecultive signals
		// that are valid. Example: '2--2' is stacked as '2+2', '2---2' as '2-2'
		// and '2-+-2' as '2+2'.
		if (v1[i] == '-' && !opStack.empty())
		{	// First part
			if (opStack.top() == '-') { opStack.pop(); opStack.push('+'); }
			else if (opStack.top() == '+') { opStack.push('-'); }
	//		else if (opStack.top() == '(') { opStack.push('*'); numStack.push(-1); }
			else { opStack.push(v1[i]); }	
		}
		else if (v1[i] == '+' && !opStack.empty()) {
			if (opStack.top() == '-') { opStack.push('-'); opStack.push('-');}
			else { opStack.push(v1[i]); }
		}
		// If the element v1[i] is one of these operators, it's stacked in the opStack


		else if (v1[i] == '(' || v1[i] == '-' || v1[i] == '+' || v1[i] == '*' || v1[i] == '/') { opStack.push(v1[i]); }
		// If the element v1[i] is a number (0-9), it's transformed to an integer.
		else if (isdigit(v1[i])) {
			int number = int(v1[i]) - int('0');
			// The operation of subtraction is transformed in sum of a positive
			// and negative number. Example: '1-1' is transformed on '1+(-1)'
			// and the number (-1) is stacked.
			if (opStack.size() != 0 && opStack.top() == '-') {
				opStack.pop(); opStack.push('+');
				number = -number;
				numStack.push(number);
			}
			// If the last operator stacked is '*' or '/' and v1[i] is a number
			// the operation is made. Example:'2*1*(1+1)', as the numbers it's recognized
			// that '2*1' can be solved. Then the result is stacked.
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
				if ((opStack.size() != 0) && (opStack.top() == '*' || opStack.top() == '/' || opStack.top() == '-')) {
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
	}	//2 -+ 2
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

	std::vector<char> v1; std::vector<char> vect;
	// this first loop puts the string in a vector eliminating spaces
	for (int i = 0; i < input.size(); i++) {
		if (input[i] != ' ') {
			v1.push_back(input[i]);
		}
	}
	// Check th integrity of the string parsed.
	bool check = MathExpression::checkLine(v1);
	// If the integrity of the equation are violated, return -1.
	if (check == false) { return(-1); }
	// Otherwise returns the result of the expression.
	else { return (MathExpression::solveExpression(v1)); }
}
