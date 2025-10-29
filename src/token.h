#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,                              //0
    ID,                                 //1
    CLASS,                              //2
    EXTENDS,                            //3
    PUBLIC,                             //4
    INT,                                //5 
    STRING,                             //6
    CONSTRUCTOR,                        //7
    PRINT,                              //8
    READ,                               //9
    RETURN,                             //10
    SUPER,                              //11
    IF,                                 //12
    FOR,                                //13
    BREAK,                              //14
    OP,                                 //15
    LT,                                 //16
    LE,                                 //17
    GT,                                 //18
    GE,                                 //19
    PLUS,                               //20
    MINUS,                              //21
    MULT,                               //22
    DIV,                                //23
    MOD,                                //24
    ATTRIBUTION,                        //25
    COMPARASION,                        //26
    NOTEQUAL,                           //27
    INTEGER_LITERAL,                    //28
    STRING_LITERAL,                     //29
    SEP,                                //30
    RPARENTHESES,                       //31
    LPARENTHESES,                       //32
    RSQUAREBRACKETS,                    //33
    LSQUAREBRACKETS,                    //34
    RCURLYBRACKETS,                     //35
    LCURLYBRACKETS,                     //36
    SEMICOLON,                          //37
    FULLSTOP,                           //38
    COMMA,                              //39
    END_OF_FILE                         //40
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, string l)
        {
            this->name = name;
            attribute = UNDEF;
            lexeme = l;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }

        static void printToken(Token* t) {
            string vect[] = {
                "UNDEF",
                "ID",
                "CLASS",
                "EXTENDS",
                "PUBLIC",
                "INT",            
                "STRING",
                "CONSTRUCTOR",
                "PRINT",
                "READ",
                "RETURN",
                "SUPER",
                "IF",
                "FOR",
                "BREAK",
                "OP",
                "LT",
                "LE",
                "GT",
                "GE",             
                "PLUS",
                "MINUS",
                "MULT",
                "DIV",
                "MOD",
                "ATTRIBUTION",
                "COMPARASION",
                "NOTEQUAL",
                "INTEGER_LITERAL",
                "STRING_LITERAL", 
                "SEP",            
                "RPARENTHESES",   
                "LPARENTHESES",   
                "RSQUAREBRACKETS",
                "LSQUAREBRACKETS",
                "RCURLYBRACKETS", 
                "LCURLYBRACKETS", 
                "SEMICOLON",      
                "FULLSTOP",       
                "COMMA",          
                "END_OF_FILE"
            };
            cout << vect[t->name];

            if(t->name == INTEGER_LITERAL) {
                cout << "(" << t->lexeme << ")";
            } else {
                cout << "(" << vect[t->attribute] << ")";
            }

            cout << '\n';
        }
};
