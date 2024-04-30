/**
 * @file instructions_table.c
 * @author Ronan Bonnet
 * @author Anna Cazeneuve
 * @brief Implementation of the instructions table
 * @version 0.1
 * @date 2024-04-10
 * @bug No known bugs 
 */
#include <stdio.h> // printf
#include "instructions_table.h"

/* Instructions Table */
struct_instruction i_table[INSTRUCTIONS_TABLE_SIZE];

/* Index variable for instructions */
int it_index = 0;

/* Get the opcode as a string */
char* it_get_opcode(enum opcode opc) {
    switch(opc) {
        case iAFC:
            return "AFC";
        case iCOP:
            return "COP";
        case iADD:
            return "ADD";
        case iSOU:
            return "SOU";
        case iMUL:
            return "MUL";
        case iDIV:
            return "DIV";
        case iEQ:
            return "EQU";
        case iNEQ:
            return "NEQ";
        case iLT:   
            return "LT";
        case iLE:
            return "LE";
        case iGT:
            return "GT";
        case iGE:   
            return "GE";
        case iAND:
            return "AND";
        case iOR:
            return "OR";
        case iNOT:
            return "NOT";
        case iJMP:
            return "JMP";
        case iJMPF:
            return "JMF";
        case iPRINT:
            return "PRI";
        case iNOP:
            return "NOP";
        case iRET:
            return "RET";
        case iPUSH:
            return "PUSH";
        case iPOP:
            return "POP";
        case iCALL:
            return "CALL";
    }
}

/* Insert an instruction in the instructions table */
int it_insert(enum opcode opc, int op1, int op2, int op3) {
    if(it_index >= INSTRUCTIONS_TABLE_SIZE) {
        printf("Error: Instructions table is full\n");
        return -1;
    }
    i_table[it_index].opcode = opc;
    i_table[it_index].op1 = op1;
    i_table[it_index].op2 = op2;
    i_table[it_index].op3 = op3;
    it_index++;
    return it_index-1;
}

/* Get the index of the last instruction in the table */
int it_get_index() {
    return it_index;
}

/* Patch the first operand of an instruction: JMP */
void it_patch_op1(int index, int op) {
    i_table[index].op1 = op;
}

/* Patch the second operand of an instruction: JMPF */
void it_patch_op2(int index, int op) {
    i_table[index].op2 = op;
}

/* Print the assembly code into a FILE */
void it_print_asm() {
    FILE *file;

    // File opening
    file = fopen("asm.txt", "w");
    for(int i = 0; i < it_index; i++) {
        enum opcode opc = i_table[i].opcode;
        if(opc == iAFC || opc == iCOP || opc == iJMPF) {
            fprintf(file,"%s %d %d\n", it_get_opcode(i_table[i].opcode), i_table[i].op1, i_table[i].op2);
            continue;
        } else if (opc==iNOT || opc==iJMP || opc==iPRINT || opc==iRET || opc==iPUSH || opc==iPOP || opc==iCALL) {
            fprintf(file,"%s %d\n", it_get_opcode(i_table[i].opcode), i_table[i].op1);
            continue;
        } else if (opc==iNOP) {
            fprintf(file,"%s 0\n", it_get_opcode(i_table[i].opcode));
            continue;
        } else {
            fprintf(file,"%s %d %d %d\n", it_get_opcode(i_table[i].opcode), i_table[i].op1, i_table[i].op2, i_table[i].op3);
            continue;
        }
    }
    fclose(file);
}

/* Print the assembly code into the console */
void it_pretty_print() {

    printf("\nInstructions Table:\n");
    for(int i = 0; i < it_index; i++) {
        enum opcode opc = i_table[i].opcode;
        if(opc == iAFC || opc == iCOP || opc == iJMPF) {
            printf("0x%02x\t %-5s %-4d %-4d\n", i, it_get_opcode(i_table[i].opcode), i_table[i].op1, i_table[i].op2);
            continue;
        } else if (opc==iNOT || opc==iJMP || opc==iPRINT || opc==iRET || opc==iPUSH || opc==iPOP || opc==iCALL) {
            printf("0x%02x\t %-5s %-4d\n", i, it_get_opcode(i_table[i].opcode), i_table[i].op1);
            continue;
        } else if (opc==iNOP) {
            printf("0x%02x\t %-5s\n", i, it_get_opcode(i_table[i].opcode));
            continue;
        } else {
            printf("0x%02x\t %-5s %-4d %-4d %-4d\n", i, it_get_opcode(i_table[i].opcode), i_table[i].op1, i_table[i].op2, i_table[i].op3);
            continue;
        }
    }
    printf("\n");
}

/* Clear the instructions table */
void it_clear() {
    it_index = 0;
}