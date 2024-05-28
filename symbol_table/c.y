%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "symbol_table.h"
  #include "asm.h"
  #include "instructions_table.h"
  #include "functions_table.h"
  extern int line_number;
  int depth = 0;
  int nb_params = 0;
  int nb_args = 0;
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

S : {
    printf("S empty\n");
    it_insert(iJMP, -1, 0, 0);
  } Program {printf("S with Program\n");}
  ;


Program:
    Function Program
  | Main {printf("Main: %d\n", line_number);}
  ;

Main :
  tVOID tMAIN 
  {
    it_patch_op1(0,it_get_index());
    // st_insert("main", line_number, depth);
    ft_insert("main", it_get_index());
    // Insert return address and value
    st_insert("?VALMain", line_number, depth);
    // st_insert("?ADRMain", line_number, depth);
  } tLPAR tVOID tRPAR LBRACE Body RBRACE 
  {
    st_pop_depth(depth);
    printf("void main(void)\n");
    it_insert(iRET, 0, 0, 0);
    it_insert(iNOP, 0, 0, 0);
  }
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
          st_insert($1,line_number, depth);
          }
  | tID {
          printf("declared variable with tID '%s'\n", $1); 
          st_insert($1,line_number, depth);
  } tASSIGN Expression {
          printf("Expression: %d\n", $4);
          asm_assign($1, $4);        
        }
  | DeclaredVariable tCOMMA DeclaredVariable {printf("declared variable with tCOMMA\n");}
  ;

FunctionCall : 
    tID tLPAR tRPAR {printf("function call: %s()\n", $1);}
  | tID tLPAR 
    {
      depth++;
      $2 = st_get_count();
      st_insert("!ADR", line_number, depth);
      st_insert("!VAL", line_number, depth);
    } ParameterCall tRPAR 
    {
      it_insert(iPUSH, $2, 0, 0);
      it_insert(iCALL, ft_search($1), 0, 0);
      it_insert(iPOP, $2, 0, 0);

      printf("NB ARGS: %d\n", nb_args);
      st_print();
      // Remove the parameters from the symbol table
      // for(int i = 0; i < nb_args; i++) {
      //   st_pop();
      // }

      st_pop();
      st_pop();


      printf("Depth: %d\n", depth);
      

      // st_pop_depth(depth); // Remove badly managed symbols
      printf("RES??? %d", $2);
      nb_args = 0;
      int iADR = st_search("!ADR");

      int iVAL = st_get_count();
      $$ = iVAL;
      printf("iVAL: %d\n", iVAL);
      
      // it_insert(iCOP, iADR, iADR+1, 0);
      printf("function call: %s(params)\n", $1);

      printf("Symbol table after function call\n:");
      st_print();
      depth--;

    }
  ;

ParameterCall : 
    Expression 
    {
      // Argument is a tmp variable
      st_pop();

      // Get the value of the expression
      int expressionVal = st_get_tmp($1);
      printf("expressionVal: %d\n", expressionVal);

      // Insert var name in symbol table
      // Make a copy of the expression to it 
      char str[16];
      sprintf(str, "%d", expressionVal);
      st_insert(str, line_number, depth);
      // st_insert_tmp($1, line_number, depth);
      nb_args++;
      printf("parameter call with expression\n");
    }
  | Expression tCOMMA ParameterCall {printf("parameter call with expression and tCOMMA\n");}
  ;

Expression : 
    tID {printf("expression with tID '%s'\n", $1);
          $$ = st_search($1);
        }
  | tNB { $$ = asm_nb(line_number, $1, depth); }
  | FunctionCall {$$ = $1;printf("expression with function call, %d\n", $1);}
  | tLPAR Expression tRPAR { printf("expression with tLPAR and tRPAR\n"); $$ = $2;
        }
  | Expression tADD Expression { $$ = asm_add(line_number, $1, $3, depth); }
  | Expression tSUB Expression { $$ = asm_sub(line_number, $1, $3, depth); }
  | Expression tMUL Expression { $$ = asm_mul(line_number, $1, $3, depth); }
  | Expression tDIV Expression { $$ = asm_div(line_number, $1, $3, depth); }
  | Expression tEQ Expression  { $$ = asm_eq(line_number, $1, $3, depth); }
  | Expression tNE Expression {$$ = asm_ne(line_number, $1, $3, depth);}
  | Expression tLT Expression  { $$ = asm_lt(line_number, $1, $3, depth); }
  | Expression tLE Expression {$$ = asm_le(line_number, $1, $3, depth);}
  | Expression tGT Expression  { $$ = asm_gt(line_number, $1, $3, depth);}
  | Expression tGE Expression {$$ = asm_ge(line_number, $1, $3, depth);}
  | tSUB Expression {$$ = asm_neg_nb(line_number, $2, depth);}
  | tNOT Expression { $$ = asm_not(line_number, $2, depth);}
  | Expression tAND Expression {$$ = asm_and(line_number, $1, $3, depth);}
  | Expression tOR Expression {$$ = asm_or(line_number, $1, $3, depth);}
  ;

Instruction : 
    tID tASSIGN Expression tSEMI { asm_assign($1, $3); printf("ASSIGN with id: %s and expression: %d", $1, $3); }
  | FunctionCall tSEMI {printf("instruction with function call\n");}
  | tRETURN Expression tSEMI 
    {
      // Get ?VAL address
      st_print();
      int iVAL = st_search("?VAL");
      it_insert(iCOP, iVAL, $2, 0);
      it_insert(iRET, 0, 0, 0);
      printf("instruction with tRETURN and expression\n");
    }
  | tPRINT tLPAR Expression tRPAR tSEMI { asm_print($3); }
  | tIF tLPAR Expression tRPAR LBRACE
    {
      printf("Expression: %d\n", $3);
      //JMP to unknown line if condition not met
      if(st_is_tmp($3)) {st_pop_tmp();}
      int line_return = it_insert(iJMPF, $3, -1, 0); 
      $1 = line_return;
    } 
    Body 
    {
      // Update the line number of the JMPF instruction
      int current = it_get_index();
      it_patch_op2($1, current+1);
    } 
    RBRACE ElsePart
    
  | tWHILE tLPAR Expression tRPAR LBRACE 
    {
      printf("Expression: %d\n", $3);
      //JMP to unknown line if condition not met
      int line_return = it_insert(iJMPF, $3, -1, 0); 
      $1 = line_return;
    } Body RBRACE {
      printf("instruction with tWHILE and expression\n");
      // Update the line number of the JMPF instruction
      int current = it_get_index();
      it_patch_op2($1, current+1);
      //JMP to the entry of while loop again after executing body
      it_insert(iJMP, $1-1, 0, 0);
      st_pop_tmp(); // @TODO: check if this is correct,we need to pop 
      // the temporary variable from the stack at a moment but idk when
    }
  ;

ElsePart : 
    tELSE LBRACE {
      // Add a JMP instruction to jump to the end of the if/else block
      int line_return = it_insert(iJMP, -1, 0, 0);
      $1 = line_return;
    
    } Body {
      // Update the line number of the JMP instruction
      int current = it_get_index();
      it_patch_op1($1, current);
    
    } RBRACE {printf("else part with tELSE\n");}
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
    tINT tID 
    {
      printf("function int '%s'\n", $2);
      // st_insert($2, line_number, depth);
      ft_insert($2, it_get_index());
      // Insert return address
      // Insert return value
      st_insert("?ADR", line_number, depth);
      st_insert("?VAL", line_number, depth);
    } tLPAR Parameter tRPAR
    LBRACE {

    } Body RBRACE 
    {
      printf("function int '%s' (params) \n", $2);

      // Remove the parameters from the symbol table
      for(int i = 0; i < nb_params; i++) {
        st_pop();
      }
      nb_params = 0;

      // Remove the return address and value from the symbol table
      st_pop();
      st_pop();

      it_insert(iRET, 0, 0, 0);
    }
  | tVOID tID tLPAR Parameter tRPAR LBRACE Body RBRACE {printf("function void '%s' (params) \n", $2);}
  | tVOID tID tLPAR tVOID tRPAR LBRACE Body RBRACE {printf("function void '%s'(void) \n", $2);}
  // | tINT tID tLPAR tVOID tRPAR LBRACE Body RBRACE {printf("function int '%s'(void) \n", $2);}
  ;

Parameter : 
    tINT tID {st_insert($2, line_number, depth+1); nb_params++; printf("parameter int '%s'\n", $2);}
  | tINT tID tCOMMA Parameter {printf("parameter int '%s' and tCOMMA\n", $2);}
  ;

LBRACE : tLBRACE {depth++;printf("LBRACE\n");}
RBRACE : tRBRACE {depth--;printf("RBRACE\n");}

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
  ft_print();
  // st_test();
  // it_test();
}

