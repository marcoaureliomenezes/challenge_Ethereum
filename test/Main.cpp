#include <gtest/gtest.h>
#include "windows.h"
int main(int argc, char* argv[])	{
	Sleep(2000);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}	
