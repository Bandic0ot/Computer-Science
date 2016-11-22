# Makefile for vecalc application.
# Author: Matthew Mulenga

CXXFLAGS = -Wall -Wextra

.PHONY: all clean

all: vecalc input

VECALC_OBJECT = calc_state.o vecalc.o

vecalc: $(VECALC_OBJECT)
	g++ $(VECALC_OBJECT) -o vecalc

input: input_state.o
	g++ input_state.o -o input

calc_state.o: calc_state.cc calc_state.h
	g++ $(CXXFLAGS) -c calc_state.cc

vecalc.o: vecalc.cc vecalc.h
	g++ $(CXXFLAGS) -c vecalc.cc

input_state.o: input_state.cc input_state.h
	g++ $(CXXFLAGS) -c input_state.cc

clean:
	rm -f calc_state.o vecalc.o input_state.o
	rm -f vecalc input
