#include "scanner.h"    

// Construtor
Scanner::Scanner(string input, SymbolTable* table)
{
    pos = 0;
    line = 1;

    st = table;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile,line))
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

    // cout << this->input;
}

int
Scanner::getLine()
{
    return line;
}

// Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;
    string lexeme;
    
    // Trecho que reconhece e consome espaços vazios
    while(isspace(input[pos]))
        pos++;

    // Trecho que reconhece fim do arquivo
    if(input[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);

    }

    // Trecho que reconhece Números Inteiros Literais
    else if(isdigit(input[pos]))
    {
        lexeme.push_back(input[pos]);
        while(isdigit(input[pos]))
        {
            lexeme.push_back(input[pos]);
            pos++;
        }

        tok = new Token(INTEGER_LITERAL);
    }

    // Trecho que reconhece Operadores de Comparação/Relação
    // Menor e Menor ou Igual
    else if(input[pos] == '<')
    {
        pos++;
        if(input[pos] == '=')
            tok = new Token(RELOP, LE);
        else
            tok = new Token(RELOP, LT);
    }

    // Maior e Maior ou igual
    else if(input[pos] == '>')
    {
        pos++;
        if(input[pos] == '=')
            tok = new Token(RELOP, GE);
        else
            tok = new Token(RELOP, GT);
    }

    // Trecho que recohence Operadores Aritiméticos
    // Operador de soma
    else if(input[pos] == '+')
    {
        pos++;
        tok = new Token(OP, PLUS);
    }

    // Operador de subtração
    if(input[pos] == '-')
    {
        pos++;
        tok = new Token(OP, MINUS);
    }
    
    // Operador de multiplicação
    if(input[pos] == '*')
    {
        pos++;
        tok = new Token(OP, MULT);
    }

    // Operador de Divisão, Comentário de Linha e Comentário de Bloco
    else if(input[pos] == '/')
    {
        pos++;
        if(input[pos] == '/') {
            while(input[pos] != '\n') {
                pos++;
            }
            tok = nextToken();                                          // sistema de recursão
        } else if(input[pos] == '*') {
            while(input[pos] != '/' && input[pos-1] != '*') {
                pos++;
            }
            tok = nextToken();                                          // sistema de recursão
        } else
            tok = new Token(OP, DIV);
    }

    // Operador de Mod (Resto da Divisao)
    else if(input[pos] == '%')
    {
        pos++;
        tok = new Token(OP, MOD);
    }

    // Operador de Atribuição e Igualdade
    else if(input[pos] == '=')
    {
        pos++;
        if(input[pos] == '=')
            tok = new Token(RELOP, COMPARASION);
        else
            tok = new Token(OP, ATTRIBUTION);
    }

    // Operador de Diferença
    else if(input[pos] == '!')
    {
        pos++;
        if(input[pos] == '=')
            tok = new Token(RELOP, NOTEQUAL);
        else
            lexicalError("Found another character instead '=' after '!'");
    }

    // Trecho que reconhece Identificadores
    else if(isalpha(input[pos]) || input[pos] == '_')
    {
        lexeme.push_back(input[pos]);
        pos++;
        while (isalnum(input[pos]) || input[pos] == '_')
        {
            lexeme.push_back(input[pos]);
            pos++;
        }

        //Pesquisar na tabela de palavras reservadas
        //caso encontrem, retornem o token adequado,
        //caso contrário, é ID
        STEntry* obj = st->get(lexeme);
        if (!obj)
            tok = new Token(ID, lexeme);
        else 
            tok = new Token(obj->token->name);
    }
    
    // Trecho que reconhece Strings Literais
    else if(input[pos] == '"')
    {
        pos++;
        while(input[pos] != '"')
        {
            lexeme.push_back(input[pos]);
            pos++;
        }
        tok = new Token(STRING_LITERAL, lexeme);
    }

    // Trecho que reconhece Separadores
    // Parenteses
    else if(input[pos] == '(')
    {
        pos++;
        tok = new Token(SEP, LPARENTHESES);
    }

    else if(input[pos] == ')')
    {
        pos++;
        tok = new Token(SEP, RPARENTHESES);
    }

    // Colchetes (Square Brackets)
    else if(input[pos] == '[')
    {
        pos++;
        tok = new Token(SEP, LSQUAREBRACKETS);
    }

    else if(input[pos] == ']')
    {
        pos++;
        tok = new Token(SEP, RSQUAREBRACKETS);
    }

    // Chaves (Curly Brackets)
    else if(input[pos] == '{')
    {
        pos++;
        tok = new Token(SEP, LCURLYBRACKETS);
    }
 
    else if(input[pos] == '}')
    {
        pos++;
        tok = new Token(SEP, RCURLYBRACKETS);
    }

    // Ponto e Vírgula (Semicolom)
    else if(input[pos] == ';')
    {
        pos++;
        tok = new Token(SEP, SEMICOLON);
    }

    // Ponto final (Full Stop)
    else if(input[pos] == '.')
    {
        pos++;
        tok = new Token(SEP, FULLSTOP);
    }

    // Vírgula (Comma)
    else if(input[pos] == ',')
    {
        pos++;
        tok = new Token(SEP, COMMA);
    }

    return tok;
}

void 
Scanner::lexicalError(string msg)
{
    cout << "Line "<< line << ": " << msg << endl;
    exit(EXIT_FAILURE);
}
