%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "symbol_table.h"
  #include "asm.h"
  #include "instructions_table.h"
  extern int line_number;
%}

%code provides {
  int yylex (void);
  void yyerror (const char *);
}

%union {int n ; char id[16] ;}

%token <n> tNB // On prend le nombre
%token <id> tID // On prend l'identifiant
%token <n> tIF tELSE
%token <n> tWHILE

%token tMAIN tPRINT tRETURN tINT tVOID tASSIGN tLPAR tRPAR tLBRACE tRBRACE tCOMMA tSEMI tERROR

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
    tID {
          printf("declared variable with tID '%s'\n", $1); 
          st_insert($1,line_number);
          }
  | tID tASSIGN Expression {
          printf("declared variable with tID '%s' and expression\n", $1);
          st_insert($1,line_number);
          asm_assign($1, $3);          
        }
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
  | tNB { $$ = asm_nb(line_number, $1); }
  | FunctionCall {printf("expression with function call\n");}
  | tLPAR Expression tRPAR { printf("expression with tLPAR and tRPAR\n"); $$ = $2;
        }
  | Expression tADD Expression { $$ = asm_add(line_number, $1, $3); }
  | Expression tSUB Expression { $$ = asm_sub(line_number, $1, $3); }
  | Expression tMUL Expression { $$ = asm_mul(line_number, $1, $3); }
  | Expression tDIV Expression { $$ = asm_div(line_number, $1, $3); }
  | Expression tEQ Expression  { $$ = asm_eq(line_number, $1, $3); }
  | Expression tNE Expression {$$ = asm_ne(line_number, $1, $3);}
  | Expression tLT Expression  { $$ = asm_lt(line_number, $1, $3); }
  | Expression tLE Expression {$$ = asm_le(line_number, $1, $3);}
  | Expression tGT Expression  { $$ = asm_gt(line_number, $1, $3);}
  | Expression tGE Expression {$$ = asm_ge(line_number, $1, $3);}
  | tSUB Expression {$$ = asm_neg_nb(line_number, $2);}
  | tNOT Expression { $$ = asm_not(line_number, $2);}
  | Expression tAND Expression {$$ = asm_and(line_number, $1, $3);}
  | Expression tOR Expression {$$ = asm_or(line_number, $1, $3);}
  ;

Instruction : 
    tID tASSIGN Expression tSEMI { asm_assign($1, $3); }
  | FunctionCall tSEMI {printf("instruction with function call\n");}
  | tRETURN Expression tSEMI {printf("instruction with tRETURN and expression\n");}
  | tPRINT tLPAR Expression tRPAR tSEMI { asm_print($3); }
  | tIF tLPAR Expression tRPAR tLBRACE
    {
      printf("Expression: %d\n", $3);
      //JMP to unknown line if condition not met
      int line_return = it_insert(iJMPF, $3, -1, 0); 
      $1 = line_return;
    } 
    Body 
    {
      // Update the line number of the JMPF instruction
      int current = it_get_index();
      it_patch_op2($1, current+1);
    } 
    tRBRACE ElsePart
    
  | tWHILE tLPAR Expression tRPAR tLBRACE 
    {
      printf("Expression: %d\n", $3);
      //JMP to unknown line if condition not met
      int line_return = it_insert(iJMPF, $3, -1, 0); 
      $1 = line_return;
    } Body tRBRACE {
      printf("instruction with tWHILE and expression\n");
      // Update the line number of the JMPF instruction
      int current = it_get_index();
      it_patch_op2($1, current+1);
      //JMP to the entry of while loop again after executing body
      it_insert(iJMP, $1-1, 0, 0);
    }
  ;

ElsePart : 
    tELSE tLBRACE {
      // Add a JMP instruction to jump to the end of the if/else block
      int line_return = it_insert(iJMP, -1, 0, 0);
      $1 = line_return;
    
    } Body {
      // Update the line number of the JMP instruction
      int current = it_get_index();
      it_patch_op1($1, current);
    
    } tRBRACE {printf("else part with tELSE\n");}
  | %empty 
    {
      // Add a NOP instruction if the else part is empty
      // because we jump to the end of the if block and if there is a else part,
      // we have one more instruction to execute
      printf("else part empty\n");
      it_insert(iNOP, 0, 0, 0);
    }
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

  // asm_init();
  yyparse();
  st_print();

  // asm_close();
  it_pretty_print();
  it_print_asm();
  // st_test();
  // it_test();
}

