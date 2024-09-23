################################################################
#	Project:	IMAP client with TLS support
#	File: 		Makefile
#	Author: 	Adam Ližičiar xlizic00@stud.fit.vutbr.cz
################################################################

COMPILER = g++
COMPILER_FLAGS = -std=c++20 -Wall -Wextra -Werror
PROGRAM_NAME = imapcl

.PHONY: make run test clean pack

make: src/main.cpp
	$(COMPILER) $(COMPILER_FLAGS) src/main.cpp -o $(PROGRAM_NAME)

run: make
	./$(PROGRAM_NAME)

clean:
	rm -f test/runTests
	rm -f *.exe *.out *.core *.tar
	rm -f $(PROGRAM_NAME)

pack:
	tar -cvf xlizic00.tar .