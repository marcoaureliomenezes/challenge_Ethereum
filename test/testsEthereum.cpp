#include <iostream>
#include "../include/MathExpression.h"
#include <gtest/gtest.h>

MathExpression operation;
TEST(Oepration, test1) {
	std::string input1 = "(4 + 5 * (7 - 3)) - 2";
	int expectResult = (4 + 5 * (7 - 3)) - 2;
	int softwareResult = operation.readLine(input1);
	//MathExpression operation;
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Operation, Teste2) {
	std::string input = "4+5+7/2";
	int expectResult = 4 + 5 + 7 / 2;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Operation, Teste3) {
	std::string input = "10+1";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}
TEST(Operation, Teste4) {
	std::string input = "-10";
	int expectResult = -1;
	int softwareResult = operation.readLine(input);
	EXPECT_EQ(expectResult, softwareResult);
}