/**
 * @file instructions_table.h
 * @author Ronan Bonnet
 * @brief  This file contains the prototypes for the instructions table
 * 
 * The instructions table is used to store the instructions of the assembly code.
 * It is implemented as an array of struct_instruction, which is a structure that
 * contains the instruction code and the operands of the instruction.
 * 
 * The following instructions are supported:
 * - AFC: Assign a value to a variable
 * - COP: Copy a value from one variable to another
 * - ADD: Addition
 * - SOU: Subtraction
 * - MUL: Multiplication
 * - DIV: Division
 * - EQ: Equal
 * - NEQ: Not equal
 * - LT: Less than
 * - LE: Less or equal
 * - GT: Greater than
 * - GE: Greater or equal
 * - AND: Logical AND
 * - OR: Logical OR
 * - NOT: Logical NOT
 * - JMP: Jump
 * - JMPF: Jump if false
 * - PRINT: Print a value
 * - NOP: No operation
 *  
 * @version 0.1
 * @date 2024-04-10
 * 
 * @bug No known bugs 
 */
#ifndef INSTRUCTIONS_TABLE_H
#define INSTRUCTIONS_TABLE_H

/**
 * @brief Constant for the size of the instructions table
 * 
 * The instructions table is implemented as an array of
 * instructions. This constant defines the size of the array.
 * Larger programs may require a larger table. 
 * 
 * @todo Make the size of the table dynamic
 */
#define INSTRUCTIONS_TABLE_SIZE 1024

/**
 * @brief Structure for an instruction
 * 
 * An instruction is defined by its opcode and its operands.
 * The opcode is an enum that defines the type of the instruction.
 * 
 * @param opcode the opcode(enum) of the instruction
 * @param op1 the first operand of the instruction
 * @param op2 the second operand of the instruction
 * @param op3 the third operand of the instruction
 * 
 */
typedef struct {
    int opcode;
    int op1;
    int op2;
    int op3;
} struct_instruction;

/**
 * @brief Enumeration of all instructions
 * 
 * The instructions are defined as an enumeration. Each instruction
 * has a unique value that is used to identify the instruction in
 * the instructions table.
 * 
 * The name opcode stands for operation code.
 * 
 * @param iAFC Assign a value to a variable
 * @param iCOP Copy a value from one variable to another
 * @param iADD Addition
 * @param iSOU Subtraction
 * @param iMUL Multiplication
 * @param iDIV Division
 * @param iEQ Equal
 * @param iNEQ Not equal
 * @param iLT Less than
 * @param iLE Less or equal
 * @param iGT Greater than
 * @param iGE Greater or equal
 * @param iAND Logical AND
 * @param iOR Logical OR
 * @param iNOT Logical NOT
 * @param iJMP Jump
 * @param iJMPF Jump if false
 * @param iPRINT Print a value
 * @param iNOP No operation
 * @param iRET Return
 * @param iPUSH Push a value on the stack
 * @param iPOP Pop a value from the stack
 * @param iCALL Call a function
 * 
 */
enum opcode { iAFC, iCOP, iADD, iSOU, iMUL, iDIV, iEQ, iNEQ, iLT, iLE,  iGT, iGE, iAND, iOR, iNOT, iJMP, iJMPF, iPRINT, iNOP, iRET, iPUSH, iPOP, iCALL};

/**
 * @brief Get the opcode of an instruction
 * 
 * This function returns the opcode of an instruction as a string.
 * It is used to print the opcode in the assembly code.
 * 
 * @param opc the opcode of the instruction
 * @return char* the opcode as a string (short name)
 */
char* it_get_opcode(enum opcode opc);

/**
 * @brief Insert an instruction in the instructions table
 * 
 * This function inserts an instruction in the instructions table.
 * It takes the opcode of the instruction and its operands as arguments.
 * The function returns the index of the instruction in the table.
 * 
 * If the instruction requires less than 3 operands, set the unused
 * operands to 0.
 * 
 * If the table is full, the function prints an error message and
 * returns -1.
 * 
 * @param opcode the opcode of the instruction
 * @param op1 the first operand of the instruction
 * @param op2 the second operand of the instruction
 * @param op3 the third operand of the instruction
 * @return int the index of the instruction in the table
 */
int it_insert(enum opcode opcode, int op1, int op2, int op3);

/**
 * @brief Get the index of the last instruction in the table
 * 
 * This function returns the index of the last instruction in the
 * instructions table. The index is used to patch the jump instructions.
 * 
 * @return int the index of the last instruction
 */
int it_get_index();

/**
 * @brief Patch the first operand of an instruction
 * 
 * This function patches the first operand of an instruction in the
 * instructions table. It is used to update the address of the target
 * of a jump instruction.
 * 
 * @param index the index of the instruction in the table
 * @param op the new value of the first operand
 */
void it_patch_op1(int index, int op);

/**
 * @brief Patch the second operand of an instruction
 * 
 * This function patches the second operand of an instruction in the
 * instructions table. It is used to update the address of the target
 * of a jump false instruction.
 * 
 * @param index the index of the instruction in the table
 * @param op the new value of the second operand
 */
void it_patch_op2(int index, int op);

/**
 * @brief Print the assembly code to a file
 * 
 * This function prints the assembly code to a file. It is used to
 * generate the final assembly code that can be executed by the
 * machine.
 * 
 * The assembly code is printed in the following format:
 * 
 * opcode operand1 operand2 operand3
 * 
 * If an operand is not used, it is not printed.
 * 
 * @bug The function does not check if the file is opened successfully
 * 
 */
void it_print_asm();

/**
 * @brief Print the instructions table
 * 
 * This function prints the instructions table to the standard output.
 * It is used for debugging purposes.
 * 
 * The instructions are printed in the following format:
 * 
 * 0x00 opcode operand1 operand2 operand3
 * 
 * If an operand is not used, it is not printed.
 * 
 */
void it_pretty_print();


/**
 * @brief Clear the instructions table
 * 
 * This function resets the index of the instructions table to 0.
 * It is used to clear the table before generating the assembly code.
 * 
 */
void it_clear();

#endif // INSTRUCTIONS_TABLE_H