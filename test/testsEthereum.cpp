#include <iostream>
#include "../include/MathExpression.h"
#include <gtest/gtest.h>

MathExpression operation;
// Tests sugested by Ethereum
TEST(Ethereum_Tests, test1) {
	std::string input = "(4 + 5 * (7 - 3)) - 2";
	int expectResult = (4 + 5 * (7 - 3)) - 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Ethereum_Tests, Teste2) {
	std::string input = "4+5+7/2";
	int expectResult = 4 + 5 + 7 / 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Ethereum_Tests, Teste3) {
	std::string input = "10+1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Ethereum_Tests, Teste4) {
	std::string input = "-10";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
// Exception tests
TEST(Exception_Tests, test0) {			//Error 0
	std::string input = "1/0";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, test1) {			//Error 1
	std::string input = "1*(1))";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, Teste2) {		   // Error 2
	std::string input = "1 + (1 + (1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, Teste3) {		  // Error 3
	std::string input = "(1-)+1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, Teste4) {		  // Error 4
	std::string input = "1(1+1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, test5) {		  // Error 5
	std::string input = "(1+1)1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, Teste6) {		  // Error 6
	std::string input = "1+ (b)*3";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, Teste7) {		  // Error 7
	std::string input = "(10+1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, Teste8) {		  // Error 8	
	std::string input = "-1*1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, Teste9) {		  // Error 9	
	std::string input = "1*(-1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, test10) {		  // Error 10
	std::string input = "*1+1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}

TEST(Exception_Tests, Teste11) {		  // Error 11
	std::string input = "1+1*";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}

TEST(Exception_Tests, Teste12) {		  // Error 12
	std::string input = "1+(/1)";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Exception_Tests, Teste13) {		  // Many errors	
	std::string input = "2+1)@(-4+)(5)+20//2";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
// Other tests.
TEST(Other_Tests, test1) {
	std::string input = "+4 +5/-+-2+ 4*(2+1)/2";
	int expectResult = +4 + 5 /-+- 2 + 4 * (2 + 1) / 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Other_Tests, Teste2) {
	std::string input = "(2/1*4/2)-3+(5+(4+(9-3)))/2";
	int expectResult = (2 / 1 * 4 / 2) - 3 + (5 + (4 + (9 - 3))) / 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Other_Tests, Teste3) {
	std::string input = "4+8/4*9-8/2 +8*(-+-+-+-2)";
	int expectResult = 4 + 18 - 4 + 8 * (-+-+-+-2);
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Other_Tests, Teste4) {
	std::string input = "8-3/2+-+-5*8/3+1";
	int expectResult = int(8 - 3 / 2 + -+-5 * 8 / 3 + 1);
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}