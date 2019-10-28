
#include "MathExpression.h"
#include <vector>
#include <stack>
#include <iostream>

std::string op = "+-*/";


int MathExpression::readLine(std::string input) {
	std::vector<char> v1;
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


int MathExpression::operation(int a, int b, char c) {
	switch (c) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		if (b == 0) {
			std::cout << "Divide Zero. Error: ";
			return -4;
		}
		else
			return a / b;
	default:
		std::cout << "This operator is invalid" << std::endl;
	}
}

bool MathExpression::checkLine(std::vector<char> v1) {
	std::vector<char> vCheck;
	int checkPar = 0;
	for (int i = 0; i < v1.size(); i++) {
		if (v1[i] != '(' && v1[i] != ')') {
			vCheck.push_back(v1[i]);
		}
		if (v1[i] == '(') { checkPar++; }
		if (v1[i] == ')') { checkPar--; }
		// Check 1: Checks if there's a parenthesis closed without
		// that one has opened it. Example: '2*(3-1))+1'.
		if (checkPar < 0) {
			std::cout << "Irregular use of parenthesis1!" << std::endl;
			return(false);
		}
	}
	// Check 2: It checks if there's some place where a parenthesis
	// being closed follows a operator. Example: '(9+)2'
	for (int i = 1; i < v1.size() - 1; i++) {
		for (int j = 0; j < op.size(); j++) {
			if (v1[i] == op[j] && v1[i + 1] == ')') {
				std::cout << "Operator before a parenthesis being closed!" << std::endl;
				return(false);
			}
		}
	}
	// Check3: It checks if there's some literal integer bigger than
	// 9. If a element vCheck[i] is a digit the next must be a operator.
	// Since it's being used vCheck vector, check 2 also gets a irregular
	// use of parenthesis, such as '9(2)-1'.
	for (int i = 0; i < vCheck.size() - 1; i++) {
		if (isdigit(vCheck[i]) && isdigit(vCheck[i + 1])) {
			std::cout << "Literal bigger than 9 or irregular use of parenthesis!" << std::endl;
			return(false);
		}
	}

	// Check 4: Checks in the whole expression if some parenthesis 
	// were not closed. Example: '2+3(-2+(2)'.
	if (checkPar != 0) {
		std::cout << "Irregular use of parenthesis2!" << std::endl;
		return(false);

	}
	// Check 5:	Checks if the first value is a negative number. 
	// Since in vCheck parenthesis were eliminated, for example
	// '-5' or '((-7))' will generate error.
	if (vCheck[0] == '-') {
		std::cout << "negative number or unary minus" << std::endl;
		return(false);
	}
	// Check 6: Checks if in first position there's the operators
	// (*/) because it makes no sense. Examples: '*5+4' or '/5-4'.
	else if (vCheck[0] == '*' || vCheck[0] == '/') {
		std::cout << "Expression makes no sense1!" << std::endl;
		return(false);
	}
	// Check 7: Checks if the last position contains any operator,
	// because that makes no sense too. 
	// Examples: '5+4-' or '4-1*' are invalid inputs.
	for (int i = 0; i < op.size(); i++) {
		if (vCheck[vCheck.size() - 1] == op[i]) {
			std::cout << "Expression makes no sense2!" << std::endl;
			return(false);
		}
	}
	// Check 8: Consecultive operators. Some cases it makes no sense.
	// Examples: (+*; +/; -*; -/; **; */; /*; //) -> '4+*5' or '3+*2'.
	// Other cases it means a negative literal, condition not permited.
	// Examples: (*-; /-) -> '2/-4' or '5*(-4)'. 
	// These consecultive oeprators are acceptables: (++; *+; /+; -+;--; +-)
	for (int i = 0; i < vCheck.size() - 1; i++) {
		for (int j = 0; j < op.size(); j++) {
			if (vCheck[i] == op[j]) {
				if (vCheck[i + 1] == '*' || vCheck[i + 1] == '/') {
					std::cout << "Makes no sense 3" << std::endl;
					return(false);
				}
				if (vCheck[i + 1] == '-') {
					std::cout << "Negative number";
					return(false);
				}
			}
		}
	}
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
		// If the element v1[i] is one of these operators, it's stacked in the opStack
		if (v1[i] == '(' || v1[i] == '+' || v1[i] == '-' || v1[i] == '*' || v1[i] == '/') {
			opStack.push(v1[i]);
		}
		// If the element v1[i] is a number (0-9), it's transformed to an integer.
		else if (isdigit(v1[i])) {
			int number = int(v1[i]) - int('0');
			// The operation of subtraction is tranformed in a sum of a pisitive number
			// and a negative number. Example: '5-4' is transformed on  5+(-4).
			if (opStack.size() != 0 && opStack.top() == '-') {
				opStack.pop(); opStack.push('+');
				number = -number;
				numStack.push(number);
			}
			// If the stack of operators is not empty and the last operator stacked is '*' or '/'
			// the operation is made. Example: if the expression is '4*5*(2+1)', as the numbers
			// and operators are stacked, it's recognized that the part '4*5' can be solved.
			// Then it's solved and the result takes place '20*(2+1)'.
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
	}
		// after all the operations above there's no more high priority
		// operations. Just simple sums. Example: 3+4+(-3)+13. There's also
		// no parenthesis. The one used is just to represent that a subtraction
		// was transformed in a sum of a positive with a negative number.
		// Then, the last stage of the soluction of the expression is made and
		// the result is the only number that is on top of the numStack.
	while (opStack.size() > 0 && numStack.size() > 1) {
		MathExpression::solveOperation(*ptNumStack, *ptOpStack);
	}
	return(numStack.top());
}


