#include "parser.h"

Parser::Parser(string input)
{
	currentST = globalST = new SymbolTable();
	initSimbolTable();

	scanner = new Scanner(input, globalST);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
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
	if(lToken->name == COMMA){
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
Parser::methodBody()
{

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
