all: size newer dirlist

size: size.cpp
	g++ -o size size.cpp

newer: newer.cpp
	g++ -o newer newer.cpp

dirlist: dirlist.cpp
	g++ -o dirlist dirlist.cpp
