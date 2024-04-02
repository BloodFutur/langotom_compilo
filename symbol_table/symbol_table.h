#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
// Faire une struct pour un symbole
#include <stdbool.h>

#define TABLE_SIZE 255

typedef struct {
    char name[32];
    int line_number;
} struct_symbol;

bool st_is_tmp(int address);

int st_insert(char *name, int line_number);

int st_insert_tmp(int value, int line_number);

void st_clear();

int st_search(char *name);

/**
 * @brief Delete a symbol from the symbol table
 * 
 * @param name  the name of the symbol
 */
void st_pop_tmp();

void st_pop_tmp_all();

void st_update_tmp(int index, int value);


/**
 * @brief Print the symbol table
 * 
 */
void st_print();

void st_test();

#endif