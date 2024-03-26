%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "symbol_table.h"
  extern int line_number;
  FILE *file;
%}

%code provides {
  int yylex (void);
  void yyerror (const char *);
}

%union {int n ; char id[16] ;}

%token <n> tNB // On prend le nombre
%token <id> tID // On prend l'identifiant

%token tMAIN tIF tELSE tWHILE tPRINT tRETURN tINT tVOID tASSIGN tLPAR tRPAR tLBRACE tRBRACE tCOMMA tSEMI tERROR

%left tOR
%left tAND
%left tEQ tNE
%left tLT tLE tGT tGE
%left tADD tSUB
%left tMUL tDIV
%right tNOT

%left tCOMMA

%type <n> Expression

%%

S :
    Function S
  | Main {printf("Main: %d\n", line_number);}
  ;

Main :
  tVOID tMAIN tLPAR tVOID tRPAR tLBRACE Body tRBRACE {printf("void main(void)\n");}
  ;

Body : 
    Declaration Body
  | Instruction Body
  | %empty {printf("Body empty\n");}
  ;


Declaration : 
    tINT DeclaredVariable tSEMI {printf("declaration int, line:%d\n", line_number);}
  ;

DeclaredVariable : 
    tID {printf("declared variable with tID '%s'\n", $1); st_insert($1,line_number);}
  | tID tASSIGN Expression {printf("declared variable with tID '%s' and expression\n", $1);}
  | DeclaredVariable tCOMMA DeclaredVariable {printf("declared variable with tCOMMA\n");}
  ;

FunctionCall : 
    tID tLPAR tRPAR {printf("function call: %s()\n", $1);}
  | tID tLPAR ParameterCall tRPAR {printf("function call: %s(params)\n", $1);}
  ;

ParameterCall : 
    Expression {printf("parameter call with expression\n");}
  | Expression tCOMMA ParameterCall {printf("parameter call with expression and tCOMMA\n");}
  ;

Expression : 
    tID {printf("expression with tID '%s'\n", $1);
          $$ = st_search($1);
        }
  | tNB {printf("expression with tNB '%d'\n", $1);
         int a = st_insert_tmp($1, line_number);
         st_print();
         fprintf(file,"AFC %d %d\n", a, $1);
         $$ = a;
        }
  | FunctionCall {printf("expression with function call\n");}
  | tLPAR Expression tRPAR {printf("expression with tLPAR and tRPAR\n");}
  | Expression tADD Expression {
          printf("expression with tADD\n");
          int address = st_insert_tmp(0, line_number);
          fprintf(file,"ADD %d %d %d\n", address, $1, $3);
          $$ = address;
        }
  | Expression tSUB Expression {printf("expression with tSUB\n");}
  | Expression tMUL Expression {printf("expression with tMUL\n");}
  | Expression tDIV Expression {printf("expression with tDIV\n");}
  | Expression tEQ Expression {printf("expression with tEQ\n");}
  | Expression tNE Expression {printf("expression with tNE\n");}
  | Expression tLT Expression {printf("expression with tLT\n");}
  | Expression tLE Expression {printf("expression with tLE\n");}
  | Expression tGT Expression {printf("expression with tGT\n");}
  | Expression tGE Expression {printf("expression with tGE\n");}
  | tSUB Expression {printf("expression with tSUB\n");}
  | tNOT Expression {printf("expression with tNOT\n");}
  | Expression tAND Expression {printf("expression with tAND\n");}
  | Expression tOR Expression {printf("expression with tOR\n");}
  ;

Instruction : 
    tID tASSIGN Expression tSEMI {
      printf("instruction with tID %s and expression %d\n", $1, $3);
      int a=st_search($1);
      fprintf(file,"COP %d %d\n", a, $3);
      st_pop_tmp_all();
      st_print();
      }
  | FunctionCall tSEMI {printf("instruction with function call\n");}
  | tRETURN Expression tSEMI {printf("instruction with tRETURN and expression\n");}
  | tPRINT tLPAR Expression tRPAR tSEMI {printf("instruction with tPRINT and expression\n");}
  | tIF tLPAR Expression tRPAR tLBRACE Body tRBRACE {printf("instruction with tIF and expression\n");}
  | tIF tLPAR Expression tRPAR tLBRACE Body tRBRACE tELSE tLBRACE Body tRBRACE {printf("instruction with tIF and tELSE\n");}
  | tWHILE tLPAR Expression tRPAR tLBRACE Body tRBRACE {printf("instruction with tWHILE and expression\n");}
  ;

Function : 
    tINT tID tLPAR Parameter tRPAR tLBRACE Body tRBRACE {printf("function int '%s' (params) \n", $2);}
  | tVOID tID tLPAR Parameter tRPAR tLBRACE Body tRBRACE {printf("function void '%s' (params) \n", $2);}
  | tVOID tID tLPAR tVOID tRPAR tLBRACE Body tRBRACE {printf("function void '%s'(void) \n", $2);}
  | tINT tID tLPAR tVOID tRPAR tLBRACE Body tRBRACE {printf("function int '%s'(void) \n", $2);}
  ;

Parameter : 
    tINT tID {printf("parameter int '%s'\n", $2);}
  | tINT tID tCOMMA Parameter {printf("parameter int '%s' and tCOMMA\n", $2);}
  ;

%%

void yyerror(const char *msg) {
  fprintf(stderr, "error: %s\n", msg);
  exit(1);
}

int main(void) {
  file = fopen("asm.txt", "w");
  if (file == NULL) {
    fprintf(stderr, "Can't open file\n");
    exit(1);
  }

  yyparse();
  st_print();
  fclose(file);

  // st_test();
}

