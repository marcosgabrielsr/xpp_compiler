#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Scanner* sScanner;
		Scanner* ssScanner;
		Token* lToken;
		Token* slToken;
		Token* sslToken;
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
		void _methodDeclList();
		void methodDecl();
		void methodBody();
		void paramListOpt();
		void paramList();
		void _paramList();
		void param();
		void statementsOpt();
		void statements();
		void _statements();
		void statement();
		void atribStat();
		void printStat();
		void readStat();
		void returnStat();
		void superStat();
		void ifStat();
		void forStat();
		void lValue();
		void expression();
		void allocExpression();
		void argListOpt();
		void atribStatOpt();
		void expressionOpt();
		void lValueComp();
		void numExpression();
		void term();
		void unaryExpression();
		void factor();
		void argList();
		void _argList();

	public:
		Parser(string);
		void run();
};