# Simple Makefile for LCD Project

build:
	g++ -o lcd LCD2.cpp Services/*.cpp -llgpio

run:
	sudo ./lcd