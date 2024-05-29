#ifndef FUNCTIONS_TABLE_H
#define FUNCTIONS_TABLE_H

#define FUNCTIONS_TABLE_SIZE 255

typedef struct {
    char name[32];
    int memory_address;
} struct_function;

int ft_insert(char *name, int memory_address);

/**
 * @brief 
 * 
 * @param name 
 * @return int Memory address of the function
 */
int ft_search(char *name);

struct_function ft_search_by_address(int address);

void ft_clear();

void ft_print();

#endif // FUNCTIONS_TABLE_H