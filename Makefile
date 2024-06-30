
all: indent

main.cc: Indent.h

indent: main.cc Indent.h
	g++ -std=c++17 -o $@ $<