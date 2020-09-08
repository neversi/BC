#include "my_bc.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Insufficient or over amount of arguments (should be only equation)\n"
            "Write your equation in format:  \"<equation>\"\n");
        return 1;
    }
    array_pair *stack = parse_string(argv[1]);
    if (stack == NULL) return 1;
    printf("Result is: %d\n", postfix_result(stack));
    free(stack->array);
    free(stack);
    return 0;
}