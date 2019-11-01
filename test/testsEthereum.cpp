#include <iostream>
#include "../include/MathExpression.h"
#include <gtest/gtest.h>
#include "windows.h"

MathExpression operation;
// Ethereum tests
TEST(Operation, test1) {
	std::string input = "(4 + 5 * (7 - 3)) - 2";
	int expectResult = (4 + 5 * (7 - 3)) - 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste2) {
	std::string input = "4+5+7/2";
	int expectResult = 4 + 5 + 7 / 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste3) {
	std::string input = "10+1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste4) {
	std::string input = "-10";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
// Exception tests
TEST(Operation, test5) {			//Error 1
	std::string input = "1*(1))";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste6) {		   // Error 2
	std::string input = "1 + (1 + (1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste7) {		  // Error 3
	std::string input = "(1+)1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste8) {		  // Error 4
	std::string input = "1(1+1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, test9) {		  // Error 5
	std::string input = "(1+1)1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste10) {		  // Error 6
	std::string input = "1+ (b)*3";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste11) {		  // Error 7
	std::string input = "(-(1)+1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste12) {		  // Error 8	
	std::string input = "1*(-1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, test13) {		  // Error 9
	std::string input = "*1+1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}

TEST(Operation, Teste14) {		  // Error 10
	std::string input = "1+1*";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}

TEST(Operation, Teste15) {		  // Error 11
	std::string input = "1+(/1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste16) {		  // Many errors	
	std::string input = "2+1)@(-4+)(5)+20//2";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, test17) {
	std::string input = "+4 +-+-+5/2+ 4*(2+1)/2";
	int expectResult = +4 + -+-+5 / 2 + (4 * (2) + 1) / 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste18) {
	std::string input = "(2/1*4/2)-3+(5+(4+(9-3)))/2";
	int expectResult = (2 / 1 * 4 / 2) - 3 + (5 + (4 + (9 - 3))) / 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste19) {
	std::string input = "9/2+1/4*9-5/2 +8*(-+-+-+-2)";
	int expectResult = 9 / 2 + 1 / 4 * 9 - 5 / 2 + 8 * (-+-+-+-2);
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}
TEST(Operation, Teste20) {
	std::string input = "8-2/2+-+-5*8/3+1";
	int expectResult = 8 - 2 / 2 + -+-5 * 8 / 3 + 1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
	Sleep(500);
}