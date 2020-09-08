#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "my_string.h"


typedef union u_data
{
    int num;
    char oper;
    int parenthesis_id;
}data;

typedef enum e_Type {
    err, // other characters
    number,
    oper_1, // +, -
    oper_2, // *, /, %
    parenthesis
}Type;

typedef struct s_pair
{
    data current;
    Type type;
}pair;

typedef struct s_arr_pair
{
    pair *array;
    int size;
}array_pair;

array_pair *parse_string(const char *);
int check_equation(array_pair *);
Type determine_type(char);
void add_pair(pair, array_pair *);
int calculate(int, char, int);
int postfix_result(array_pair *);
int postfix_calculation(array_pair *);
void print_pair(array_pair *);
#endif //FUNC

