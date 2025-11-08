#include "symboltable.h"
#include <fstream>

class Scanner 
{
    private:
        string input_file;
        string input;//Armazena o texto de entrada
        int pos;//Posição atual
        int line;
        SymbolTable* st;
    
    public:
    //Construtor
        Scanner(string, SymbolTable*);

        int getLine();
    
        //Método que retorna o próximo token da entrada
        Token* nextToken();        
    
        //Método para manipular erros
        void lexicalError(string);

        //friend class Parser;
        int getPos();
        void setPos(int);
        int* lookNNext(int);
};
