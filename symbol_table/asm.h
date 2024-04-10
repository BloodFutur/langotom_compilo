#ifndef ASM_H
#define ASM_H


#include <stdio.h>

// @TODO : Check that a variable is declared before using it (search returns -1 if not found)
// @TODO: LE and GE => create operator asm.
// @TODO: Correct NEG number

int asm_nb(int line_number, int address1, int depth);

void asm_assign(char* address1, int address2);

int asm_add(int line_number, int address1, int address2, int depth);
int asm_sub(int line_number, int address1, int address2, int depth);
int asm_mul(int line_number, int address1, int address2, int depth);
int asm_div(int line_number, int address1, int address2, int depth);

int asm_eq(int line_number, int address1, int address2, int depth);
int asm_ne(int line_number, int address1, int address2, int depth);
int asm_lt(int line_number, int address1, int address2, int depth);
int asm_gt(int line_number, int address1, int address2, int depth);
int asm_le(int line_number, int address1, int address2, int depth);
int asm_ge(int line_number, int address1, int address2, int depth);

int asm_neg_nb(int line_number, int address1, int depth);
int asm_not(int line_number, int address1, int depth);

int asm_and(int line_number, int address1, int address2, int depth);
int asm_or( int line_number, int address1, int address2, int depth);

void asm_print(int address1);

//void asm_if()

#endif // ASM_H 