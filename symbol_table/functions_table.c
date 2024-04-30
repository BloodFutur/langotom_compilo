#include "functions_table.h"

#include <stdio.h>
#include <string.h>

/**
 * @brief The functions table
 * 
 * The functions table is an array of struct_function. It
 * is used to store the functions of the assembly code.
 */
struct_function functions_table[FUNCTIONS_TABLE_SIZE];

/**
 * @brief Index variable for functions
 * 
 * This variable is used to keep track of the index of the
 * next function to insert in the functions table.
 */
int ft_index = 0;


int ft_insert(char *name, int memory_address) {
    if(ft_index >= FUNCTIONS_TABLE_SIZE) {
        printf("Error: Functions table is full\n");
        return -1;
    }
    if(ft_search(name) != -1) {
        printf("Error: Function %s already exists\n", name);
        return -1;
    }
    strncpy(functions_table[ft_index].name, name, 32);
    functions_table[ft_index].memory_address = memory_address;
    ft_index++;
    return ft_index-1;
}

int ft_search(char *name) {
    for(int i = 0; i < ft_index; i++) {
        if(strcmp(functions_table[i].name, name) == 0) {
            return functions_table[i].memory_address;
        }
    }
    return -1;
}

void ft_clear() {
    ft_index = 0;
}

void ft_print() {
    printf("Functions table:\n");
    printf("----------------\n");
    printf("Index\tName\tMemory Address\n");
    for(int i = 0; i < ft_index; i++) {
        printf("%d\t%s\t%d\n", i, functions_table[i].name, functions_table[i].memory_address);
    }
    printf("----------------\n");
    printf("\n");
   
}