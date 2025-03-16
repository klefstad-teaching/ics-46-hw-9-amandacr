F = -std=c++20 -Wall -Wextra -Wpedantic -Wfatal-errors
Z = ICS46_hw8.zip


main: dijkstras_main.cpp
	g++ $F dijkstras.cpp dijkstras_main.cpp -o main

clean:
	/bin/rm -f $P $Z

zip: clean
	zip $Z Makefile main.cpp dijkstras.h small.txt medium.txt large.txt largest.txt