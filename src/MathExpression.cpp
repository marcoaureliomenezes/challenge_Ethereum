#include "../include/MathExpression.h"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;
std::string op = "+-*/";

int MathExpression::readLine(string input)  {
	vector<char> v1;
	v1 = MathExpression::formatInput(input);
	bool check = MathExpression::checkLine(v1);
	if (check == false) { 
		return(-1); 
	} else { 
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
			cout << "Error " << x << "  - Division by 0." << endl;
			return -1;
		}
		return a / b;
	default:
		cout << "This operator is invalid" << endl;
		return -1;
	}
}
vector<char> MathExpression::formatInput(string input)  {	
	// Eliminates spaces from the string.
	vector<char> v1; vector<char> v2;
	for (char i:input) {
		if (i != ' ') {
			v2.push_back(i);
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
		} else { v2.push_back(v1[i]); i++; }
	}
	v1.clear();
	// Removes useless operators of '+'.
	for (int i = 0; i < v2.size(); i++) {
		if (v2[i] == '+') {
			if ((i == 0 || i == v2.size())) {}
			else if (isdigit(v2[i - 1]) && (isdigit(v2[i + 1]) || v2[i + 1] == '(')) {
				v1.push_back('+');
			}
		} else { v1.push_back(v2[i]); }
	}
	return v1;
}
void MathExpression::solveOperation(stack<int>& numStack, stack<char>& opStack)  {
	int val1, val2, result; 
	char op;
	val1 = numStack.top();	numStack.pop();
	op = opStack.top();		opStack.pop();
	val2 = numStack.top();	numStack.pop();

	result = MathExpression::operation(val2, val1, op);
	numStack.push(result);
}
int MathExpression::solveExpression(vector<char> v1)  {
	stack<int> numStack; stack<char> opStack;
	stack<int>* ptNumStack; stack<char>* ptOpStack;
	ptNumStack = &numStack; ptOpStack = &opStack;
	vector<char>::iterator itr;
	for (vector<char>::iterator itr = v1.begin(); itr != v1.end(); ++itr) {
		for (int j = 0; j < op.size(); j++) {
			if (*itr == op[j]) {
				opStack.push(*itr);
				break;
			}
		}
		if (*itr == '(') { opStack.push(*itr); }
		if (isdigit(*itr)) {
			int number = int(*itr) - int('0');
			numStack.push(number);
			if ((opStack.size() != 0) && (opStack.top() == '*' || opStack.top() == '/')) {
				MathExpression::solveOperation(*ptNumStack, *ptOpStack);
			}
		}
		else if (*itr == ')') {
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
			if (itr < v1.end()-1 && ( *(itr+1) == '+' || *(itr+1) == '-')) {
				MathExpression::solveOperation(*ptNumStack, *ptOpStack);
			}
		}
	}
	while (!opStack.empty() && numStack.size() > 1) {
		solveOperation(*ptNumStack, *ptOpStack);
	}
	return(numStack.top());
}
bool MathExpression::checkLine(vector<char> v1)  {
	vector<char> vCheck; 
	vector<char>::iterator itr;
	int checkPar = 0, errorSignal = 0;
	try {
		for (char elem:v1) {
			if (elem != '(' && elem != ')') {
				vCheck.push_back(elem);
			}
			if (elem == '(') { checkPar++; }
			if (elem == ')') { checkPar--; }
			// Parenthesis being closed without that one has been opened.
			if (checkPar < 0) { throw 1; }
		}
		// If all parenthes were closed.
		if (checkPar != 0) { throw 2; }
		
		for (itr = v1.begin(); itr != v1.end() - 1; itr++) {
			for (char oper:op) {
				// Operator before parenthesis being closed
				if (*itr == oper && *(itr+1) == ')') { throw 3; }
			}
			// Number before parenthesis being opened.
			if (isdigit(*itr) && *(itr+1) == '(') { throw 4; }
			// Number after parenthesis being closed.
			if (*itr == ')' && isdigit(*(itr+1))) { throw 5; }
		}
	}
	catch (int x) {
		cout << "Error " << x << "  - Irregular use of parenthesis!" << endl;
		errorSignal++;
	}
	try {
		for (char elem:vCheck) {
			// Invalid operators.
			if (!isdigit(elem)) {
				if (elem != '+' and elem != '-' and elem != '*' and elem != '/') {
					throw 6;
				}
			}
		}
	}
	catch (int x) {
		cout << "Error " << x << "  - Irregular charactere!" << endl;
		errorSignal++;
	}
	// Literal integer bigger than 9.
	try {
		for (itr = v1.begin(); itr != v1.end() - 1; itr++) {
			if (isdigit(*itr) && isdigit(*(itr+1))) { throw 7; }
		}
	}
	catch (int x) {
		cout << "Error " << x << "  - Literal is too large!" << endl;
		errorSignal++;
	}	 
	try {
		if (vCheck[0] == '-') { throw 8; }
		for (itr = v1.begin(); itr != v1.end()-1; itr++) {
			if (*itr == '(' || *itr == '*' || *itr == '/') {
				if( *(itr+1) == '-') { throw 9; }
			}
		}
	}
	catch (int x) {
		cout << "Error " << x << "  - Negative literal!" << endl;
		errorSignal++;
	}
	try {
		// Operators '*' or '/' in first position.
		if (vCheck[0] == '*' || vCheck[0] == '/') { throw 10; }
		for (char oper:op) {
			// Any operator in last position.
			if (vCheck[vCheck.size() - 1] == oper) { throw 11; }
			// Operators '*' or '/' after any operator.
			for (itr = vCheck.begin(); itr != vCheck.end()-1; itr++) {
				if (*itr == oper) {
					if (*(itr+1) == '*' || *(itr+1) == '/') { throw 12; }
				}
			}
		}
	}
	catch (int x) {
		cout << "Error " << x << "  - Operation makes no sense!" << endl;
		errorSignal++;
	}
	// If at least one exception has been executed, returns false.
	if (errorSignal > 0) { return false; } 
	else                 { return(true); }
}