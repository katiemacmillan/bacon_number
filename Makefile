# Makefile
# Makefile for CSC300 Data Structures PA1 Paint Program

# Author:
# Class: CSC300 Data Structures
# Date: Fall 2015

# Usage: make target1 target2 ...

#------------------------------------------------------------------------------

# GNU C/C++ compiler and linker:
LINK = g++

# Preprocessor and compiler flags (turn on warning, optimization, and debugging):
# CPPFLAGS = <preprocessor flags go here>

CFLAGS = -Wall -O -g -std=c++11
CXXFLAGS = $(CFLAGS)

#------------------------------------------------------------------------------
# Targets

all: bacon_number

#------------------------------------------------------------------------------

bacon_number:	Bacon_Number.o process.o search.o globals.o
	$(LINK) -o $@ $^ 

#------------------------------------------------------------------------------

clean:
	rm -f *.o *~ core

cleanall:
	rm -f *.o *~ core bacon_number
