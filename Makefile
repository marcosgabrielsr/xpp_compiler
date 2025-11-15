# Diretórios
DIR_BUILD =
DIR_EXAMPLES = examples

# Files
MAIN = principal.cpp
TOKEN = token.h
SCANNER = scanner.cpp
SCANNER_H = scanner.h
PARSER = parser.cpp
PARSER_H = parser.h
STENTRY = stentry.cpp
STENTRY_H = stentry.h
SYMBOLTABLE = symboltable.cpp
SYMBOLTABLE_H = symboltable.h
EXECUTABLE = xpp_compiler

# Examples
EXAMPLE1 = $(DIR_EXAMPLES)/example1.xpp
EXAMPLE2 = $(DIR_EXAMPLES)/example2.xpp
EXAMPLE3 = $(DIR_EXAMPLES)/example3.xpp
EXAMPLE4 = $(DIR_EXAMPLES)/example4.xpp
EXAMPLE5 = $(DIR_EXAMPLES)/example5.xpp
EXAMPLE6 = $(DIR_EXAMPLES)/example6.xpp

# Main
all: $(EXECUTABLE)

$(EXECUTABLE): scanner.o parser.o stentry.o symboltable.o
	g++ scanner.o parser.o stentry.o symboltable.o $(MAIN) -o $(EXECUTABLE) -Wall

parser.o: $(PARSER) $(PARSER_H)
	g++ -c $(PARSER) -o $@ -Wall

scanner.o: $(SCANNER) $(SCANNER_H)
	g++ -c $(SCANNER) -o $@ -Wall

stentry.o: $(STENTRY) $(STENTRY_H)
	g++ -c $(STENTRY) -o $@ -Wall

symboltable.o: $(SYMBOLTABLE) $(SYMBOLTABLE_H)
	g++ -c $(SYMBOLTABLE) -o $@ -Wall

run:
	./$(EXECUTABLE)

clear:
	rm -f *.o

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

test6:
	./$(EXECUTABLE) $(EXAMPLE6)

testall:
	./$(EXECUTABLE) $(EXAMPLE1)
	./$(EXECUTABLE) $(EXAMPLE2)
	./$(EXECUTABLE) $(EXAMPLE3)
	./$(EXECUTABLE) $(EXAMPLE4)
	./$(EXECUTABLE) $(EXAMPLE5)
	./$(EXECUTABLE) $(EXAMPLE6)
