#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,
    ID,                                 //1
    CLASS,                              //2
    EXTENDS,                            //3
    PUBLIC,                             //4
    INT,                                //5 
    STRING,                             //6
    CONSTRUCTOR,                        
    OP,                                 //8
    LT,                                 //9
    LE,                                 //10
    GT,                                 //11
    GE,                                 //12
    PLUS,                               //13
    MINUS,                              //14
    MULT,                               //15
    DIV,                                //16
    MOD,                                //17
    ATTRIBUTION,                        //18
    COMPARASION,                        //19
    NOTEQUAL,                           //20
    INTEGER_LITERAL,                    //7
    STRING_LITERAL,                     //21
    SEP,                                //22
    RPARENTHESES,                       //23
    LPARENTHESES,                       //24
    RSQUAREBRACKETS,                    //25
    LSQUAREBRACKETS,                    //26
    RCURLYBRACKETS,                     //27
    LCURLYBRACKETS,                     //28
    SEMICOLON,                          //29
    FULLSTOP,                           //30
    COMMA,                              //31
    END_OF_FILE
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
};
