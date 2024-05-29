/**
 * @file asm.h
 * @author Ronan Bonnet
 * @author Anna Cazeneuve
 * @brief This file contains prototypes for the assembly code generation
 * 
 * This file contains the prototypes for the functions that generate the
 * assembly code for the different operations of the language. It
 * uses an instruction table to store the generated instructions. It also
 * uses the symbol table to store the temporary variables and symbols such
 * as variables, functions, etc.
 *  
 * @version 0.1
 * @date 2024-04-10
 * 
 * @bug No known bugs
 * @todo Add error handling
 * 
 */
#ifndef ASM_H
#define ASM_H

#include <stdio.h>

//
// PROGRAM RELATED OPERATIONS
//

/**
 * @brief Initialize the assembly code generation
 * 
 * This function initializes the assembly code generation. It
 * initializes the instruction table.
 * 
 */
void asm_init();

/**
 * @brief Generate the assembly code for the start of the main function
 * 
 * This function generates the assembly code for the start of the main
 * function. It inserts the main function in the function table and
 * prepares the stack for the main function.
 *
 * @param line_number   the line number in the code
 * @param depth         the depth of the symbol table
 */
void asm_main_start(int line_number, int depth);

/**
 * @brief Generate the assembly code for the end of the main function
 * 
 * This function generates the assembly code for the end of the main
 * function. It inserts the return instruction in the instruction table.
 * It pops the stack and returns the result.
 * 
 * @param depth the depth of the symbol table
 */
void asm_main_end(int depth);


//
// ARITHMETIC BINARY OPERATIONS
//


/**
 * @brief Generate the assembly code for an addition
 * 
 * This function generates the assembly code for an addition
 * operation. If the operands are temporary variables, they are
 * popped from the stack. The result is pushed on the stack.
 * The instruction is inserted in the instruction table. The 
 * address of the result is returned.
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_add(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a subtraction
 * 
 * This function generates the assembly code for a subtraction.
 * If the operands are temporary variables, they are popped from
 * the stack. The result is pushed on the stack. The instruction
 * is inserted in the instruction table. The address of the result
 * is returned.
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_sub(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a multiplication
 * 
 * This function generates the assembly code for a multiplication.
 * If the operands are temporary variables, they are popped from
 * the stack. The result is pushed on the stack. The instruction
 * is inserted in the instruction table. The address of the result
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_mul(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a division
 * 
 * This function generates the assembly code for a division.
 * If the operands are temporary variables, they are popped from
 * the stack. The result is pushed on the stack. The instruction
 * is inserted in the instruction table. The address of the result
 * 
 * @note This function does not handle division by zero
 * 
 * @param line_number 
 * @param address1 
 * @param address2 
 * @param depth 
 * @return int 
 */
int asm_div(int line_number, int address1, int address2, int depth);


//
// LOGICAL BINARY OPERATIONS
//


/**
 * @brief Generate the assembly code for an equal comparison
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_eq(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a not equal comparison
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_ne(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a less than comparison
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_lt(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a greater than comparison
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_gt(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a less than or equal comparison
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_le(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a greater than or equal comparison
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_ge(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a logical AND operation
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_and(int line_number, int address1, int address2, int depth);

/**
 * @brief Generate the assembly code for a logical OR operation
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the first operand
 * @param address2      the address of the second operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_or(int line_number, int address1, int address2, int depth);


//
// OTHER OPERATIONS
// 

/**
 * @brief Generate the assembly code for a variable
 * 
 * This function generates the assembly code for a variable.
 * It adds the variable to the symbol table.
 * 
 * @param name          the name of the variable
 * @param line_number   the line number in the code
 * @param depth         the depth of the symbol table
 */
void asm_var(char* name, int line_number, int depth);

/**
 * @brief Generate the assembly code for a number entry
 * 
 * This function generates the assembly code for a number entry.
 * Basically, it stores the number in a temporary variable in the
 * symbols table and returns the address of the temporary variable.
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_nb(int line_number, int address1, int depth);

/**
 * @brief Generate the assembly code for a variable assignment
 * 
 * This function generates the assembly code for a variable assignment.
 * It assigns the value of the second operand to the first operand.
 * 
 * @param address1 the address of the first operand
 * @param address2 the address of the second operand
 */
void asm_assign(char* address1, int address2);

/**
 * @brief Generate the assembly code for a negation
 * 
 * This function generates the assembly code for a negation.
 * Basically, it creates a temporary variable in the symbol table
 * with the value 0 and subtracts the operand from it.
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_neg_nb(int line_number, int address1, int depth);

/**
 * @brief Generate the assembly code for a logical NOT operation
 * 
 * @param line_number   the line number in the code
 * @param address1      the address of the operand
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_not(int line_number, int address1, int depth);


/**
 * @brief Generate the assembly code for a print operation
 * 
 * This function generates the assembly code for a print operation.
 * It prints the value of the operand.
 * 
 * @param address1 the address of the value to print
 */
void asm_print(int address1);

//
// FUNCTION CALLS
//

/**
 * @brief Generate the assembly code for a function start
 * 
 * This function generates the assembly code for a function start.
 * It inserts the function name in the instruction table. @todo
 * It inserts the function in the function table.
 * 
 * @param name          the name of the function
 * @param line_number   the line number in the code
 * @param depth         the depth of the symbol table
 */
void asm_function_new_start(char* name, int line_number, int depth);

/**
 * @brief Generate the assembly code for a function end
 * 
 * This function generates the assembly code for a function end.
 * It removes the frame of the function and insert the return
 * 
 * @param nb_params the number of parameters of the function
 */
void asm_function_new_end(int nb_params);

/**
 * @brief Generate the assembly code for a function preparation
 * 
 * This function generates the assembly code for a function preparation.
 * It prepares the stack for the function call.
 * 
 * @param line_number   the line number in the code
 * @param depth         the depth of the symbol table
 * @return int the address of the top of the stack pointer before the stack preparation
 */
int asm_function_prepare_stack(int line_number, int depth);

/**
 * @brief Generate the assembly code for a function call
 * 
 * This function generates the assembly code for a function call.
 * It pushes the arguments on the stack and calls the function.
 * 
 * @param name          the name of the function
 * @param tsp           the top of the stack pointer before the call
 * @param depth         the depth of the symbol table
 * @return int the address of the result
 */
int asm_function_call(char* name, int tsp, int depth);

/**
 * @brief Generate the assembly code for arguments
 * 
 * This function generates the assembly code for the arguments of a function call.
 * It pushes the arguments on the stack.
 * 
 * @param address       the address of the expression
 * @param arg_index       the arguments index
 * @param line_number   the line number in the code
 * @param depth         the depth of the symbol table
 */
void asm_function_call_arg(int address, int arg_index, int line_number, int depth);


/**
 * @brief Generate the assembly code for a function return
 * 
 * This function generates the assembly code for a function return.
 * It copies the return value to the return adress
 * 
 * @param expression_address the address of the expression
 * @param depth the depth of the symbol table
 */
void asm_function_return(int expression_address, int depth);


//
// IF STATEMENTS
//

/**
 * @brief Generate the assembly code for an if statement
 * 
 * This function generates the assembly code for an if statement.
 * It prepares the if statement by inserting the JMPF instruction
 * in the instruction table.
 * 
 * @param expression_address the address of the expression
 * @return int the address of the instruction

 */
int asm_if_prepare(int expression_address);

/**
 * @brief Generate the assembly code for an if statement PATCH
 * 
 * This function generates the assembly code for an if statement PATCH.
 * It patches the jump address of the if statement.
 * @param jmp_address 
 */
void asm_if_patch(int jmp_address);

/**
 * @brief Generate the assembly code for an else statement
 * 
 * This function generates the assembly code for an else statement.
 * It prepares the else statement by inserting a JMP instruction
 * in the instruction table.
 * 
 * @return int the address of the instruction
 */
int asm_else_prepare();

/**
 * @brief Generate the assembly code for an else statement PATCH
 * 
 * This function generates the assembly code for an else statement PATCH.
 * It patches the jump address of the else statement.
 * 
 * @param jmp_address the address of the jump instruction
 */
void asm_else_patch(int jmp_address);

/**
 * @brief Generate the assembly code for an empty else statement
 * 
 * This function generates the assembly code for an empty else statement.
 * It prepares adds a NOP instruction to avoid infinite loops.
 * 
 */
void asm_else_empty();


//
// WHILE STATEMENTS
//

/**
 * @brief Generate the assembly code for a while statement
 * 
 * This function generates the assembly code for a while statement.
 * It prepares the while statement by inserting the JMP instruction
 * in the instruction table.
 * 
 * @param expression_address the address of the expression
 * @return int the address of the instruction
 */
int asm_while_prepare(int expression_address);

/**
 * @brief Generate the assembly code for a while statement PATCH
 * 
 * This function generates the assembly code for a while statement PATCH.
 * It patches the jump address of the while statement.
 * 
 * @param jmp_address the address of the jump instruction
 */
void asm_while_patch(int jmp_address);

#endif // ASM_H 