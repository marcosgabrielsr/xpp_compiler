# **xpp_compiler**
### **Trabalho da disciplina de Compiladores**

#### **Membros do Grupo**:
- Marcos Gabriel da Silva Rocha
---
#### **Compilação**:
Este trabalho foi feito e testado utilizando uma máquina rodando archlinux e usando o sistema Makefile para compilação e testes.

Para compilar execute o seguinte comando no terminal:
```bash
make
```

Para remover os arquivos .o utilize o seguinte comando:
```bash
make clear
```
---
#### **Execução**
Para executar o compilador execute o seguinte comando:
```bash
./xpp_compiler teste1.xpp
```
---
#### **Observações**
- As mensagens de erro buscam ser claras tentando indicar o erro de forma simples e clara;
- As transições da gramática foram feitas após definição dos conjuntos firsts e follow tentando respeitar todas as definições apresentadas na segunda etapa do traablo;
- Vários testes foram realizados, visando corrigir possíveis quebras e erros de código e para o melhoramento das mensagens de erro;
