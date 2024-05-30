/**
 * @file symbol_table.h
 * @author Ronan Bonnet
 * @author Anna Cazeneuve
 * @brief This file contains the definition of the symbol table
 * 
 * The symbol table is used to store the symbols of the code such
 * as variables, functions, etc. It is implemented as an array of
 * struct_symbol, which is a structure that contains the name of
 * the symbol, the line number in the code where it is declared and
 * the depth/scope level of the symbol.
 * 
 * @version 0.1
 * @date 2024-04-10
 * 
 * @bug No known bugs
 * @todo Make the size of the table dynamic
 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h> // bool type

#define TABLE_SIZE 255 // Change this value if you need more symbols

/* Macro to define the symbol types for enum and string conversion */
#define SYMBOLTYPES \
    X(TMP) \
    X(VARIABLE) \

/**
 * @brief The type of a symbol
 * 
 * A symbol can be a variable or a function.
 */
typedef enum {
    #define X(symboltype) symboltype,
    SYMBOLTYPES
    #undef X
} symboltype_t;


extern const char* const symboltype_str[];

/**
 * @brief A symbol in the symbol table
 * 
 * A symbol is defined by its name, the line number in the code 
 * where it is declared and the depth/scope level of the symbol.
 * For temporary symbols, the name is the value of the symbol.
 * 
 * @param name the name of the symbol, 32 characters max
 * @param line_number the line number in the code where the 
 *                    symbol is declared
 * @param depth the depth/scope level of the symbol
 */
typedef struct {
    char name[32];
    int line_number;
    symboltype_t symboltype;
    int depth;
} struct_symbol;

/**
 * @brief Check if an address is a temporary address
 * 
 * If the address is greater or equal to the index of 
 * the first temporary address, then it is a temporary address.
 * 
 * @param address the address to check
 * @return true  if the address is a temporary address
 * @return false if the address is not a temporary address
 */
bool st_is_tmp(int address);

int st_get_count();
int st_pop_depth(int depth);


/**
 * @brief Insert a symbol in the symbol table
 * 
 * @param name the name of the symbol
 * @param line_number the line number in the code where the 
 *                    symbol is declared
 * @param depth the depth/scope level of the symbol
 * @return the index of the symbol in the symbol table
 */
int st_insert(char *name, int line_number, int depth);
// void st_set_symboltype(int index, symboltype_t symboltype);

void st_pop();

/**
 * @brief Insert a temporary symbol in the symbol table
 * 
 * Temporary symbols are used to store intermediate values in 
 * the code such as the result of an arithmetic operation.
 * They are stored at the end of the symbol table.
 * 
 * @param value the value of the temporary symbol
 * @param line_number the line number in the code where the 
 *                    symbol is declared
 * @param depth the depth/scope level of the symbol
 * @return the index of the temporary symbol in the symbol table
 */
int st_insert_tmp(int value, int line_number, int depth);

/**
 * @brief Clear the symbol table
 * 
 * It resets the index of the symbol table to 0 and the index 
 * of the temporary symbols to the end of the symbol table.
 */
void st_clear();

/**
 * @brief Search for a symbol in the symbol table
 * 
 * This function searches for a symbol in the symbol table by 
 * name. It does not search for temporary symbols
 * 
 * @param name the name of the symbol
 * @return the index of the symbol in the symbol table
 * @return -1 if the symbol is not found
 */
int st_search(char *name);

int st_get_tmp(int index);

/**
 * @brief Delete a symbol from the symbol table
 * 
 * @param name the name of the symbol
 */
void st_pop_tmp();

/**
 * @brief Update the value of a temporary symbol
 * 
 * This function is used to update the value of a temporary 
 * symbol in the symbol table by changing the name of the symbol
 * to the new value.
 * 
 * @param index the index of the temporary symbol in the 
 *              symbol table
 * @param value the new value of the temporary symbol
 */
void st_update_tmp(int index, int value);


/**
 * @brief Print the symbol table
 * 
 * It prints the symbol table to the standard output. Note that
 * normal symbols are printed first, followed by temporary symbols
 * which are stored at the end of the symbol table.
 * When displayed, normal and temporary symbols are separated by
 * a line of dashes.
 */
void st_print();
#endif