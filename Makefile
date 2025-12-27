# Simple Makefile for LCD Project

build:
	g++ -o lcd LCD2.cpp Services/*.cpp -llgpio -lcurl

run:
	sudo ./lcd $(ARGS)

buildrun:
	g++ -o lcd LCD2.cpp Services/*.cpp -llgpio && sudo ./lcd $(ARGS)

test:
	 g++ -o Test/tests Test/tests.cpp -lcurl && ./Test/tests

