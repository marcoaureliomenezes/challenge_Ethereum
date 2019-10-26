#include <iostream>
using namespace std;
#include <vector>
#include <stack>
//#include <gtest/gtest.h>
string alg = "0123456789";
string op = "+-*/";

int operation(int a, int b, char c) {
	switch(c) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
			if (b == 0) {
				cout << "Divide Zero. Error: ";
				return -4;
			}
			else
				return a/b;
		default:
			cout << "This operator is invalid" << endl;
	}
}
bool checkLine(vector<char> v1) {
	vector<char> vCheck;
	int checkPar = 0;
	for (int i = 0; i < v1.size(); i++) {
		if (v1[i] != '(' && v1[i] != ')') {
			vCheck.push_back(v1[i]);
		}
		if (v1[i] == '(') {
			checkPar++;
		}
		if (v1[i] == ')') {
			checkPar--;
		}
		if (checkPar < 0) {
			cout << "Irregular use of parenthesis1!" << endl;
			return(false);
		}
	}
	if (checkPar != 0) {
		cout << "Irregular use of parenthesis2!" << endl;
		return(false);
	}
	// Check 1:	If the first value is '-' it means that there's
	// a negative number. Since it was eliminated the parenthesis,
	// expressions such as '-5' or '((-7))' will result also error.
	if (vCheck[0] == '-') {
		cout << "negative number or unary minus" << endl;
		return(false);
	}
	// Check 2: In the first position it's not possible to
	// parse the operators (*/) too, because it makes no sense.
	// For example '(*5+4*(5))' or '(/5+4*(5))' are invalid inputs.
	// The operators (+-) are logically permited, but since we have 
	// the restriction "Check1", just the operator (+) is permited.
	else if (vCheck[0] == '*' || vCheck[0] == '/') {
		cout << "Expression makes no sense1!" << endl;
		return(false);
	}
	// Equally, the last position may not contain any operator,
	// because that makes no sense. 
	// For example: '5+(4-3)-' or '4-1*' are invalid inputs.
	for (int i = 0; i < op.size(); i++) {
		if (vCheck[vCheck.size() - 1] == op[i]) {
			cout << "Expression makes no sense2!" << endl;
			return(false);
		}
	}
	// Check 3: Consecultive operators. Some cases are valid, some not.
	//error: (+*; +/; -*; -/; **; */; /*; //) makes no sense.
	//error: (*-; /-; --; +-) means that there's a negative literal.
	//For example '(2+3)/(-4)', '5*(-4+5)', '5-(-4)'' or '4+(-5)'.
	//acceptables: (++; *+; /+; -+;)

	int annuxa = 1;
	for (int i = 0; i < vCheck.size()-1; i++) {
		for (int j = 0; j < op.size(); j++) {
			if (vCheck[i] == op[j]) {
				if (vCheck[i + 1] == '*' || vCheck[i + 1] == '/') {
					cout << "Makes no sense 3";
					return(false);
				}
				if (vCheck[i + 1] == '-') {
					cout << "Negative number";
					return(false);
				}
				if (vCheck[i + 1] == '+') {
					annuxa--;
				}
			}
		}		
	}
	// Check 4:
	int count = 0;
	for (int i = 0; i < vCheck.size(); i++) {
		if (isdigit(vCheck[i])) {
			count++;
		}
		for (int j = 0; j < op.size(); j++) {
			if (vCheck[i] == op[j]) {
				count--;
			}
		}
	}
	if (count != annuxa) {
		cout << "tem numero maior que 10 nessa budega" << endl;
		return(false);
	}
	return(true);
}
double solve_Unstacked(stack<int> numStack, stack<char> opStack) {
	int val1, val2, conta;
	char op;
	val1 = numStack.top();
	numStack.pop();
	op = opStack.top();
	opStack.pop();
	val2 = numStack.top();
	numStack.pop();
	conta = operation(val2, val1, op);
	cout << val1 << " " << op << " " << val2 << " = " << conta << endl;
	return(conta);
}
int readLine(string input)
{
	vector<char> v1;
	// this first loop puts the string in a vector and eliminates spaces
	for (int i = 0; i < input.size(); i++) {		
		if (input[i] != ' ') {
			v1.push_back(input[i]);
		}
	}
	// Check th integrity of the string parsed.
	bool check = checkLine(v1);
	if (check == false) {
		return(-1);
	}
	// Just if it's all ok with the input, starts the evaluation.
	// That prevents the program to allocate memory without needed. 
	stack<int> numStack2;
	stack<char> opStack2;
	int val1, val2, conta; char op;
	// Charging the stacks Operator and number with data from the vector v1
	for (int i = 0; i < v1.size(); i++) {
		// If the element v1[i] is one of these operators, it's stacked in the opStack
		if (v1[i] == '(' || v1[i] == '+' || v1[i] == '-' || v1[i] == '*' || v1[i] == '/') {
			opStack2.push(v1[i]);
			
		}
		// If the element v1[i] is a number (0-9), it's transformed to an integer. 2 +3 -4 +5 -6
		else if (isdigit(v1[i])) {
			int number = int(v1[i]) - int('0');
			if (opStack2.size() != 0 && opStack2.top() == '-') {
				opStack2.pop(); opStack2.push('+');
				number = -number;
				numStack2.push(number);
			}
			// If the stack of operators is not empty and the last operator stacked is '*' or '/'
			// a operation is made. For example, if the expression is '4*5*(2+1)', as the numbers
			// and operators are stacked, it's recognized that the part '4*5' can be solved.
			// Then it's solved and the result takes place '20*(2+1)'.
			else if ((opStack2.size() != 0) && (opStack2.top() == '*' || opStack2.top() == '/')) {
				val1 = number;				
				op = opStack2.top();				
				opStack2.pop();
				val2 = numStack2.top();				
				numStack2.pop();	
				conta = operation(val2, val1, op);	
				cout << val1 << " " << op << " " << val2 << " = "<< conta << endl;
				numStack2.push(conta);
			}
			else {
				numStack2.push(number);
			}
		}
		else if (v1[i] == ')') {
			if (opStack2.top() == '(') {
				opStack2.pop();
				if ((opStack2.size() != 0) && (opStack2.top() == '*' || opStack2.top() == '/')) {
					val1 = numStack2.top();
					numStack2.pop();
					op = opStack2.top();
					opStack2.pop();
					val2 = numStack2.top();
					numStack2.pop();
					conta = operation(val2, val1, op);
					cout << val1 << " " << op << " " << val2 << " = " << conta << endl;
					numStack2.push(conta);
				}

			}
			else {
				while (opStack2.top() != '(') {
					val1 = numStack2.top();
					numStack2.pop();
					op = opStack2.top();
					cout << op << endl;
					opStack2.pop();
					val2 = numStack2.top();
					numStack2.pop();
					if (op == '-' || op == '/') {
						conta = operation(val2, val1, op);
					}
					else {
						conta = operation(val1, val2, op);
					}
					cout << val1 << " " << op << " " << val2 << " = " << conta << endl;
					numStack2.push(conta);
				}
				opStack2.pop();
			}
			
		}
	}
	while (opStack2.size() > 0 && numStack2.size() > 1) {
		val1 = numStack2.top();
		numStack2.pop();
		op = opStack2.top();
		opStack2.pop();
		val2 = numStack2.top();
		numStack2.pop();
		conta = operation(val2, val1, op);
		cout << val1 << " " << op << " " << val2 << " = " << conta << endl;
		numStack2.push(conta);
	}
	int result = numStack2.top();
	// Destructors
	numStack2.~stack();	opStack2.~stack();	v1.~vector();
	return(result);
}
int main()	{
	string input1 = "2 +3 -4 +5 -6";						cout << "teste1: " << (2 + 3 - 4 + 5 - 6) << endl; 
	cout << " codigo: " << readLine(input1) << endl;
	string input2 = "4/2+4*3+3-2+4*2/2";					cout << "teste2: " << (4 / 2 + 4 * 3 + 3 - 2 + 4 * 2 / 2) << endl;
	cout << " codigo: " << readLine(input2) << endl;
	string input3 = "(4-2)*(8/4) -1*6";						cout << "teste3: " << ((4 - 2) * (8 / 4) - 1 * 6) << endl;
	cout << " codigo: " << readLine(input3) << endl;
	string input4 = "(4)*(6)-4 +(2*3)/2";					cout << "teste4: " << ((4) * (6) - 4 + (2 * 3) / 2) << endl;
	cout << " codigo: " << readLine(input4) << endl;
	string input5 = "((4-2)*(6)-4)/2 -5";					cout << "teste5: " << (((4 - 2) * (6) - 4) / 2 - 5) << endl;
	cout << " codigo: " << readLine(input5) << endl;
	string input6 = "((5)) + 6 / 2 - 5 * (5 - 4) * 6 ";		cout << "teste6: " << ((5)) + 6 / 2 - 5 * (5 - 4) * 6 << endl;
	cout << " codigo: " << readLine(input6) << endl;
	string input7 = "((5))+6/2-5";
	string input8 = "(4)*(6)-4 +2";
	string input9 = "(4)*(6)-4 +2";
	string input10 = "4+5+7/2";
	string input11 = "2+3+(4)+6/2";
	string input12 = "-10";
	cout <<"codigo: " << readLine(input12) << endl;

}
