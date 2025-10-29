#include "parser.h"

Parser::Parser(string input)
{
	currentST = globalST = new SymbolTable();
	initSimbolTable();

	scanner = new Scanner(input, globalST);
	sScanner = new Scanner(input, globalST);
	ssScanner = new Scanner(input, globalST);

	// Starts shift scanner
	sScanner->nextToken();

	// Starts shift shift scanner
	ssScanner->nextToken();
	ssScanner->nextToken();
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
	slToken = sScanner->nextToken();
	sslToken = ssScanner->nextToken();
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

void
Parser::run()
{
	advance();	

	program();
	//TESTE DA TABELA DE SÍMBOLOS
	/*
    currentST = new SymbolTable(currentST);
	currentST = new SymbolTable(currentST);
    if (currentST->add(new STEntry(new Token(ID), "bianca")))
		cout << "Adição de bianca deu certo" << endl;
	else
		cout << "Adição de bianca não deu certo" << endl;

	STEntry* obj = currentST->get("bianca");

	if (obj)
		cout << "Encontrei o símbolo " << obj->lexeme << endl;
	else
		cout << "Não encontrei o símbolo buscado" << endl;

	//Fim do escopo
	currentST = currentST->getParent();

	obj = currentST->get("bianca");

	if (obj)
		cout << "Encontrei o símbolo " << obj->lexeme << endl;
	else
		cout << "Não encontrei o símbolo buscado" << endl;*/

	/////////////////////////////

	cout << "Compilação encerrada com sucesso!\n";
}

void
Parser::program()
{
	if (lToken->name == CLASS)
		classList();
}

void
Parser::classList()
{
	do
	{
		classDecl();
	}
	while(lToken->name == CLASS);
}

void
Parser::classDecl()
{
	match(CLASS);
	match(ID);

	if (lToken->name == EXTENDS)
	{
		advance();
		match(ID);
	}

	classBody();
}

void
Parser::classBody()
{
	match(LCURLYBRACKETS);
	varDeclListOpt();
	constructDeclListOpt();
	methodDeclListOpt();
	match(RCURLYBRACKETS);
}

void
Parser::varDeclListOpt()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		varDeclList();
	}
}

void
Parser::varDeclList() {
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		varDecl();
		_varDeclList();
	}
}

void
Parser::_varDeclList() {
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		varDeclList();
		_varDeclList();
	}
}

void
Parser::varDecl()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		type();
		if(lToken->attribute == LSQUAREBRACKETS)
		{
			advance();
			match(RSQUAREBRACKETS);
		}
		match(ID);
		varDeclOpt();
	}
}

void
Parser::varDeclOpt()
{
	if(lToken->attribute == COMMA){
		advance();
		match(ID);
		varDeclOpt();
	}
}

void
Parser::type()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		advance();
	}
}

void
Parser::constructDeclListOpt()
{
	if(lToken->name == CONSTRUCTOR)
	{
		constructDeclList();
	}
}

void
Parser::constructDeclList()
{
	if(lToken->name == CONSTRUCTOR)
	{
		constructDecl();
		_constructDeclList();
	}
}

void
Parser::_constructDeclList()
{
	if(lToken-> name == CONSTRUCTOR)
	{
		constructDecl();
		_constructDeclList();
	}
}

void
Parser::constructDecl()
{
	match(CONSTRUCTOR);
	methodBody();
}

void
Parser::methodDeclListOpt()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		methodDeclList();
	}
}

void
Parser::methodDeclList()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		methodDecl();
		_methodDeclList();
	}
}

void
Parser::_methodDeclList()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		methodDecl();
		_methodDeclList();
	}
}

void
Parser::methodDecl()
{
	type();
	if(lToken->attribute == LSQUAREBRACKETS)
	{
		advance();
		match(RSQUAREBRACKETS);
	}
	match(ID);
	methodBody();
}

void
Parser::methodBody()
{
	if(lToken->attribute == LPARENTHESES)
	{
		advance();
		paramListOpt();
		match(RPARENTHESES);
		match(LCURLYBRACKETS);
		statementsOpt();
		match(RCURLYBRACKETS);
	}
	else
	{
		error("Method Body bad informed, '(' not found.\n");
	}
}

void
Parser::paramListOpt()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		paramList();
	}
}

void
Parser::paramList()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		param();
		_paramList();
	}
}

void
Parser::_paramList()
{
	if(lToken->attribute == COMMA)
	{
		advance();
		param();
		_paramList();
	}
}

void
Parser::param()
{
	type();
	if(lToken->attribute == LSQUAREBRACKETS)
	{
		advance();
		match(RSQUAREBRACKETS);
	}
	match(ID);
}

void
Parser::statementsOpt()
{	
	//int, string, ID, print, read, return, super, if, for, break, ;
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON)
	{
		statements();
	}
}

void
Parser::statements()
{
	//int, string, ID, print, read, return, super, if, for, break, ;
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON)
	{
		statement();
		_statements();
	}
}

void
Parser::_statements()
{
	//int, string, ID, print, read, return, super, if, for, break, ;
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON)
	{
		statement();
		_statements();
	}
}

void
Parser::statement()
{
	if(lToken->name == INT || lToken->name == STRING)
	{
		varDeclList();
	}
	else if(lToken->name == ID)
	{
		if(slToken->name == ID)
		{
			varDeclList();
		}
		else if(slToken->attribute == LSQUAREBRACKETS && sslToken->attribute == RSQUAREBRACKETS)
		{
			varDeclList();
		}
		else
		{
			atribStat();
		}

	}
	else if(lToken->name == PRINT)
	{
		printStat();
		match(SEMICOLON);
	}
	else if(lToken->name == READ)
	{
		readStat();
		match(SEMICOLON);
	}
	else if(lToken->name == RETURN)
	{
		returnStat();
		match(SEMICOLON);
	}
	else if(lToken->name == SUPER)
	{
		superStat();
		match(SEMICOLON);
	}
	else if(lToken->name == IF)
	{
		ifStat();
	}
	else if(lToken->name == FOR)
	{
		forStat();
	}
	else if(lToken->name == BREAK)
	{
		match(BREAK);
		match(SEMICOLON);
	}
	else if(lToken->attribute == SEMICOLON)
	{
		match(SEMICOLON);
	}
}

void
Parser::atribStat()
{
	if(lToken->name == ID)
	{
		lValue();
		match(ATTRIBUTION);
		
		if(lToken->attribute == PLUS || lToken->attribute == MINUS)
		{
			expression();
		}
		else
		{
			allocExpression();
		}
	}
}

void
Parser::printStat()
{
	match(PRINT);
	expression();
}

void
Parser::readStat()
{
	match(READ);
	lValue();
}

void
Parser::returnStat()
{
	match(RETURN);
	expression();
}

void
Parser::superStat()
{
	match(SUPER);
	match(LPARENTHESES);
	argListOpt();
	match(RPARENTHESES);
}

void
Parser::ifStat()
{
	match(IF);
	match(LPARENTHESES);
	expression();
	match(RPARENTHESES);
	match(LCURLYBRACKETS);
	statements();
	match(RCURLYBRACKETS);

	if(lToken->name == ELSE)
	{
		advance();
		match(LCURLYBRACKETS);
		statements();
		match(RCURLYBRACKETS);
	}
}

void
Parser::forStat()
{
	match(FOR);
	match(LPARENTHESES);
	atribStatOpt();
	match(SEMICOLON);
	expressionOpt();
	match(SEMICOLON);
	atribStatOpt();
	match(RPARENTHESES);
	match(LCURLYBRACKETS);
	statements();
	match(RCURLYBRACKETS);
}

void
Parser::atribStatOpt()
{
	if(lToken->name == ID)
	{
		atribStat();
	}
}

void
Parser::expressionOpt()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		expression();
	}
}

void
Parser::lValue()
{
	match(ID);
	lValueComp();
}

void
Parser::lValueComp()
{
	if(lToken->name == FULLSTOP)
	{
		advance();
		match(ID);
		if(lToken->attribute == LSQUAREBRACKETS)
		{
			advance();
			expression();
			match(RSQUAREBRACKETS);
		}
		else if(lToken->attribute == LPARENTHESES)
		{
			advance();
			argListOpt();
			match(RPARENTHESES);
		}

		lValueComp();
	} else if(lToken->attribute == LSQUAREBRACKETS)
	{
		advance();
		expression();
		match(RSQUAREBRACKETS);
		lValueComp();
	}
}

void
Parser::expression()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		numExpression();
		if(lToken->name == RELOP)
		{
			advance();
			numExpression();
		}
	}
}

void
Parser::allocExpression()
{
	if(lToken->name == NEW)
	{
		advance();
		match(ID);
		match(LPARENTHESES);
		argListOpt();
		match(RPARENTHESES);
	}
	else if(lToken->name == STRING || lToken->name == INT || lToken->name == ID)
	{
		type();
		match(LSQUAREBRACKETS);
		expression();
		match(RSQUAREBRACKETS);
	}
}

void
Parser::numExpression()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		term();
		if(lToken->attribute == PLUS || lToken->attribute == MINUS)
		{
			advance();
			term();
		}
	}
}

void
Parser::term()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		unaryExpression();
		if(lToken->attribute == MULT || lToken->attribute == DIV || lToken->attribute == MOD)
		{
			advance();
			unaryExpression();
		}
	}
}

void
Parser::unaryExpression()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		advance();
		factor();
	}
}

void
Parser::factor()
{
	if(lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL)
	{
		advance();
	}
	else if(lToken->name == ID)
	{
		advance();
		lValue();
	}
	else if(lToken->attribute == LPARENTHESES)
	{	
		advance();
		expression();
		match(RPARENTHESES);
	}
	else
	{
		error("Invalid token on expressions");
	}
}

void
Parser::argListOpt()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		argList();
	}
}

void
Parser::argList()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		expression();
		_argList();
	}
}

void
Parser::_argList()
{
	if(lToken->attribute == COMMA)
	{
		advance();
		expression();
		_argList();
	}
}

void
Parser::initSimbolTable()
{
	Token* t;
        
	t = new Token(CLASS, "class");
	globalST->add(new STEntry(t, true));
	t = new Token(EXTENDS, "extends");
    globalST->add(new STEntry(t, true));
    t = new Token(PUBLIC, "public");
    globalST->add(new STEntry(t, true));
	//CONTINUAR...
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
