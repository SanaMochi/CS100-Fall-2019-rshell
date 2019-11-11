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

//--------------------fix this-------------
TEST(Test1, HelloWorld) {
	std::string s = "echo hello world";
	std::string output;
	std::fstream file; 
    file.open("output.txt", std::ios::out); 
    std::streambuf* coutBuffer = std::cout.rdbuf();	//store cout buffer
    
    std::streambuf* fileBuffer = file.rdbuf();		//store file buffer
    
	Parser p;
	Component* c = new Command();
	p.getInput(s);
	p.parse();
	std::cout.rdbuf(fileBuffer);				//write to file buffer instead of cout
	
	std::cout << "hello world";
	
	c->runAll(p.getSize(), &p);
	std::cout.rdbuf(coutBuffer);				//return to cout buffer
	
	for(int i = 0; i < file.gcount(); i++)
		output += file.get();
	
	
	std::cout << std::endl << "File length: " << file.gcount() << std::endl;
	file.close();
    EXPECT_EQ(output, "hello world");
}
#endif
