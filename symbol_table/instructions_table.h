#ifndef INSTRUCTIONS_TABLE_H
#define INSTRUCTIONS_TABLE_H

#define INSTRUCTIONS_TABLE_SIZE 1024

typedef struct {
    int opcode;
    int op1;
    int op2;
    int op3;
} struct_instruction;

enum opcode { iAFC, iCOP, iADD, iSOU, iMUL, iDIV, iEQ, iNEQ, iLT, iLE,  iGT, iGE, iAND, iOR, iNOT, iJMP, iJMPF, iPRINT, iNOP};

char* it_get_opcode(enum opcode opc);

int it_insert(enum opcode opcode, int op1, int op2, int op3);

int it_get_index();

void it_patch_op1(int index, int op);
void it_patch_op2(int index, int op);


void it_print_asm();

void it_pretty_print();

void it_clear();

void it_test();


#endif // INSTRUCTIONS_TABLE_H