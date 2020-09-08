#include "my_bc.h"

array_pair *parse_string(const char *str)
{
    array_pair *arr = (array_pair *)malloc(sizeof(array_pair));
    arr->size = 0;
    arr->array = (pair *)malloc((arr->size) * sizeof(pair));
    int flag = 0;
    for (int i = 0; i < my_strlen(str); i++)
    {
        if (str[i] == ' ') continue;

        pair cur = {.type = determine_type(str[i])};
        if (cur.type == number)
        {
            int start_num = i;
            int len = 1;
            while (determine_type(str[++i]) == number)
            {
                len++;
            }
            char *num_str = (char *)malloc(len + 1);
            num_str = my_strncpy(num_str, &str[start_num], len);
            int num = my_atoi(num_str);
            cur.current.num = num;
            free(num_str);
            i--;
        }
        else if (cur.type == oper_1 || cur.type == oper_2) cur.current.oper = str[i];
        else if (cur.type == parenthesis && str[i] == '(') cur.current.parenthesis_id = 1;
        else if (cur.type == parenthesis && str[i] == ')') cur.current.parenthesis_id = -1;
        else {flag = 1; break;}
        add_pair(cur, arr);
    }
    
    if (flag)
    {
        printf("Invalid character was written!\nDelete it!\n");
        free(arr->array);
        free(arr);
        return NULL;
    }

    if (check_equation(arr))
    {
        free(arr->array);
        free(arr);
        return NULL;
    }


    return arr;
}

int check_equation(array_pair *arr)
{
    int flag = 0;
    int parenthesis_sum = 0;
    int parenthesis_id = 0;    
    pair old = {.type = err}, cur;
    pair old_operator = {.type = err};
    for (int i = 0; i < arr->size; i++)
    {
        cur = arr->array[i];
        if ((i == 0 || i == arr->size - 1) && (cur.type == oper_1 || cur.type == oper_2))
        {
            printf("Incorrect usage of operator!\n");
            return 1;
        }
        if (cur.type == number && old_operator.type == oper_2 && cur.current.num == 0 && (old_operator.current.oper == '/'|| old_operator.current.oper == '%'))
        {
            printf("Divisor is the zero value!\n");
            return 1;
        }
        if (old.type == cur.type || (old.type == oper_1 && cur.type == oper_2) || (old.type == oper_2 && old.type ==oper_1))
        {
            if (cur.type != parenthesis)
            {
                printf("Two numbers/operators in a row!\n");
                return 1;
            }
            else if (old.current.parenthesis_id == 1 && cur.current.parenthesis_id == -1)
            {
                printf("Noting was writtent between parenthesis\n");
                return 1;
            }
        }
        else
        {
            if ((old.type == number && cur.type == parenthesis && cur.current.parenthesis_id == 1) || (old.type == parenthesis && old.current.parenthesis_id == -1 && cur.type == number))
            {
                printf("There is no operator between two values!\n");
                return 1;
            }
        }
        if (old.type == parenthesis && old.current.parenthesis_id == 1 && (cur.type == oper_1 || cur.type == oper_2))
        {
            printf("Should not contain operator after open parenthesis!\n");
            return 1;
        }
        if ((old.type == oper_1 || old.type == oper_2) && cur.type == parenthesis && cur.current.parenthesis_id == -1)
        {
            printf("Should not contain operator before close parenthesis\n");
            return 1;
        }
        
        if (cur.type == parenthesis)
        {
            parenthesis_sum += cur.current.parenthesis_id;
        }
        if (parenthesis_sum < 0)
        {
            flag = 1;
            break;
        }
        old = cur;
        if (cur.type == oper_1 || cur.type == oper_2)
        {
            old_operator = cur;
        }
    }
    if (flag == 1 || parenthesis_sum > 0)
    {
        printf("Unproper brackets usage!\nCheck your parenthesis!\n");
        return 1;
    }
    return 0;
}