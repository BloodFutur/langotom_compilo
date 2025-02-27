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
#include "functions_table.h"

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


void asm_init() {
    // By default, the main function is the entry point of the program
    // The first instruction sets the return address to -1 so that the program stops
    it_insert(iAFC, 0, -1, 0);
    it_insert(iJMP, -1, 0, 0);
}

void asm_main_start(int line_number, int depth) {
    // Update the instruction index of the main function to jump to the main function
    // when the program starts
    it_patch_op1(1,it_get_index());

    // Insert main function in the function table
    ft_insert("main", it_get_index());
    st_insert("?ADRMain", line_number, depth);
    st_insert("?VALMain", line_number, depth);
}

void asm_main_end(int depth) {
    // Remove everything from the symbol table
    // Should only remain the return address and value
    st_pop_depth(depth);
    printf("void main(void)\n");
    it_insert(iRET, 0, 0, 0);
    it_insert(iNOP, 0, 0, 0);
}

/* Var entry*/
void asm_var(char* name, int line_number, int depth) {
    printf("declared variable with tID '%s'\n", name); 
    st_insert(name,line_number, depth);
    st_print();
}

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
    if(st_is_tmp(address2)) {st_pop_tmp();}

    // st_pop_tmp(); // Pop the result of the expression
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

void asm_function_new_start(char* name, int line_number, int depth) {
    printf("function int '%s'\n", name);
    // Add the function to the function table
    ft_insert(name, it_get_index());
    // Insert return and value address in the symbol table
    st_insert("?ADR", line_number, depth);
    st_insert("?VAL", line_number, depth);
}

void asm_function_new_end(int nb_params) {
    // Remove the parameters from the symbol table
    for(int i = 0; i < nb_params; i++) {
    st_pop();
    }

    // Remove the return address and value from the symbol table
    st_pop();
    st_pop();

    it_insert(iRET, 0, 0, 0);
}

/* Function preparation */
int asm_function_prepare_stack(int line_number, int depth) {
    int tsp = st_get_count(); // Get the symbol table size (stack size)
    
    // Insert return address and value
    st_insert("!ADR", line_number, depth);
    st_insert("!VAL", line_number, depth);

    return tsp;
}

/* Function call */
int asm_function_call(char* name, int tsp, int depth) {
    // Create new frame for the function call
      it_insert(iPUSH, tsp, 0, 0);
      it_insert(iCALL, ft_search(name), 0, 0);
      it_insert(iPOP, tsp, 0, 0);

      // Remove the return address and value from the symbol table
      st_pop();
      st_pop();      

      // Remove the badly managed symbols
      // Should not remove anything, but just in case
      st_pop_depth(depth);


      // Get the return value of the function to use it in the expression
      int iVAL = st_get_count();
      
      printf("function call: %s(params)\n", name);
      st_print(); // Print the symbol table, should not contain the function call symbols

      return iVAL+1;
}

/* Function call arguments */
void asm_function_call_arg(int address, int arg_index, int line_number, int depth) {
    // If the expression is a temporary variable
      // we need to pop it from the symbol table and insert it again in the symbol table as a new variable
      // to use it in the function call
      // If the expression is a variable, we can use it directly
      // and copy its value to the argument variable reserved in the stack
      // 
      // Argument name is arg0, arg1, arg2, etc.      
      if(st_is_tmp(address))
      {
        st_pop();

        // Get the value of the expression
        int expressionVal = st_get_tmp(address);
        printf("expressionVal: %d\n", expressionVal);

        // Insert the expression in the symbol table as a new variable
        char str[16];

        sprintf(str, "arg%d", arg_index);
        st_insert(str, line_number, depth);
      } else {
        // Copy the value of the variable to the argument variable reserved in the stack
        char str[16];
        sprintf(str, "arg%d", arg_index);
        int res = st_insert(str, line_number, depth);
        it_insert(iCOP, res, address, 0);
      }
}

/* Function return */
void asm_function_return(int expression_address, int depth) {
      // Get ?VAL address
      st_print();

      // Get the return value of the current function
      // and insert the expression in the return value
      int iVAL = st_search("?VAL");
      it_insert(iCOP, iVAL, expression_address, 0);

      // Should not remove anything, but just in case
      st_pop_depth(depth);

      // Return to the return address
      it_insert(iRET, 0, 0, 0);
      printf("instruction with tRETURN and expression\n");
}

/* If preparatino*/
int asm_if_prepare(int expression_address) {
    if(st_is_tmp(expression_address)) {st_pop_tmp();}
    return it_insert(iJMPF, expression_address, -1, 0); 
}

/* If patch*/
void asm_if_patch(int jmp_address) {
    // Update the line number of the JMPF instruction
    int current = it_get_index();
    it_patch_op2(jmp_address, current+1);
}

/* Else preparation */
int asm_else_prepare() {
    // Add a JMP instruction to jump to the end of the if/else block
    return it_insert(iJMP, -1, 0, 0);
}

/* Else patch */
void asm_else_patch(int jmp_address) {
    // Update the line number of the JMP instruction
    it_patch_op1(jmp_address, it_get_index());
}

/* Else empty */
void asm_else_empty() {
    // Add a NOP instruction if the else part is empty
    // because we jump to the end of the if block and if there is a else part,
    // we have one more instruction to execute
    it_insert(iNOP, 0, 0, 0);
}

/* While preparation */
int asm_while_prepare(int expression_address) {
    return it_insert(iJMPF, expression_address, -1, 0); 
}

/* While patch */
void asm_while_patch(int jmp_address) {
    // Update the line number of the JMPF instruction
    it_patch_op2(jmp_address, it_get_index()+1);
    // JMP to the entry of while loop again after executing body
    it_insert(iJMP, jmp_address-1, 0, 0);
    st_pop_tmp(); // @TODO: check if this is correct,we need to pop 
    // the temporary variable from the stack at a moment but idk when
}
