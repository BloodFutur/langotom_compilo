#include "asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "instructions_table.h"

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
      // fprintf(file,"COP %d %d\n", a, address2);
      st_pop_tmp_all();
      st_print();
}


int asm_add(int line_number, int address1, int address2) {
    printf("expression with tADD '%d' + '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iADD, address, address1, address2);
    // fprintf(file,"ADD %d %d %d\n", address, address1, address2);
    return address;
}

int asm_sub(int line_number, int address1, int address2) {
    printf("expression with tSUB '%d' - '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iSOU, address, address1, address2);
    // fprintf(file,"SOU %d %d %d\n", address, address1, address2);
    return address;
}

int asm_mul(int line_number, int address1, int address2) {
    printf("expression with tMUL '%d' * '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iMUL, address, address1, address2);
    // fprintf(file,"MUL %d %d %d\n", address, address1, address2);
    return address;
}

int asm_div(int line_number, int address1, int address2) {
    printf("expression with tDIV '%d' / '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iDIV, address, address1, address2);
    // fprintf(file,"DIV %d %d %d\n", address, address1, address2);
    return address;
}

int asm_eq(int line_number, int address1, int address2) {
    printf("expression with tEQ '%d' == '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iEQ, address, address1, address2);
    // fprintf(file,"EQU %d %d %d\n", address, address1, address2);
    return address;
}

int asm_ne(int line_number, int address1, int address2) {
    printf("expression with tNE '%d' != '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iNEQ, address, address1, address2);
    // fprintf(file,"NEQ %d %d %d\n", address, address1, address2); //nvelle instruction asm (def un code)
    return address;
}

int asm_lt(int line_number, int address1, int address2) {
    printf("expression with tLT '%d' < '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iLT, address, address1, address2);
    // fprintf(file,"INF %d %d %d\n", address, address1, address2);
    return address;
}

int asm_gt(int line_number, int address1, int address2) {
    printf("expression with tGT '%d' > '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iGT, address, address1, address2);
    // fprintf(file,"SUP %d %d %d\n", address, address1, address2);
    return address;
}

int asm_le(int line_number, int address1, int address2) {
    printf("expression with tLE '%d' <= '%d'\n", address1, address2);
    int address_tmp1 = st_insert_tmp(0, line_number);
    it_insert(iLT, address_tmp1, address1, address2);
    // fprintf(file,"INF %d %d %d\n", address_tmp1, address1, address2);
    int address_tmp2 = st_insert_tmp(0, line_number);
    it_insert(iEQ, address_tmp2, address1, address2);
    // fprintf(file,"EQU %d %d %d\n", address_tmp2, address1, address2);
    int address_tmp3 = st_insert_tmp(0, line_number);
    it_insert(iOR, address_tmp3, address_tmp1, address_tmp2);
    // fprintf(file,"OR %d %d %d\n", address_tmp3, address_tmp1, address_tmp2);
    return address_tmp3;
}

int asm_ge(int line_number, int address1, int address2) {
    printf("expression with tGE '%d' >= '%d'\n", address1, address2);
    int address = st_insert_tmp(0, line_number);
    it_insert(iGE, address, address1, address2);
    // fprintf(file,"GEQ %d %d %d\n", address, address1, address2);//nvelle instruction asm (def un code)
    return address;
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

int asm_and(int line_number, int address1, int address2){
    printf("expression with tAND\n");
    int address = st_insert_tmp(0, line_number);
    it_insert(iAND, address, address1, address2);
    // fprintf(file,"AND %d %d %d\n", address, address1, address2);
    return address;
}

int asm_or(int line_number, int address1, int address2){
    printf("expression with tOR\n");
    int address = st_insert_tmp(0, line_number);
    it_insert(iOR, address, address1, address2);
    // fprintf(file,"OR %d %d %d\n", address, address1, address2);
    return address;
}

void asm_print(int address1) {
    printf("instruction with tPRINT and expression\n");
    it_insert(iPRINT,address1, 0,0);
}

/*
void asm_if(int line_number, int address_jump, int condition){
    printf("instruction with tIF and expression\n");
    // fprintf(file, "JMF %d %d\n", address_jump, condition);
}
*/