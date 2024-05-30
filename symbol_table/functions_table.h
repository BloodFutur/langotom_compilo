/**
 * @file functions_table.h
 * @author Ronan Bonnet & Anna Cazeneuve
 * @brief This file contains the definition of the functions table
 * @date 2024-05-29
 * 
 * @bug No known bugs
 * @todo Make the size of the table dynamic 
 */
#ifndef FUNCTIONS_TABLE_H
#define FUNCTIONS_TABLE_H

#define FUNCTIONS_TABLE_SIZE 255

/**
 * @brief Structure for a function
 * 
 * A function is defined by its name and its memory address.
 * 
 * @param name the name of the function
 * @param memory_address the instruction address of the function
 * 
 */
typedef struct {
    char name[32];
    int memory_address;
} struct_function;

/**
 * @brief Insert a function in the functions table
 * 
 * This function inserts a function in the functions table.
 * It checks that the table is not full and that the function
 * does not already exists.
 * 
 * @param name the name of the function
 * @param memory_address the instruction address of the function
 * @return int the index of the function in the table
 */
int ft_insert(char *name, int memory_address);

/**
 * @brief Search for a function in the functions table
 * 
 * This function searches for a function in the functions table.
 * It returns the memory address of the function if it is found,
 * or -1 if the function is not found.
 * 
 * @param name the name of the function
 * @return int Memory address of the function, or -1 if not found
 */
int ft_search(char *name);

/**
 * @brief Search for a function in the functions table by function index
 * 
 * This function searches for a function in the functions table by
 * its index.
 * 
 * @param address the memory address of the function
 * @return struct_function the struct_function found, or an empty struct_function.
 */
struct_function ft_search_by_address(int address);

/**
 * @brief Clear the functions table
 * 
 */
void ft_clear();

/**
 * @brief Print the functions table
 * 
 */
void ft_print();

#endif // FUNCTIONS_TABLE_H