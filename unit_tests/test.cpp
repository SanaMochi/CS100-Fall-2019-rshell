#ifndef __UNIT_TEST_CPP__
#define __UNIT_TEST_CPP__
#include "gtest/gtest.h"
#include "../header/command.h"
#include "../header/component.h"
#include "../header/parser.h"
#include <string>
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
TEST(Test2, exit_test_1) {
	Component* parser = new Command();
	parser->exit = true;

	EXPECT_TRUE(parser->shouldIExit()== true);
}
TEST(Test2, exit_test_2) {
	Component* parser = new Command();
	parser->exit = false;

	EXPECT_FALSE(parser->shouldIExit());
}
TEST(Test3, reset_vectors) {
	Component* c = new Command();

	c->resetVectors();

	ASSERT_EQ(c->pattern.size(), 0);
//	EXPECT_EQ(c->Component::commands(), 0);
//	EXPECT_EQ(c->Component::to_run.size(), 0);

	EXPECT_EQ(c->numOfCommands, 0);
}

TEST(Test4, getSize) {
	Parser* p = new Parser();
	EXPECT_EQ(p->getSize(), 0);
}

TEST(Test5, single_command_test) {
	system("./integration_tests/single_command_tests.sh");
	std::string output;
	int c;
	FILE* file = std::fopen("data-file", "r");
	if(!file)	
		std::cout << std::endl << "error "  << std::endl;
		
    while ((c = std::fgetc(file)) != EOF) { 
       std::putchar(c);
       if (c == "&&" || c == "||" || c == ";")
		output += c;
    }
	std::fclose(file);
    EXPECT_EQ(output, "");
}

// TEST(Test4, removeNextCommand) {
// 	system("./integration_tests/single_command_tests.sh");
// 	std::string output;
// 	int c;
// 	FILE* file = std::fopen("data-file", "r");
// 	//file.open("data-file");      // open input file
// 	if(!file)	
// 		std::cout << std::endl << "error "  << std::endl;
		
//  		while ((c = std::fgetc(file)) != EOF) { 
// 			std::putchar(c);
//     		numOfCommands++;
//     	}
// 	std::fclose(file);
// // 	Component* c = new Command();
// // 	c->numOfCommands = 1;
// // 	c->fileNames.at(0) = "x";
// // 	c->fileNames.at(1) = "y";
// // 	c->pattern.at(0) = "||";
// // 	c->pattern.at(1) = "&&";
// // 	c->removeNextCommand(0);
// // 	EXPECT_EQ(c->pattern.size(),0);
// 	EXPECT_EQ(c->numOfCommands, 0);
// }

#endif
