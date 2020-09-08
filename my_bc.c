#include "my_bc.h"

Type determine_type(char c)
{
    if (c == '+' || c == '-') return oper_1;
    else if (c == '/' || c == '*' || c == '%') return oper_2;
    else if (c == '(' || c == ')') return parenthesis;
    else if (c >= '0' && c <= '9') return number;
    else return err;
    return err;
}

void add_pair(pair add, array_pair *arr)
{
    arr->size += 1;
    arr->array = (pair *)realloc(arr->array, (arr->size) * sizeof(pair));
    arr->array[arr->size - 1] = add;
}

int calculate(int var_1, char oper, int var_2)
{
    switch(oper)
    {
        case '+':
            return var_1 + var_2;
        case '-':
            return var_1 - var_2;
        case '/':
            return var_1 / var_2;
        case '*':
            return var_1 * var_2;
        case '%':
            return var_1 % var_2;
        default:
            printf("Invalid operator\n");
            break;
    }
    return 0;
}

int postfix_result(array_pair *infix)
{
    int sum;
    array_pair postfix = {.size = 0, .array = (pair *)malloc(sizeof(pair))};
    pair *equation = infix->array;
    int size = infix->size;
    array_pair oper = {.size = 0, .array = (pair *)malloc(sizeof(pair))};
    //
    for (int i = 0; i < size; i++)
    {
        pair eq = equation[i];
        if (eq.type == number)
        {
            add_pair(eq, &postfix);
        }
        if (eq.type == parenthesis && eq.current.parenthesis_id > 0)
        {
            add_pair(eq, &oper);
        }
        if (eq.type == parenthesis && eq.current.parenthesis_id < 0)
        {
            while (oper.size > 0 && oper.array[oper.size - 1].type != parenthesis)
            {
                pair add = oper.array[oper.size - 1];
                oper.size--;
                add_pair(add, &postfix);
            }
            if (oper.size > 0)
            {
                oper.size--;
            }
        }
        if (eq.type == oper_1 || eq.type == oper_2)
        {
            if (oper.size == 0 || oper.array[oper.size - 1].type == parenthesis)
            {
                add_pair(eq, &oper);
            }
            else 
            {
                while (oper.size > 0 && oper.array[oper.size - 1].type != parenthesis && eq.type <= oper.array[oper.size - 1].type)
                {
                    pair add = oper.array[oper.size - 1];
                    oper.size--;
                    add_pair(add, &postfix);
                }
                add_pair(eq, &oper);
            }
        }
    }
    while (oper.size--)
    {
        add_pair(oper.array[oper.size], &postfix);
    }

    // print_pair(&postfix);
    sum = postfix_calculation(&postfix);
    free(postfix.array);
    free(oper.array);
    return sum;
}

int postfix_calculation(array_pair *postfix)
{
    //The maximum stack size for value and operation manipulation
    int stack[postfix->size];
    int stack_size = 0;
    for (int i = 0; i <postfix->size; i++)
    {
        pair eq = postfix->array[i];
        if (eq.type == number)
        {
            stack[stack_size] = eq.current.num;
            stack_size++;
        }
        else
        {
            stack[stack_size - 2] = calculate(stack[stack_size - 2], eq.current.oper, stack[stack_size - 1]);
            stack_size--;
        }
    }

    return stack[0];
}

void print_pair(array_pair *stack)
{
    for (int i = 0; i < stack->size; i++)
    {
        data cur = stack->array[i].current;
        switch (stack->array[i].type)
        {
            case number:
                printf("%d ", cur.num);
                break;
            case oper_1:
                printf("%c ", cur.oper);
                break;
            case oper_2:
                printf("%c ", cur.oper);
                break;
            case parenthesis:
                printf("(%d) ", cur.parenthesis_id);
                break;
            default:
                break;
        }
    }
    printf("\n");
}