# Diretories
DIR_SRC = src
DIR_BUILD = build
DIR_EXAMPLES = examples

# Files
MAIN = $(DIR_SRC)/principal.cpp
TOKEN = $(DIR_SRC)/token.h
SCANNER = $(DIR_SRC)/scanner.cpp
SCANNER_H = $(DIR_SRC)/scanner.h
PARSER = $(DIR_SRC)/parser.cpp
PARSER_H = $(DIR_SRC)/parser.h
STENTRY = $(DIR_SRC)/stentry.cpp
STENTRY_H = $(DIR_SRC)/stentry.h
SYMBOLTABLE = $(DIR_SRC)/symboltable.cpp
SYMBOLTABLE_H = $(DIR_SRC)/symboltable.h
EXECUTABLE = $(DIR_BUILD)/xpp_compiler

# Examples
EXAMPLE1 = $(DIR_EXAMPLES)/example1.txt
EXAMPLE2 = $(DIR_EXAMPLES)/example2.txt
EXAMPLE3 = $(DIR_EXAMPLES)/example3.txt
EXAMPLE4 = $(DIR_EXAMPLES)/example4.txt
EXAMPLE5 = $(DIR_EXAMPLES)/example5.txt

# Main
all: $(EXECUTABLE)

$(EXECUTABLE): $(DIR_BUILD)/scanner.o $(DIR_BUILD)/parser.o $(DIR_BUILD)/stentry.o $(DIR_BUILD)/symboltable.o
	g++ $(DIR_BUILD)/scanner.o $(DIR_BUILD)/parser.o $(DIR_BUILD)/stentry.o $(DIR_BUILD)/symboltable.o $(MAIN) -o $(EXECUTABLE) -Wall

$(DIR_BUILD)/parser.o: $(PARSER_H)
	g++ -c $(PARSER) -o $@ -Wall

$(DIR_BUILD)/scanner.o: $(SCANNER_H)
	g++ -c $(SCANNER) -o $@ -Wall

$(DIR_BUILD)/stentry.o: $(STENTRY_H)
	g++ -c $(STENTRY) -o $@ -Wall

$(DIR_BUILD)/symboltable.o: $(SYMBOLTABLE_H)
	g++ -c $(SYMBOLTABLE) -o $@ -Wall

run:
	./$(EXECUTABLE)

clear:
	rm $(DIR_BUILD)/*.o

test1:
	./$(EXECUTABLE) $(EXAMPLE1)

test2:
	./$(EXECUTABLE) $(EXAMPLE2)

test3:
	./$(EXECUTABLE) $(EXAMPLE3)

test4:
	./$(EXECUTABLE) $(EXAMPLE4)

test5:
	./$(EXECUTABLE) $(EXAMPLE5)