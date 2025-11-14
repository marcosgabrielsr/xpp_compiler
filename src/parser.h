#include "scanner.h"

enum TypeErrors {
	INITIAL_TOKEN_ERROR,
	CLASS_DECLARATION_ID_NOT_FOUND,
	CLASS_DECLARATION_ERROR_LCB_NOT_FOUND,
	CLASS_DECLARATION_ERROR_RCB_NOT_FOUND,
	CLASS_DECLARATION_EXTENDS_ERROR,
	VAR_DECLARATION_ERROR,
	SEMICOLON_NOT_FOUND_ERROR,
	CONSTRUCTOR_DECLARATION_ERROR,
	METHOD_DECLARATION_ERROR,
	METHOD_BODY_DECLARATION_ERROR_LCB_NOT_FOUND,
	METHOD_BODY_DECLARATION_ERROR_RCB_NOT_FOUND,
	PARAM_LIST_PARENTHESES_ERROR,
	PARAM_LIST_PARAMS_ERROR_UNDEFINED_ID,
	STATEMENTS_UNDEF_TOKEN_ERROR,
	ATRIBSTAT_ERROR_ATTRIBUTION_NOT_FOUND,
	ATRIBSTAT_ERROR_INDEFINITE_ATTRIBUTION,
	EXPRESSIONOPT_ERROR_INVALID_TOKEN,
	UNDEF_ERROR
};

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;
		SymbolTable* globalST;
    	SymbolTable* currentST;

		void advance();
		void match(int);
		void match(int,int);
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
		string getMessageError(int);
		void run();
};