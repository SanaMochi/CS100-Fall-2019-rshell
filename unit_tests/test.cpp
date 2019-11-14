#ifndef __UNIT_TEST_CPP__
#define __UNIT_TEST_CPP__
#include "gtest/gtest.h"
#include "../header/command.h"
#include "../header/component.h"
#include "../header/parser.h"
#include <fstream>
#include <iostream> 
#include <stdio.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


TEST(Test1, single_command_test) {
	//remove("data-file");
	system("./integration_tests/single_command_tests.sh");
	std::string output;
	int c;
	FILE* file = std::fopen("data-file", "r");
	//file.open("data-file");      // open input file
	if(!file)	
		std::cout << std::endl << "error "  << std::endl;
		
    while ((c = std::fgetc(file)) != EOF) { 
       std::putchar(c);
       output += c;
    }
	//std::getline(file, output);
	std::fclose(file);
    EXPECT_EQ(output, "hello world\nit works\n");
}

TEST(Test1, multiple_command_test) {
	//remove("data-file");
	system("./integration_tests/multiple_commands_tests.sh");
	std::string output;
	int c;
	FILE* file = std::fopen("data-file", "r");
	//file.open("data-file");      // open input file
	if(!file)	
		std::cout << std::endl << "error "  << std::endl;
		
    while ((c = std::fgetc(file)) != EOF) { 
       std::putchar(c);
       output += c;
    }
	//std::getline(file, output);
	std::fclose(file);
    EXPECT_EQ(output, "hello\nyes\nit works\n");
}


TEST(Test1, commented_command_test) {
	//remove("data-file");
	system("./integration_tests/commented_command_tests.sh");
	std::string output;
	int c;
	FILE* file = std::fopen("data-file", "r");
	//file.open("data-file");      // open input file
	if(!file)	
		std::cout << std::endl << "error "  << std::endl;
		
    while ((c = std::fgetc(file)) != EOF) { 
       std::putchar(c);
       output += c;
    }
	//std::getline(file, output);
	std::fclose(file);
    EXPECT_EQ(output, "it works\n");
}

TEST(Test1, exit_command_test) {
	//remove("data-file");
	system("./integration_tests/exit_command_tests.sh");
	std::string output;
	int c;
	FILE* file = std::fopen("data-file", "r");
	//file.open("data-file");      // open input file
	if(!file)	
		std::cout << std::endl << "error "  << std::endl;
		
    while ((c = std::fgetc(file)) != EOF) { 
       std::putchar(c);
       output += c;
    }
	//std::getline(file, output);
	std::fclose(file);
    EXPECT_EQ(output, "it should work\n");
}
TEST(Test2, exit_command_test) {
	exit = false;
	shouldIExit();
	EXPECT_EQ(output, false);
}
#endif
