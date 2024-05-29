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

#endif // ASM_H 