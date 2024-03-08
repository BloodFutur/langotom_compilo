%{
    #include <stdio.h>
    #include <stdlib.h>
}

%code provides {
    int yylex (void);
    void yyerror (const char *);
}

%union {int n ; char id[16] ;}

%token <n> tNB // On prend le nombre
%token <id> tID // On prend l'identifiant

%token tID tNB tIF tELSE tWHILE tPRINT tRETURN tINT tVOID tADD 
%token tSUB tMUL tDIV tASSIGN tEQ tNE tLT tLE tGT tGE tAND tOR tNOT tLPAR tRPAR tLBRACE tRBRACE tCOMMA tSEMI tERROR

%%

S : Function S 
  | Main %empty
  ;

Main : tVOID tID "main" tLPAR tVOID tRPAR tLBRACE Body tRBRACE
  ;

Body : Declaration Body
     | Instruction Body
     | %empty
     ;

Operator : tADD
         | tSUB
         | tMUL
         | tDIV
         | tEQ
         | tNE
         | tLT
         | tLE
         | tGT
         | tGE
         | tAND
         | tOR
         | tNOT
         ;

Declaration : tINT tID tSEMI
            | tINT tID tASSIGN Expression tSEMI
            ;

Expression : tID
            | tNB
            | tLPAR Expression tRPAR
            | Expression Operator Expression
            ;

Instruction : tID tASSIGN Expression
            | tPRINT tLPAR Expression tRPAR tSEMI
            | tIF tLPAR Expression tRPAR tLBRACE Body tRBRACE
            | tIF tLPAR Expression tRPAR tLBRACE Body tRBRACE tELSE tLBRACE Body tRBRACE
            | tWHILE tLPAR Expression tRPAR tLBRACE Body tRBRACE
            ;

Function : tINT tID tLPAR Parameter tRPAR tLBRACE Body tRETURN Expression tSEMI tRBRACE
         | tVOID tID tLPAR Parameter tRPAR tLBRACE Body tRBRACE
         | tVOID tID tLPAR tVOID tRPAR tLBRACE Body tRBRACE
         | tINT tID tLPAR tVOID tRPAR tLBRACE Body tRETURN Expression tSEMI tRBRACE
         ;

Parameter : tINT tID
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
