#include "asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "instructions_table.h"

#define ASSEMBLE_BINARY_OP(instruction, opcode) \
int asm_##instruction(int line_number, int address1, int address2) {\
    printf("expression with t" #instruction " '%d' " #opcode " '%d'\n", address1, address2); \
    if(st_is_tmp(address1)) {st_pop_tmp();} \
    if(st_is_tmp(address2)) {st_pop_tmp();} \
    int address = st_insert_tmp(0, line_number); \
    it_insert(opcode, address, address1, address2); \
    return address; \
}

// ARITHMETIC BINARY OPERATIONS
ASSEMBLE_BINARY_OP(add, iADD)
ASSEMBLE_BINARY_OP(sub, iSOU)
ASSEMBLE_BINARY_OP(mul, iMUL)
ASSEMBLE_BINARY_OP(div, iDIV)

// LOGICAL BINARY OPERATIONS
ASSEMBLE_BINARY_OP(eq, iEQ)
ASSEMBLE_BINARY_OP(ne, iNEQ)
ASSEMBLE_BINARY_OP(lt, iLT)
ASSEMBLE_BINARY_OP(gt, iGT)
ASSEMBLE_BINARY_OP(le, iLE)
ASSEMBLE_BINARY_OP(ge, iGE)
ASSEMBLE_BINARY_OP(and, iAND)
ASSEMBLE_BINARY_OP(or, iOR)


int asm_nb(int line_number, int address1){
    printf("expression with tNB '%d'\n", address1);
    int a = st_insert_tmp(address1, line_number);
    st_print();
    it_insert(iAFC, a, address1, 0);
    // fprintf(file,"AFC %d %d\n", a, address1);
    return a;
}

void asm_assign(char* address1, int address2){
    printf("instruction with tID %s and expression %d\n", address1, address2);
    int a=st_search(address1);
    it_insert(iCOP, a, address2, 0);
    //fprintf(file,"COP %d %d\n", a, address2);
    st_pop_tmp();
    st_print();
}


int asm_neg_nb(int line_number, int address1){
    printf("expression with tSUB\n");
    int address = st_insert_tmp(0, line_number);
    it_insert(iAFC, address, 0 , 0);
    it_insert(iSOU, address, address, address1);
    // fprintf(file,"SOU %d %d %d\n", address, address, address1);
    return address;
}

int asm_not(int line_number, int address1){
    printf("expression with tNOT\n");
    int address = st_insert_tmp(0, line_number);
    it_insert(iNOT, address, 0, 0);
    // fprintf(file,"NOT %d\n", address);
    return address;
}

void asm_print(int address1) {
    printf("instruction with tPRINT and expression\n");
    it_insert(iPRINT,address1, 0,0);
}