################################################################
#	Project:	IMAP client with TLS support
#	File: 		Makefile
#	Author: 	Adam Ližičiar xlizic00@stud.fit.vutbr.cz
################################################################

COMPILER = g++
COMPILER_FLAGS = -std=c++20 -Wall -Wextra -Werror
PROGRAM_NAME = imapcl
DOC=documentation
OBJ_DIR = obj
DOC_DIR = doc

.PHONY: make run doc valgrind clean pack

make: src/main.cpp
	$(COMPILER) $(COMPILER_FLAGS) src/main.cpp -o $(PROGRAM_NAME)

run: make
	./$(PROGRAM_NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

doc: $(OBJ_DIR) $(DOC_DIR)/$(DOC).tex
	cd $(DOC_DIR) && pdflatex $(DOC).tex
	cd $(DOC_DIR) && pdflatex $(DOC).tex
	cd $(DOC_DIR) && pdflatex $(DOC).tex
	cd ../
	if [ -e $(DOC_DIR)/$(DOC).aux ]; then mv $(DOC_DIR)/$(DOC).aux $(OBJ_DIR)/$(DOC).aux; fi
	if [ -e $(DOC_DIR)/$(DOC).dvi ]; then mv $(DOC_DIR)/$(DOC).dvi $(OBJ_DIR)/$(DOC).dvi; fi
	if [ -e $(DOC_DIR)/$(DOC).xdv ]; then mv $(DOC_DIR)/$(DOC).xdv $(OBJ_DIR)/$(DOC).xdv; fi
	if [ -e $(DOC_DIR)/$(DOC).log ]; then mv $(DOC_DIR)/$(DOC).log $(OBJ_DIR)/$(DOC).log; fi
	if [ -e $(DOC_DIR)/$(DOC).ps ]; then mv $(DOC_DIR)/$(DOC).ps $(OBJ_DIR)/$(DOC).ps; fi
	if [ -e $(DOC_DIR)/$(DOC).synctex.gz ]; then mv $(DOC_DIR)/$(DOC).synctex.gz $(OBJ_DIR)/$(DOC).synctex.gz; fi
	if [ -e $(DOC_DIR)/$(DOC).fls ]; then mv $(DOC_DIR)/$(DOC).fls $(OBJ_DIR)/$(DOC).fls; fi
	if [ -e $(DOC_DIR)/$(DOC).fdb_latexmk ]; then mv $(DOC_DIR)/$(DOC).fdb_latexmk $(OBJ_DIR)/$(DOC).fdb_latexmk; fi
	if [ -e $(DOC_DIR)/$(DOC).bbl ]; then mv $(DOC_DIR)/$(DOC).bbl $(OBJ_DIR)/$(DOC).bbl; fi
	if [ -e $(DOC_DIR)/$(DOC).blg ]; then mv $(DOC_DIR)/$(DOC).blg $(OBJ_DIR)/$(DOC).blg; fi
	if [ -e $(DOC_DIR)/$(DOC).out ]; then mv $(DOC_DIR)/$(DOC).out $(OBJ_DIR)/$(DOC).out; fi
	if [ -e $(DOC_DIR)/$(DOC).toc ]; then mv $(DOC_DIR)/$(DOC).toc $(OBJ_DIR)/$(DOC).toc; fi
	if [ -e $(DOC_DIR)/$(DOC).pdf.filepart ]; then mv $(DOC_DIR)/$(DOC).pdf.filepart $(OBJ_DIR)/$(DOC).pdf.filepart; fi
	if [ -e $(DOC_DIR)/$(DOC).pdf ]; then mv $(DOC_DIR)/$(DOC).pdf $(DOC).pdf; fi

valgrind:
	valgrind --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        --log-file=log/valgrind-log-$(shell date +%Y%m%d-%H%M%S).txt \
        ./$(PROGRAM_NAME) 

clean:
	rm -f tests/run
	rm -f *.exe *.out *.core *.tar
	rm -f $(PROGRAM_NAME)

pack:
	tar -cvf xlizic00.tar .