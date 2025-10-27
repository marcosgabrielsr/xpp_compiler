#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;
		SymbolTable* globalST;
    	SymbolTable* currentST;

		void advance();
		void match(int);
		void error(string);
		void initSimbolTable();

		void program();
		void classList();
		void classDecl();
		void classBody();
		void varDeclListOpt();
		void varDeclList();
		void varDecl();
		void _varDeclList();
		void varDeclOpt();
		void type();
		void constructDeclListOpt();
		void constructDeclList();
		void constructDecl();
		void _constructDeclList();
		void methodDeclListOpt();
		void methodDeclList();
		void methodBody();

	public:
		Parser(string);
		void run();
};