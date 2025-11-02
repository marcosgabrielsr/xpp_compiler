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
    NEW,                                //5
    INT,                                //6 
    STRING,                             //7
    CONSTRUCTOR,                        //8
    PRINT,                              //9
    READ,                               //10
    RETURN,                             //11
    SUPER,                              //12
    IF,                                 //13
    ELSE,                               //14
    FOR,                                //15
    BREAK,                              //16
    OP,                                 //17
    LT,                                 //18
    LE,                                 //19
    GT,                                 //20
    GE,                                 //21
    PLUS,                               //22
    MINUS,                              //23
    MULT,                               //24
    DIV,                                //25
    MOD,                                //26
    RELOP,                              //27
    ATTRIBUTION,                        //28
    COMPARASION,                        //29
    NOTEQUAL,                           //30
    INTEGER_LITERAL,                    //31
    STRING_LITERAL,                     //32
    SEP,                                //33
    RPARENTHESES,                       //34
    LPARENTHESES,                       //35
    RSQUAREBRACKETS,                    //36
    LSQUAREBRACKETS,                    //37
    RCURLYBRACKETS,                     //38
    LCURLYBRACKETS,                     //39
    SEMICOLON,                          //40
    FULLSTOP,                           //41
    COMMA,                              //42
    END_OF_FILE                         //43
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

        static string get_token_name(int name)
        {
            string vect[] = {
                "UNDEF",          
                "ID",
                "CLASS",          
                "EXTENDS",        
                "PUBLIC",         
                "NEW",            
                "INT",            
                "STRING",         
                "CONSTRUCTOR",    
                "PRINT",          
                "READ",           
                "RETURN",         
                "SUPER",          
                "IF",             
                "ELSE",           
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
                "RELOP",          
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

            return vect[name];
        }

        static void printToken(Token* t)
        {
            cout << get_token_name(t->name);

            if(t->name == INTEGER_LITERAL || t->name == STRING_LITERAL || t->name == ID) {
                cout << "(" << t->lexeme << ")";
            } else {
                if(t->attribute != UNDEF) 
                {
                    cout << "(" << get_token_name(t->attribute) << ")";
                }
            }

            cout << '\n';
        }
};
