C_COMP = gcc
CPP_COMP = g++
SOURCE = sort.c
SOURCE_CPP = sort.cpp
C_FLAGS = -Wall -Wpedantic -Wextra

all:
	$(C_COMP) $(C_FLAGS) $(SOURCE) -o sort.out
	$(CPP_COMP) $(C_FLAGS) --std=c++20 $(SOURCE_CPP) -o sort_cpp.out
