/**
 * @file asm.c
 * @author Ronan Bonnet
 * @author Anna Cazeneuve
 * @brief  This file contains the implementation of the assembly code generation
 * @version 0.1
 * @date 2024-04-10
 * @bug No known bugs
 * @todo Add error handling
 * @todo Add more functions such as if, while, etc. 
 */
#include "asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "instructions_table.h"

/**
 * @brief A macro to generate the assembly code for a binary operation
 * 
 * As the assembly code for binary operations is very similar, we can
 * use a macro to generate the code for each operation. The macro takes
 * two arguments: the name of the operation and the opcode of the operation.
 * 
 * @param instruction the name of the operation
 * @param opcode the opcode of the operation
 * 
 * The macro generates a function with the name asm_instruction that takes
 * four arguments: the line number in the code, the address of the first
 * operand, the address of the second operand and the depth of the symbol table.
 * Symbol table is used to store the result of the operation. If the operands
 * are temporary variables, they are popped from the stack. The result is pushed
 * on the stack. The instruction is inserted in the instruction table. The address
 * of the result is returned.
 * 
 */
#define ASSEMBLE_BINARY_OP(instruction, opcode) \
int asm_##instruction(int line_number, int address1, int address2, int depth) {\
    printf("expression with t" #instruction " '%d' " #opcode " '%d'\n", address1, address2); \
    if(st_is_tmp(address1)) {st_pop_tmp();} \
    if(st_is_tmp(address2)) {st_pop_tmp();} \
    int address = st_insert_tmp(0, line_number, depth); \
    st_print(); \
    it_pretty_print(); \
    it_insert(opcode, address, address1, address2); \
    return address; \
}

//
// ARITHMETIC BINARY OPERATIONS
//
ASSEMBLE_BINARY_OP(add, iADD) // Addition
ASSEMBLE_BINARY_OP(sub, iSOU) // Subtraction
ASSEMBLE_BINARY_OP(mul, iMUL) // Multiplication
ASSEMBLE_BINARY_OP(div, iDIV) // Division

//
// LOGICAL BINARY OPERATIONS
//
ASSEMBLE_BINARY_OP(eq, iEQ)   // Equal
ASSEMBLE_BINARY_OP(ne, iNEQ)  // Not equal
ASSEMBLE_BINARY_OP(lt, iLT)   // Less than 
ASSEMBLE_BINARY_OP(gt, iGT)   // Greater than
ASSEMBLE_BINARY_OP(le, iLE)   // Less than or equal
ASSEMBLE_BINARY_OP(ge, iGE)   // Greater than or equal
ASSEMBLE_BINARY_OP(and, iAND) // Logical AND
ASSEMBLE_BINARY_OP(or, iOR)   // Logical OR

/* Number entry */
int asm_nb(int line_number, int address1, int depth){
    printf("expression with tNB '%d'\n", address1);
    
    // Create a temporary symbol for the result
    int a = st_insert_tmp(address1, line_number, depth);
    st_print();
    it_pretty_print();
    it_insert(iAFC, a, address1, 0);
    return a;
}

/* Variable assignment */
void asm_assign(char* address1, int address2){
    printf("instruction with tID %s and expression %d\n", address1, address2);
    
    // Get the address of the variable to assign to
    int a=st_search(address1);
    it_insert(iCOP, a, address2, 0);
    st_pop_tmp(); // Pop the result of the expression
    st_print();
    it_pretty_print();
}

/* Number negation */
int asm_neg_nb(int line_number, int address1, int depth){
    printf("expression with tSUB\n");
    // Create a temporary symbol for the result
    int address = st_insert_tmp(0, line_number, depth);
    // Store 0 in the result
    it_insert(iAFC, address, 0 , 0);
    // Subtract the number from 0(0 - number = -number)
    it_insert(iSOU, address, address, address1);
    return address;
}

/* Number logical NOT */
int asm_not(int line_number, int address1, int depth){
    printf("expression with tNOT\n");
    int address = st_insert_tmp(0, line_number, depth);
    it_insert(iNOT, address, 0, 0);
    return address;
}

/* Print instruction */
void asm_print(int address1) {
    printf("instruction with tPRINT and expression\n");
    if(st_is_tmp(address1)) {st_pop_tmp();}
    it_insert(iPRINT,address1, 0,0);
}