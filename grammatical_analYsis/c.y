%{
  #include <stdio.h>
  #include <stdlib.h>
%}

%code provides {
  int yylex (void);
  void yyerror (const char *);
}

%union {int n ; char id[16] ;}

%token <n> tNB // On prend le nombre
%token <id> tID // On prend l'identifiant

%token tIF tELSE tWHILE tPRINT tRETURN tINT tVOID tASSIGN tLPAR tRPAR tLBRACE tRBRACE tCOMMA tSEMI tERROR

%left tOR
%left tAND
%left tEQ tNE
%left tLT tLE tGT tGE
%left tADD tSUB
%left tMUL tDIV
%right tNOT

%left tCOMMA

%%

S : 
    Function S
  | %empty  
  ;

Body : 
    Declaration Body
  | Instruction Body
  | %empty  
  ;


Declaration : 
    tINT DeclaredVariable tSEMI  
  ;

DeclaredVariable : 
    tID  
  | tID tASSIGN Expression  
  | DeclaredVariable tCOMMA DeclaredVariable  
  ;

FunctionCall : 
    tID tLPAR tRPAR  
  | tID tLPAR ParameterCall tRPAR  
  ;

ParameterCall : 
    Expression  
  | Expression tCOMMA ParameterCall  
  ;

Expression : 
    tID  
  | tNB  
  | FunctionCall  
  | tLPAR Expression tRPAR  
  | Expression tADD Expression  
  | Expression tSUB Expression  
  | Expression tMUL Expression  
  | Expression tDIV Expression  
  | Expression tEQ Expression  
  | Expression tNE Expression  
  | Expression tLT Expression  
  | Expression tLE Expression  
  | Expression tGT Expression  
  | Expression tGE Expression  
  | tSUB Expression  
  | tNOT Expression  
  | Expression tAND Expression  
  | Expression tOR Expression  
  ;

Instruction : 
    tID tASSIGN Expression tSEMI  
  | FunctionCall tSEMI  
  | tRETURN Expression tSEMI  
  | tPRINT tLPAR Expression tRPAR tSEMI  
  | tIF tLPAR Expression tRPAR tLBRACE Body tRBRACE  
  | tIF tLPAR Expression tRPAR tLBRACE Body tRBRACE tELSE tLBRACE Body tRBRACE  
  | tWHILE tLPAR Expression tRPAR tLBRACE Body tRBRACE  
  ;

Function : 
    tINT tID tLPAR Parameter tRPAR tLBRACE Body tRBRACE  
  | tVOID tID tLPAR Parameter tRPAR tLBRACE Body tRBRACE  
  | tVOID tID tLPAR tVOID tRPAR tLBRACE Body tRBRACE  
  | tINT tID tLPAR tVOID tRPAR tLBRACE Body tRBRACE  
  ;

Parameter : 
    tINT tID  
  | tINT tID tCOMMA Parameter  
  ;

%%

void yyerror(const char *msg) {
  fprintf(stderr, "error: %s\n", msg);
  exit(1);
}

int main(void) {
  yyparse();
}

