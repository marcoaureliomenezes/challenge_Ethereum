#pragma once
#include <vector>
#include <stack>
#include <iostream>

class MathExpression{
public:
	/** @brief Public method that calls the other private methods to solve
	 * the mathematical expression passed as parameter.
	 *
	 *  First, the string  passed is formatted by the method formatInput.
	 * 	Then the validity of the input is check by the method checkLine.
	 *  If it's valid the result is calculated by the method solveExpression. 
	 *  Otherwise it returns -1.
	 *
	 *	@param input The expression which the user wants to get the result.
	 *	@return Result of mathematical expression, of integer type.
	 */
	int readLine(std::string input);
private:

	/** @brief Private method that solve a simple mathematical operation.
	 *
	 *  Calculates a simple operation using 2 integer values and one character
	 * 	that represents a addition, subtraction, multiplication or division.
	 *  In case of a number divided by zero or a invalid operator passed it 
	 *	generates an exception with a message and the method returns -1.
	 *
	 *	@param a First integer value of the operation.
	 *  @param b Second integer value of the operation.
	 *  @param c Operator used (+,-,*,/).
	 *	@return Result of the operation, of integer type.
	 */
	int operation(int, int, char);

	/** @brief Private method that formats the input passed as parameter and
	 *  returns a vector.
	 *
	 *  It eliminates spaces of the input, simplifies consecultive operators
	 * 	of '+' or '-'. Example: '--' is converted in '+'.
	 *  Lastly it eliminates useless '+' operators are eliminated.
	 *	For example '+1+(+1)' is converted in '1+(1)'
	 *
	 *	@param input The string containing the mathematical expression.
	 *	@return Vector of the type char, containing the input formatted.
	 */
	std::vector<char> formatInput(std::string input);

	/** @brief Private method that uses the stacks numStack and opStack
	 *		   from the method solveExpression to solve an operation.
	 *
	 *  The parameters passed as reference are two stacks from the method
	 * 	solveExpression. The method does the following tasks:
	 *  * gets a number of the numStack and unstacks it from the stack,
	 *	* gets an operator from the opStack and unstacks it from the stack,
	 *  * gets another number of the numStack and unstacks it from the stack, 
	 *  * uses the 2 two numbers and operator to make a simple operation,
	 *	* stacks the result on top of numStack.
	 *
	 *	@param &numStack: Address of the stack of numbers in solveExpression method.
	 *	@param &opStack: Address of the stack of operators in solveExpression method.
	 *	@return Void.
	 */
	void solveOperation(std::stack<int>& numStack, std::stack<char>& opStack);

	/** @brief Private method that solves an expression passed by a vector
     *  and returns an integer.
	 *
	 *  While it runs through the vector elements:
	 * 	* If it's an operator, it is stacked on opStack.
	 *  * If it's a parenthesis being opened, it's stacked on opStack too.
	 *	* If it's a literal, it's converted to an integer and the if the operator
	 *    on top of opStack is '*' or '/', the operation is solved.
	 *  * If the vector element is a parenthesis being closed and the operator
	 *	  on top of the opStack is diferent of "(", then operations are resolved till
	 *    it reaches the "(", that is after that removed.
	 *  * Then, if the operator on top of opStack is "*" or "/" (high priority)
	 *	  the operation is solved.
	 *	* If the operator on top of opStack is "-", and the next operator is "+" or -",
	 *	  the operation is solved. 
	 *	* Finally the values and operators into the stacks are unstacked with simple
	 *    operations and the result of the expression is stacked on top of numStack.
	 *
	 *	@param v1: Vector containing the input provided after formatting.
	 *	@return int: Result of the mathematical expressin on top of numStack.
	 */
	int solveExpression(std::vector<char> v1);

	/** @brief Private method that checks if a input passed as parameter is valid.
	 *
	 *  The validity of an input passed as vector of char is tested. Wether for any
	 *  reasons it's not valid exceptions are generated and error messages are printed.
	 * 	* Error 1: If there's a parenthesis closed without that one has opened it.
	 *	  Example: '1*(1))'.
	 *  * Error 2: If some parenthesis opened were closed.
	 *	  Example: '1+(1+(1)'.
	 *	* Error 3: If a parenthesis was closed after an operator
	 *	  Example: '(1+)1'.
	 *  * Error 4: If a parenthesis was opened after a number
	 *	  Example: '1(1+1)'.
	 *	* Error 5: If there's a number after a parenthesis is closed. 
	 *	  Example: '(1+1)1'.
	 *	* Error 6: If there's invalid characteres in the expression.
	 *	  Example: '(1@1)%1'.
	 *	* Error 7: If there's some literal bigger than 9.
	 *	  Example: '10+1'.
	 *	* Error 8: If the first value is a negative number.
	 *	  Example: '-1+1'.
	 *	* Error 9: If there's some minus operator after the operators '/*('
	 *	  Example: '1/-1' or '1*(-1)'.
	 *	  Error 10: If the first element is an operator '*' or '/'
	 *	  Example: '*1+1'.
	 *	  Error 11: If the last element is an operator,
	 *	  Example: '1+1-'.
	 *	  Error 12: If any operator is followed by '*' or '/'.
	 *	  Example: '1+(/1)'.
	 *	@param v1: Vector containing the input provided after formatting.
	 *	@return bool: True if the input is valid, false if it's not.
	 */
	bool checkLine(std::vector<char> v1);
};