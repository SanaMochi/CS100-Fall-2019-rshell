CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
src/rshell.cpp src/component.cpp src/command.cpp src/parser.cpp src/test.cpp
)

ADD_EXECUTABLE(test
unit_tests/test.cpp src/component.cpp src/command.cpp src/parser.cpp src/test.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)


