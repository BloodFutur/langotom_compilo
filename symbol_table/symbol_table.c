#include "symbol_table.h"
#include <stdio.h>
#include <string.h>

struct_symbol symbol_table[TABLE_SIZE];

int st_index = 0;
int st_indextmp = TABLE_SIZE - 1;

int st_insert(char *name, int line_number) {
    if(st_index > st_indextmp) {
        printf("Error: Symbol table is full\n");
        return -1;
    }
    if(st_search(name) != -1) {
        printf("Error: Symbol %s already exists\n", name);
        return -1;
    }
    // strcpy(symbol_table[st_index].name,name);
    strncpy(symbol_table[st_index].name, name, 32);

    symbol_table[st_index].line_number = line_number;
    st_index++;
    return st_index-1;
}

int st_insert_tmp(int value, int line_number) {
    if(st_indextmp < st_index) {
        printf("Error: Symbol table is full\n");
        return -1;
    }
    snprintf(symbol_table[st_indextmp].name,32, "%d", value);
    // strncpy(symbol_table[st_indextmp].name, sprintf(value), 32);
    symbol_table[st_indextmp].line_number = line_number;
    st_indextmp--;
    return st_indextmp+1;
}

void st_clear() {
    st_index = 0;
    st_indextmp = TABLE_SIZE - 1;
}

int st_search(char *name) {
    for (int i = 0; i < st_index; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    for (int i = TABLE_SIZE - 1; i > st_indextmp; i--) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}


void st_pop_tmp() {
    st_indextmp++;
}

void st_pop_tmp_all() {
    st_indextmp = TABLE_SIZE - 1;
}

void st_update_tmp(int index, int value) {
    snprintf(symbol_table[index].name,32, "%d", value);
}


void st_print() {
    printf("\nSymbol table:\n");
    printf("_____________________________________\n");
    printf("| %-3s | %-20s | %-5s |\n", "#", "Name", "Line");
    printf("|-----|----------------------|-------|\n");
    for (int i = 0; i < st_index; i++) {
        printf("| %-3d | %-20s | %-5d |\n", i, symbol_table[i].name, symbol_table[i].line_number);
    }
    printf("|____________________________________|\n");
    for (int i = st_indextmp + 1; i < TABLE_SIZE; i++) {
        printf("| %-3d | %-20s | %-5d |\n", i, symbol_table[i].name, symbol_table[i].line_number);
    }
    printf("|____________________________________|\n");
}

void st_test() {
    st_clear();
    int a = st_insert("a", 1);
    st_insert("b", 1);
    st_insert_tmp(2, 1);
    st_insert_tmp(1, 1);

    st_print();


    
    st_pop_tmp();
    st_insert_tmp(3, 1);
    st_print();
    int sa = st_search("a");
    printf("a: %s| l%d\n", symbol_table[sa].name, symbol_table[sa].line_number);

    st_pop_tmp();
    st_print();

    st_clear();
    st_print();

    int sa1;
    sa1 = st_search("a");
    if(sa1 == -1) {
        printf("a: NULL\n");
    } else {
        printf("a: %s| l%d\n", symbol_table[sa1].name, symbol_table[sa1].line_number);
    }

    st_clear();
    st_insert("c", 4);
    st_insert("d", 5);
    st_insert_tmp(69, 5);
    st_insert("c", 4);
    for(int i = 0; i < 110; i++) {
        st_insert_tmp(i, 5);
    }
    st_print();
    st_clear();
}