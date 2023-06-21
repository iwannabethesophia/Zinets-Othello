CXX_FILES = src/main.cpp src/bit.cpp src/board.cpp src/myrandom.cpp src/perft.cpp src/protocol.cpp
CXX_FLAGS = -DDEBUG -std=c++17 -O2 -Wall -Wshadow -Wunused
CXX_OUTPUT = zinets

ifeq ($(OS),Windows_NT)
	CXX_COMPILER = g++
else
	CXX_COMPILER = clang++
endif

main:
	$(CXX_COMPILER) $(CXX_FILES) -o $(CXX_OUTPUT) $(CXX_FLAGS)

test:
	$(CXX_COMPILER) $(CXX_FILES) -o $(CXX_OUTPUT) $(CXX_FLAGS)
	@echo Run zinets
	@./$(CXX_OUTPUT)