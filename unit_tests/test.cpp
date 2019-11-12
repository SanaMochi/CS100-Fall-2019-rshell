#ifndef __UNIT_TEST_CPP__
#define __UNIT_TEST_CPP__
#include "gtest/gtest.h"
#include "../header/command.h"
#include "../header/component.h"
#include "../header/parser.h"
#include <fstream>
#include <iostream> 

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


TEST(Test1, single_command_test) {
	system("./integration_tests/single_command_tests.sh");
	std::string output;
	std::ifstream file;
	file.open("data-file");      // open input file
	if(!file)	
		std::cout << std::endl << "error "  << std::endl;
	std::getline(file, output);
	file.close();
    EXPECT_EQ(output, "hello world");
}

TEST(Test1, multiple_command_test) {
	system("./integration_tests/single_command_tests.sh");
	std::string output;
	std::ifstream file;
	file.open("data-file");      // open input file
	if(!file)	
		std::cout << std::endl << "error "  << std::endl;
	std::getline(file, output);
	file.close();
    EXPECT_EQ(output, "hello world");
}
#endif
