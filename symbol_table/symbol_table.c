/**
 * @file symbol_table.c
 * @author Ronan Bonnet
 * @author Anna Cazeneuve
 * @brief Implementation of the symbol table
 * 
 * @version 0.1
 * @date 2024-04-10 
 */
#include "symbol_table.h"
#include <stdio.h>
#include <string.h>

#define TMP_BASE TABLE_SIZE/2

/**
 * @brief The symbol table
 * 
 * The symbol table is an array of struct_symbol. It
 * is used as a double stack, the first part of the array
 * is used for the symbols and the second part is used for
 * the temporary symbols.
 */
struct_symbol symbol_table[TABLE_SIZE];



/**
 * @brief Index variable for symbols
 * 
 * This variable is used to keep track of the index of the
 * next symbol to insert in the symbol table.
 */
int st_index = 0;

/**
 * @brief Index variable for temporary symbols
 * 
 * This variable is used to keep track of the index of the
 * next temporary symbol to insert in the symbol table.
 */
int st_indextmp = TMP_BASE;


// O(1)
bool st_is_tmp(int address){
    return ( TABLE_SIZE > address && address >= TMP_BASE);
}

int st_get_count() {
    return st_index;
}

int st_pop_depth(int depth) {
    int i = st_index;
    while(i >= 0 && symbol_table[i].depth >= depth) {
        i--;
        st_pop();
    }
    return i;

}

// O(TABLE_SIZE)
int st_insert(char *name, int line_number, int depth) {
    if(st_index >= TMP_BASE) {
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
    symbol_table[st_index].depth = depth;
    st_index++;
    return st_index-1;
}

void st_pop() {
    st_index--;
}

// O(TABLE_SIZE)
int st_insert_tmp(int value, int line_number, int depth) {
    if(st_indextmp >= TABLE_SIZE) {
        printf("Error: Symbol table is full\n");
        return -1;
    }
    snprintf(symbol_table[st_indextmp].name,32, "%d", value);
    // strncpy(symbol_table[st_indextmp].name, sprintf(value), 32);
    symbol_table[st_indextmp].line_number = line_number;
    symbol_table[st_indextmp].depth = depth;
    st_indextmp++;
    return st_indextmp-1;
}

// O(1)
void st_clear() {
    st_index = 0;
    st_indextmp = TMP_BASE;
}

// O(TABLE_SIZE)
int st_search(char *name) {
    // Search for the symbol in the first part of the symbol table
    for (int i = st_index - 1; i >= 0; i--) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// O(1)
void st_pop_tmp() {
    st_indextmp--;
}

// O(1)
void st_update_tmp(int index, int value) {
    snprintf(symbol_table[index].name,32, "%d", value);
}

// O(TABLE_SIZE)
void st_print() {
    printf("\nSymbol table:\n");
    printf("st_index: %d\n", st_index);
    printf("st_indextmp: %d\n", st_indextmp);
    printf("______________________________________________\n");
    printf("| %-3s | %-20s | %-5s | %-5s |\n", "#", "Name", "Line", "Depth");
    printf("|-----|----------------------|-------|-------|\n");
    // Print normal symbols
    for (int i = 0; i < st_index; i++) {
        printf("| %-3d | %-20s | %-5d | %-5d |\n",
            i,
            symbol_table[i].name, 
            symbol_table[i].line_number, 
            symbol_table[i].depth
        );
    }
    printf("|____________________________________________|\n");
    // Print temporary symbols
    for (int i = TMP_BASE + 1; i < st_indextmp; i++) {
        printf("| %-3d | %-20s | %-5d | %-5d |\n", 
            i, 
            symbol_table[i].name, 
            symbol_table[i].line_number, 
            symbol_table[i].depth
        );
    }
    printf("|____________________________________________|\n");
}