#include <iostream>
#include "MathExpression.h"

int main()	{
	MathExpression operation;
	std::string input = "";
	std::cout << "Mode user can insert a input. Type 'quit' to get out!"<< std::endl;
	while(1) {
		std::cout << "Type a expression: ";
		std::cin >> input;
		if (input == "quit") { break; }
		else { 
			std::cout<<"result: "<< operation.readLine(input)<< std::endl; }
	}
	std::cout << "Tests required: " << std::endl;
	std::string input1 = "2 + 3 -4 +5 -6";						
	std::cout << "teste1: " << (2 + 3 - 4 + 5 - 6) << std::endl;
	std::cout << "Codigo: " << operation.readLine(input1) << std::endl;
	std::string input2 = "4/2+4*3+3-2+4*2/2";
	std::cout << "teste2: " << (4 / 2 + 4 * 3 + 3 - 2 + 4 * 2 / 2) << std::endl;
	std::cout << "Codigo: " << operation.readLine(input2) << std::endl;
	std::string input3 = "(4-2)*(8/4) -1*6";
	std::cout << "teste3: " << ((4 - 2) * (8 / 4) - 1 * 6) << std::endl;
	std::cout << "Codigo: " << operation.readLine(input3) << std::endl;
	std::string input4 = "(4)*(6)-4 +(2*3)/2";
	std::cout << "teste4: " << ((4) * (6) - 4 + (2 * 3) / 2) << std::endl;
	std::cout << "Codigo: " << operation.readLine(input4) << std::endl;
	std::string input5 = "((4-2)*(6)-4)/2 -5";					
	std::cout << "teste5: " << (((4 - 2) * (6) - 4) / 2 - 5) << std::endl;
	std::cout << "Codigo: " << operation.readLine(input5) << std::endl;
	std::string input6 = "((5)) + 6 / 2 - 5 * (5 - 4) * 6 ";
	std::cout << "teste6: " << ((5)) + 6 / 2 - 5 * (5 - 4) * 6 << std::endl;
	std::cout << "Codigo: " << operation.readLine(input6) << std::endl;

	std::string input7 = "((5))+6/2-5";
	std::string input8 = "(4)*(6)-4 +2";
	std::string input9 = "(4)*(6)-4 +2";
	std::string input10 = "4+75+7/2";
	std::string input11 = "2+3+(4)+6/2";
	std::string input12 = "2+(-5+5)";
	std::cout <<"codigo: " << operation.readLine(input12) << std::endl;
	// create console
			 // make comments
			 // write unit tests
}
