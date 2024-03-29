#include <stdio.h>
#include "instructions_table.h"

struct_instruction i_table[INSTRUCTIONS_TABLE_SIZE];
int it_index = 0;

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
            return "EQ";
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
    }
}

void it_insert(enum opcode opc, int op1, int op2, int op3) {
    i_table[it_index].opcode = opc;
    i_table[it_index].op1 = op1;
    i_table[it_index].op2 = op2;
    i_table[it_index].op3 = op3;
    it_index++;
}


void it_print_asm() {
    for(int i = 0; i < it_index; i++) {
        enum opcode opc = i_table[i].opcode;
        if(opc == iAFC || opc == iCOP) {
            printf("%s %d %d\n", it_get_opcode(i_table[i].opcode), i_table[i].op1, i_table[i].op2);
            continue;
        } else if (opc==iNOT) {
            printf("%s %d\n", it_get_opcode(i_table[i].opcode), i_table[i].op1);
            continue;
        } else {
            printf("%s %d %d %d\n", it_get_opcode(i_table[i].opcode), i_table[i].op1, i_table[i].op2, i_table[i].op3);
            continue;
        }
    }
}

void it_pretty_print() {
    printf("Instructions Table:\n");
    for(int i = 0; i < it_index; i++) {
        enum opcode opc = i_table[i].opcode;
        if(opc == iAFC || opc == iCOP) {
            printf("0x%02x\t %-5s %-4d %-4d\n", i, it_get_opcode(i_table[i].opcode), i_table[i].op1, i_table[i].op2);
            continue;
        } else if (opc==iNOT) {
            printf("0x%02x\t %-5s %-4d\n", i, it_get_opcode(i_table[i].opcode), i_table[i].op1);
            continue;
        } else {
            printf("0x%02x\t %-5s %-4d %-4d %-4d\n", i, it_get_opcode(i_table[i].opcode), i_table[i].op1, i_table[i].op2, i_table[i].op3);
            continue;
        }
    }
}

void it_clear() {
    it_index = 0;
}

void it_test() {
    it_insert(iAFC, 0, 0, 0);
    it_insert(iCOP, 1, 2, 0);
    it_insert(iADD, 3, 4, 5);
    it_insert(iSOU, 6, 7, 8);
    it_insert(iMUL, 9, 10, 11);
    it_insert(iDIV, 12, 13, 14);
    it_insert(iEQ, 15, 16, 17);
    it_insert(iNEQ, 18, 19, 20);
    it_insert(iLT, 21, 22, 23);
    it_insert(iLE, 24, 25, 26);
    it_insert(iGT, 27, 28, 29);
    it_insert(iGE, 30, 31, 32);
    it_insert(iAND, 33, 34, 35);
    it_insert(iOR, 36, 37, 38);
    it_insert(iNOT, 39, 0, 0);
    it_pretty_print();
}