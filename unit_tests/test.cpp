#ifndef __UNIT_TEST_CPP__
#define __UNIT_TEST_CPP__
#include "gtest/gtest.h"
#include "../header/command.h"
#include "../header/component.h"
#include "../header/parser.h"
#include "../header/test.h"
#include <string>
#include <fstream>
#include <iostream> 
#include <stdio.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(TestAssn4, redirect_in) {
	Component* c = new Command();
	Parser p;
	std::string input = "cat < names.txt";
	p.getInput(input);
	p.parse();

	c->runAll(p.getSize(), &p);

	EXPECT_EQ(p.pattern.size(), 2);
//	EXPECT_EQ(p.to_run.size(), 1);
	EXPECT_EQ(p.commands.size(), 3);
}

TEST(TestAssn4, redirect_out_new) {
	Component* c = new Command();
        Parser p;
        std::string input = "echo hi > trial.txt";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

        EXPECT_EQ(p.pattern.size(), 2);
//        EXPECT_EQ(p.to_run.size(), 1);
        EXPECT_EQ(p.commands.size(), 4);
}

TEST(TestAssn4, redirect_out) {
	Component* c = new Command();
        Parser p;
        std::string input = "echo hi >> names.txt";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

        EXPECT_EQ(p.pattern.size(), 2);
//        EXPECT_EQ(p.to_run.size(), 1);
        EXPECT_EQ(p.commands.size(), 4);
}

TEST(TestAssn4, pipe) {
	Component* c = new Command();
        Parser p;
        std::string input = "echo hi | tr A-Z";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

        EXPECT_EQ(p.pattern.size(), 2);
//        EXPECT_EQ(p.to_run.size(), 1);
        EXPECT_EQ(p.commands.size(), 5);
}

TEST(TestAssn4, combined_redirections) {
        Component* c = new Command();
        Parser p;
        std::string input = "cat > names.txt | tr A-Z a-z > newOutputFile1";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

        EXPECT_EQ(p.pattern.size(), 6);
//        EXPECT_EQ(p.to_run.size(), 1);
	EXPECT_EQ(p.commands.size(), 9);
}

/*
TEST(TestAssn4, combined_redirects) {
	Component* c = new Command();
        Parser p;
        std::string input = "cat > names.txt | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

        EXPECT_EQ(p.pattern.size(), 10);
//        EXPECT_EQ(p.to_run.size(), 1);
	EXPECT_EQ(p.commands.size(), 16);
}
*/
TEST(TestAssn3, single_test) {
	Component* c = new Command();
        Parser p;
        std::string input = "test -e src/command.cpp";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

	EXPECT_EQ(p.pattern.size(), 1);
//        EXPECT_EQ(p.to_run.size(), 1);
        EXPECT_EQ(p.commands.size(), 3);

}

TEST(TestAssn3, single_test_brackets) {
	Component* c = new Command();
        Parser p;
        std::string input = "[ -e src/command.cpp ]";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

	EXPECT_EQ(p.pattern.size(), 3);
//        EXPECT_EQ(p.to_run.size(), 1);
        EXPECT_EQ(p.commands.size(), 3);
}

TEST(TestAssn3, multiple_test) {
	Component* c = new Command();
        Parser p;
        std::string input = "test -e src/command.cpp && test -f src/parser.cpp && test -d src";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

	EXPECT_EQ(p.pattern.size(), 3);
//        EXPECT_EQ(p.to_run.size(), 3);
        EXPECT_EQ(p.commands.size(), 11);

}

TEST(TestAssn3, multiple_test_brackets) {
	Component* c = new Command();
        Parser p;
        std::string input = "[ -e src/command.cpp ] && [ -f src/parser.cpp ] && [ -d src ]";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

	EXPECT_EQ(p.pattern.size(), 9);
//        EXPECT_EQ(p.to_run.size(), 3);
        EXPECT_EQ(p.commands.size(), 11);
}

TEST(TestAssn3, parentheses) {
	Component* c = new Command();
        Parser p;
        std::string input = "echo Alhamdulillah || ls && eecho fail || git status";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

	EXPECT_EQ(p.pattern.size(), 4);
//	EXPECT_EQ(p.to_run.size(), 4);
	EXPECT_EQ(p.commands.size(), 10);
}

TEST(TestAssn3, nested_parentheses) {
        Component* c = new Command();
        Parser p;
        std::string input = "echo Alhamdulillah || ls || eecho fail || git status";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

        EXPECT_EQ(p.pattern.size(), 4);
//        EXPECT_EQ(p.to_run.size(), 4);
        EXPECT_EQ(p.commands.size(), 10);
}


TEST(TestAssn2, single_command_test) {
	Component* c = new Command();
	Parser p;
	std::string input = "echo hello";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

	EXPECT_EQ(p.pattern.size(), 1);
//	EXPECT_EQ(p.to_run.size(), 1);
	EXPECT_EQ(p.commands.size(), 2);
}

TEST(TestAssn2, multiple_command_test_without_quotes) {
 Component* c = new Command();
        Parser p;
        std::string input = "ls || git status";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

        EXPECT_EQ(p.pattern.size(), 2);
	EXPECT_EQ(p.commands.size(), 4);
//        EXPECT_EQ(p.to_run.size(), 2);
//        p.printCommands();
}


TEST(TestAssn2, multiple_command_test_with_quotes) {
 Component* c = new Command();
        Parser p;
        std::string input = "echo \"hello && goodbye\" || git status"; 
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

	EXPECT_EQ(p.pattern.size(), 2);
	EXPECT_EQ(p.commands.size(), 5);
//	EXPECT_EQ(p.to_run.size(), 2);
//	p.printCommands();
}

TEST(TestAssn2, exit_test_1) {
	Component* parser = new Command();
	parser->exit_bool = true;

	EXPECT_TRUE(parser->shouldIExit()== true);
}
TEST(TestAssn2, exit_test_2) {
	Component* parser = new Command();
	parser->exit_bool = false;

	EXPECT_FALSE(parser->shouldIExit());
}
TEST(TestAssgn2, reset_vectors) {
	Component* c = new Command();

	c->resetVectors();

	ASSERT_EQ(c->pattern.size(), 0);
	EXPECT_EQ(c->numOfCommands, 0);
}

TEST(TestAssn2, getSize) {
	Parser* p = new Parser();
	EXPECT_EQ(p->getSize(), 0);
}

TEST(TestAssn2, exit_command_test) {
 Component* c = new Command();
        Parser p;
        std::string input = "exit";
        p.getInput(input);
        p.parse();

        c->runAll(p.getSize(), &p);

        EXPECT_EQ(p.pattern.size(), 1);
        EXPECT_EQ(p.argv.size(), 0);
//        EXPECT_EQ(p.to_run.size(), 1);

}

#endif

