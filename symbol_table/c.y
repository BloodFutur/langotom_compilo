/* 
 * @file  c.y
 * @brief  Yacc file for a simple C compiler
 * @author Ronan & Anna
 * @date  2024-05-29
 */
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "symbol_table.h"
  #include "asm.h"
  #include "instructions_table.h"
  #include "functions_table.h"


  extern int line_number; // Defined in lex.c
  int depth = 0;          // Scope depth
  int nb_params = 0;      // Number of parameters in a function
  int nb_args = 0;        // Number of arguments in a function call
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
%token <n> tLPAR

%token tMAIN tPRINT tRETURN tINT tVOID tASSIGN tRPAR tLBRACE tRBRACE tCOMMA tSEMI tERROR

%left tOR
%left tAND
%left tEQ tNE
%left tLT tLE tGT tGE
%left tADD tSUB
%left tMUL tDIV
%right tNOT

%left tCOMMA

%type <n> Expression
%type <n> FunctionCall

%%

S : { asm_init(); } Program
  ;


Program:
    Function Program
  | Main 
  ;

Main :
  tVOID tMAIN { asm_main_start(line_number, depth); } tLPAR tVOID tRPAR LBRACE Body RBRACE { asm_main_end(depth); }
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
    tID { asm_var($1, line_number, depth); }
  | tID { asm_var($1, line_number, depth); } tASSIGN Expression { asm_assign($1, $4); }
  | DeclaredVariable tCOMMA DeclaredVariable
  ;

FunctionCall : 
    tID tLPAR tRPAR {printf("function call: %s()\n", $1);}
  | tID tLPAR 
    {
      depth++;       // New scope
      $2 = asm_function_prepare_stack(line_number, depth);
    } ParameterCall tRPAR 
    {
      $$ = asm_function_call($1, $2, depth);
      depth--;       // Go back to the previous scope
      nb_args = 0;   // Reset for the next function call
    }
  ;

ParameterCall : 
    Expression 
    {
      asm_function_call_arg($1, nb_args, line_number, depth);
      nb_args++;
    }
  | ParameterCall tCOMMA ParameterCall
  ;

Expression : 
    tID                        { $$ = st_search($1);} 
  | tNB                        { $$ = asm_nb(line_number, $1, depth); }
  | FunctionCall               { $$ = $1; }
  | tLPAR Expression tRPAR     { $$ = $2; }
  | Expression tADD Expression { $$ = asm_add(line_number, $1, $3, depth); }
  | Expression tSUB Expression { $$ = asm_sub(line_number, $1, $3, depth); }
  | Expression tMUL Expression { $$ = asm_mul(line_number, $1, $3, depth); }
  | Expression tDIV Expression { $$ = asm_div(line_number, $1, $3, depth); }
  | Expression tEQ Expression  { $$ = asm_eq(line_number, $1, $3, depth); }
  | Expression tNE Expression  { $$ = asm_ne(line_number, $1, $3, depth);}
  | Expression tLT Expression  { $$ = asm_lt(line_number, $1, $3, depth); }
  | Expression tLE Expression  { $$ = asm_le(line_number, $1, $3, depth);}
  | Expression tGT Expression  { $$ = asm_gt(line_number, $1, $3, depth);}
  | Expression tGE Expression  { $$ = asm_ge(line_number, $1, $3, depth);}
  | tSUB Expression            { $$ = asm_neg_nb(line_number, $2, depth);}
  | tNOT Expression            { $$ = asm_not(line_number, $2, depth);}
  | Expression tAND Expression { $$ = asm_and(line_number, $1, $3, depth);}
  | Expression tOR Expression  { $$ = asm_or(line_number, $1, $3, depth);}
  ;

Instruction : 
    tID tASSIGN Expression tSEMI          { asm_assign($1, $3); }
  | FunctionCall tSEMI                    { printf("instruction with function call\n");}
  | tRETURN Expression tSEMI              { asm_function_return($2, depth); }
  | tPRINT tLPAR Expression tRPAR tSEMI   { asm_print($3); }
  | tIF tLPAR Expression tRPAR LBRACE     { $1 = asm_if_prepare($3);   } Body { asm_if_patch($1); } RBRACE ElsePart
  | tWHILE tLPAR Expression tRPAR LBRACE  { $1 = asm_while_prepare($3);} Body RBRACE { asm_while_patch($1); }
  ;

ElsePart : 
    tELSE LBRACE { $1 = asm_else_prepare();} Body { asm_else_patch($1); } RBRACE
  | %empty { asm_else_empty(); }
  ;

Function : 
    tINT tID { asm_function_new_start($2, line_number, depth); } tLPAR Parameter tRPAR LBRACE Body RBRACE 
    {
      asm_function_new_end(nb_params);
      nb_params = 0;
    }
  | tVOID tID tLPAR Parameter tRPAR LBRACE Body RBRACE {printf("function void '%s' (params) \n", $2);}
  // | tVOID tID tLPAR tVOID tRPAR LBRACE Body RBRACE {printf("function void '%s'(void) \n", $2);}
  // | tINT tID tLPAR tVOID tRPAR LBRACE Body RBRACE {printf("function int '%s'(void) \n", $2);}
  ;

Parameter : 
    tINT tID {st_insert($2, line_number, depth); nb_params++; printf("parameter int '%s'\n", $2);}
  | tVOID
  | Parameter tCOMMA Parameter {printf("parameters and tCOMMA\n");}
  ;

LBRACE : tLBRACE {depth++;printf("LBRACE\n");}
RBRACE : tRBRACE {depth--;printf("RBRACE\n");}

%%

void yyerror(const char *msg) {
  fprintf(stderr, "error: %s\n", msg);
  exit(1);
}

int main(void) {
  yyparse();

  // Print all the tables
  st_print();
  it_pretty_print();
  it_print_asm();
  ft_print();
}

