
all: indent

main.cc: Indent.h

indent: main.cc
	g++ -std=c++17 -o $@ $^