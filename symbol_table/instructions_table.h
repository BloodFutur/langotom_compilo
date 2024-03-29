#ifndef INSTRUCTIONS_TABLE_H
#define INSTRUCTIONS_TABLE_H

#define INSTRUCTIONS_TABLE_SIZE 1024

typedef struct {
    int opcode;
    int op1;
    int op2;
    int op3;
} struct_instruction;

enum opcode { iAFC, iCOP, iADD, iSOU, iMUL, iDIV, iEQ, iNEQ, iLT, iLE,  iGT, iGE, iAND, iOR, iNOT};

char* it_get_opcode(enum opcode opc);

void it_insert(enum opcode opcode, int op1, int op2, int op3);

void it_print_asm();

void it_pretty_print();

void it_clear();

void it_test();


#endif // INSTRUCTIONS_TABLE_H