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
	// Token::printToken(lToken);
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else {
		int f = (lToken->name == OP || lToken->name == SEP) ? lToken->attribute : lToken->name;
		string msgError = "  Token esperado: " + Token::getTokenName(t) + " - Token Encontrado: " + Token::getTokenName(f);
		error(msgError);
	}
}

void
Parser::match(int t, int idError)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else {
		// int f = (lToken->name == OP || lToken->name == SEP) ? lToken->attribute : lToken->name;
		string msgError = getMessageError(idError) /*+ "\n\t-> Token esperado: " + Token::get_token_name(t) + " - Token Encontrado: " + Token::get_token_name(f)*/;
		error(msgError);
	}
}

string
Parser::getMessageError(int idError)
{
	string msg;
	switch (idError)
	{
	case INITIAL_TOKEN_ERROR:
		return "Token inválido. Arquivos devem ser vazios ou conter pelo menos uma declaração de classe";
	
	case CLASS_DECLARATION_ID_NOT_FOUND:
		return "Erro de Declaração de Classe\n\t-> Identificado de classe não foi encontrado depois da palavra-chave 'class'";

	case CLASS_DECLARATION_ERROR_LCB_NOT_FOUND:
		return "Erro de Declaração de Classe\n\t-> '{' não foi encontrado depois da definição do nome da classe";
	
	case CLASS_DECLARATION_ERROR_RCB_NOT_FOUND:
		return "Erro de Declaração de Classe\n\t-> '}' não foi encontrado ao fim da declaração da classe";

	case CLASS_DECLARATION_EXTENDS_ERROR:
		return "Error de Herança";

	case VAR_DECLARATION_ERROR:
		return "Erro de Declaração de Variáveis";
	
	case SEMICOLON_NOT_FOUND_ERROR:
		return "Elemento ';' não encontrado";
	
	case CONSTRUCTOR_DECLARATION_ERROR:
		return "Erro na Declaração de Método Construtor";
	
	case METHOD_DECLARATION_ERROR:
		return "Erro na Declaração de Métodos";
	
	case METHOD_BODY_DECLARATION_ERROR_LCB_NOT_FOUND:
		return "Erro na Estrutura do corpo do Método\n\t-> '{' não foi econtrado após definição dos parâmetros do método";
	
	case METHOD_BODY_DECLARATION_ERROR_RCB_NOT_FOUND:
		return "Erro na Estrutura do corpo do Método\n\t-> '}' não foi econtrado ao fim da declaração do método";

	case PARAM_LIST_PARENTHESES_ERROR:
		return "Erro na Declaração do Corpo de Método\n\t-> Erro na estrutura da lista de Parametros";
	
	case PARAM_LIST_PARAMS_ERROR_UNDEFINED_ID:
		return "Erro na Declaração de Parâmetros\n\t-> Declaração indefinida de Tipo e ID apoś a ','";
	
	case STATEMENTS_UNDEF_TOKEN_ERROR:
		return "Erro na Definição de Estamentos";

	case ATRIBSTAT_ERROR_ATTRIBUTION_NOT_FOUND:
		return "Erro de Atribuição\n\t-> '=' não encontrado";
	
	case ATRIBSTAT_ERROR_INDEFINITE_ATTRIBUTION:
		return "Erro de Atribuição\n\t-> Nenhum valor está sendo atribuido corretamente";
	
	case EXPRESSIONOPT_ERROR_INVALID_TOKEN:
		return "Erro na Expressão\n\t-> Expressão indefinida ou má formulada";

	default:
		return "Erro econtrado, mas não informado";
	}
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
	else if(lToken->name != END_OF_FILE) {
		error(getMessageError(INITIAL_TOKEN_ERROR));
	}
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
	match(ID, CLASS_DECLARATION_ID_NOT_FOUND);

	if (lToken->name == EXTENDS)
	{
		advance();
		match(ID, CLASS_DECLARATION_EXTENDS_ERROR);
	}

	classBody();
}

void
Parser::classBody()
{
	match(LCURLYBRACKETS, CLASS_DECLARATION_ERROR_LCB_NOT_FOUND);
	varDeclListOpt();
	constructDeclListOpt();
	methodDeclListOpt();
	match(RCURLYBRACKETS, CLASS_DECLARATION_ERROR_RCB_NOT_FOUND);
}

void
Parser::varDeclListOpt()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		varDeclList();
	} else if(!(lToken->name == CONSTRUCTOR || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON || lToken->attribute == RCURLYBRACKETS)) {
		error(getMessageError(VAR_DECLARATION_ERROR) + "(Token inválido)");
	}
}

void
Parser::varDeclList() {
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		varDecl();
		_varDeclList();
	}
	else if(!(lToken->name == CONSTRUCTOR || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON))
	{
		// int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		error(getMessageError(VAR_DECLARATION_ERROR) + "(Token inválido)");
	}
}

void
Parser::_varDeclList() {
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		varDecl();
		_varDeclList();
	}
}

void
Parser::varDecl()
{
	int* nextTokens = scanner->lookNNext(4);

	if(nextTokens[0] == LSQUAREBRACKETS && nextTokens[3] == LPARENTHESES)
	{
		methodDeclListOpt();
	}
	else if(nextTokens[0] == ID && nextTokens[1] == LPARENTHESES)
	{
		methodDeclListOpt();
	}
	else
	{	
		if(nextTokens[0] == ATTRIBUTION || nextTokens[0] == FULLSTOP || (nextTokens[0] == LSQUAREBRACKETS && (nextTokens[1] == PLUS || nextTokens[1] == MINUS)))
		{
			atribStat();
			match(SEMICOLON);
		}
		else
		{
			if((lToken->name == INT || lToken->name == STRING || lToken->name == ID) && !Token::isRelop(nextTokens[0]) && !Token::isOp(nextTokens[0]))
			{
				// cout << "Estou aqui (varDecl)\n";
				type();
				if(lToken->attribute == LSQUAREBRACKETS)
				{
					advance();
					match(RSQUAREBRACKETS);
				}
				match(ID, VAR_DECLARATION_ERROR);
				varDeclOpt();
				match(SEMICOLON);
			}
			else
				error(getMessageError(ATRIBSTAT_ERROR_ATTRIBUTION_NOT_FOUND));
		}
	}

	delete nextTokens;
}

void
Parser::varDeclOpt()
{	
	if(lToken->attribute == COMMA)
	{
		advance();
		match(ID, VAR_DECLARATION_ERROR);
		varDeclOpt();
	}
	else if(!(lToken->attribute == SEMICOLON))
	{
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		error(getMessageError(SEMICOLON_NOT_FOUND_ERROR) + " antes de '" + Token::getElementByToken(lTokenCode) + "'");
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
	else if(!(lToken->name == INT || lToken->name == STRING || lToken->name == ID || lToken->attribute == RCURLYBRACKETS)) {
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		if(lTokenCode == END_OF_FILE)
			error(getMessageError(CLASS_DECLARATION_ERROR_RCB_NOT_FOUND));
		else
			error(getMessageError(METHOD_DECLARATION_ERROR) + ": Token " + Token::getTokenName(lTokenCode) + " inválido");
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
	else if(!(lToken->name == INT || lToken->name == STRING || lToken->name == ID || lToken->attribute == RCURLYBRACKETS)) {
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		if(lTokenCode == END_OF_FILE)
			error(getMessageError(CLASS_DECLARATION_ERROR_RCB_NOT_FOUND));
		else
			error(getMessageError(METHOD_DECLARATION_ERROR) + ": Token " + Token::getTokenName(lTokenCode) + " inválido");
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
	else if(!(lToken->attribute == RCURLYBRACKETS))
	{
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		if(lTokenCode == END_OF_FILE)
			error(getMessageError(CLASS_DECLARATION_ERROR_RCB_NOT_FOUND));
		else
			error(getMessageError(METHOD_DECLARATION_ERROR) + ": Token " + Token::getTokenName(lTokenCode) + " inválido");
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
	else if(!(lToken->attribute == RCURLYBRACKETS))
	{
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		if(lTokenCode == END_OF_FILE)
			error(getMessageError(CLASS_DECLARATION_ERROR_RCB_NOT_FOUND));
		else
			error(getMessageError(METHOD_DECLARATION_ERROR) + ": Token " + Token::getTokenName(lTokenCode) + " inválido");
	}
}

void
Parser::methodDecl()
{
	type();
	if(lToken->attribute == LSQUAREBRACKETS)
	{
		advance();
		match(RSQUAREBRACKETS, METHOD_DECLARATION_ERROR);
	}
	match(ID, METHOD_DECLARATION_ERROR);
	methodBody();
}

void
Parser::methodBody()
{
	if(lToken->attribute == LPARENTHESES)
	{
		advance();
		paramListOpt();
		match(RPARENTHESES, PARAM_LIST_PARENTHESES_ERROR);
		match(LCURLYBRACKETS, METHOD_BODY_DECLARATION_ERROR_LCB_NOT_FOUND);
		statementsOpt();
		match(RCURLYBRACKETS, METHOD_BODY_DECLARATION_ERROR_RCB_NOT_FOUND);
	}
	else
	{
		error(getMessageError(PARAM_LIST_PARENTHESES_ERROR) + ": '(' não encontrado");
	}
}

void
Parser::paramListOpt()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID)
	{
		paramList();
	}
	else if(!(lToken->attribute == RPARENTHESES))
	{
		error(getMessageError(PARAM_LIST_PARENTHESES_ERROR)+ ": ')' não encontrado");
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
	else if(!(lToken->attribute == RPARENTHESES))
	{
		error(getMessageError(PARAM_LIST_PARENTHESES_ERROR)+ ": ')' não encontrado");
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
	match(ID, PARAM_LIST_PARAMS_ERROR_UNDEFINED_ID);
}

void
Parser::statementsOpt()
{	
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON)
	{
		statements();
	}
	else if(!(lToken->attribute == RCURLYBRACKETS))
	{
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		error(getMessageError(STATEMENTS_UNDEF_TOKEN_ERROR) + "\n\t-> O Token '" + Token::getElementByToken(lTokenCode) + "' não corresponde à uma definição de estamentos");
	}
}

void
Parser::statements()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON)
	{
		statement();
		_statements();
	}
}

void
Parser::_statements()
{
	if(lToken->name == INT || lToken->name == STRING || lToken->name == ID || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON)
	{
		statement();
		_statements();
	}
	else if(!(lToken->attribute == RCURLYBRACKETS))
	{
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		error(getMessageError(STATEMENTS_UNDEF_TOKEN_ERROR) + "\n\t-> O Token '" + Token::getElementByToken(lTokenCode) + "' não corresponde à uma definição de estamentos");
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
		int* nextTokens = scanner->lookNNext(2);
		if(nextTokens[0] == ID)
		{
			varDeclList();
		}
		else if(nextTokens[0] == LSQUAREBRACKETS && nextTokens[1] == RSQUAREBRACKETS)
		{
			varDeclList();
		}
		else
		{
			atribStat();
			match(SEMICOLON, SEMICOLON_NOT_FOUND_ERROR);
		}

	}
	else if(lToken->name == PRINT)
	{
		printStat();
		match(SEMICOLON, SEMICOLON_NOT_FOUND_ERROR);
	}
	else if(lToken->name == READ)
	{
		readStat();
		match(SEMICOLON, SEMICOLON_NOT_FOUND_ERROR);
	}
	else if(lToken->name == RETURN)
	{
		returnStat();
		match(SEMICOLON, SEMICOLON_NOT_FOUND_ERROR);
	}
	else if(lToken->name == SUPER)
	{
		superStat();
		match(SEMICOLON, SEMICOLON_NOT_FOUND_ERROR);
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
		match(SEMICOLON, SEMICOLON_NOT_FOUND_ERROR);
	}
	else if(lToken->attribute == SEMICOLON)
	{
		match(SEMICOLON, SEMICOLON_NOT_FOUND_ERROR);
	}
}

void
Parser::atribStat()
{
	if(lToken->name == ID)
	{
		lValue();
		match(ATTRIBUTION, ATRIBSTAT_ERROR_ATTRIBUTION_NOT_FOUND);
		
		if(lToken->attribute == PLUS || lToken->attribute == MINUS)
		{
			expression();
		}
		else if(lToken->attribute == SEMICOLON)
		{
			error(getMessageError(ATRIBSTAT_ERROR_INDEFINITE_ATTRIBUTION));
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
	else if(!(lToken->attribute == SEMICOLON || lToken->attribute == RPARENTHESES))
	{
		error(getMessageError(ATRIBSTAT_ERROR_INDEFINITE_ATTRIBUTION));
	}
}

void
Parser::expressionOpt()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		expression();
	}
	else if(!(lToken->attribute == SEMICOLON))
	{
		// int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		error(getMessageError(EXPRESSIONOPT_ERROR_INVALID_TOKEN));
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
	if(lToken->attribute == FULLSTOP)
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
	}
	else if(lToken->attribute == LSQUAREBRACKETS)
	{
		advance();
		expression();
		match(RSQUAREBRACKETS);
		lValueComp();
	}
	else if(!(lToken->name == OP || lToken->name == RELOP || lToken->attribute == SEMICOLON || lToken->attribute == RPARENTHESES || lToken->attribute == RSQUAREBRACKETS || lToken->attribute == COMMA))
	{
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		error("Token bad informed on lValueComp (" + Token::getTokenName(lTokenCode) + ")");
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
		error("Invalid token on Expressions.\n");
	}
}

void
Parser::argListOpt()
{
	if(lToken->attribute == PLUS || lToken->attribute == MINUS)
	{
		argList();
	}
	else if(!(lToken->attribute == RPARENTHESES))
	{
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		error("Token bad informed on argListOpt (" + Token::getTokenName(lTokenCode) + ")");
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
	else if(!(lToken->attribute == RPARENTHESES))
	{
		int lTokenCode = (lToken->attribute == UNDEF) ? lToken->name : lToken->attribute;
		error("Token bad informed on _argList (" + Token::getTokenName(lTokenCode) + ")");
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
	t = new Token(NEW, "new");
	globalST->add(new STEntry(t, true));
	t = new Token(INT, "int");
	globalST->add(new STEntry(t, true));
	t = new Token(STRING, "string");
	globalST->add(new STEntry(t, true));
	t = new Token(CONSTRUCTOR, "constructor");
	globalST->add(new STEntry(t, true));
	t = new Token(PRINT, "print");
	globalST->add(new STEntry(t, true));
	t = new Token(READ, "read");
	globalST->add(new STEntry(t, true));
	t = new Token(RETURN, "return");
	globalST->add(new STEntry(t, true));
	t = new Token(SUPER, "super");
	globalST->add(new STEntry(t, true));
	t = new Token(IF, "if");
	globalST->add(new STEntry(t, true));
	t = new Token(ELSE, "else");
	globalST->add(new STEntry(t, true));
	t = new Token(FOR, "for");
	globalST->add(new STEntry(t, true));
	t = new Token(BREAK, "break");
	globalST->add(new STEntry(t, true));
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;
	exit(EXIT_FAILURE);
}
