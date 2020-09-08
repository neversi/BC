#include "my_string.h"

int my_atoi(char* inString) 
{
    int  num = 0; 
    for (int i = 0; inString[i]!= '\0'; i++) 
         num =  num * 10 + inString[i] - '0';
    return  num; 
}

char* my_strcpy(char* param_1, char* param_2)
{
    int a=0;
    int b=0;
    while(param_1[a]!='\0')
    {
        a++;
        }
        while(param_2[b]!='\0')
        {
            b++;
        }
        for(int i=0;i<=b+1;i++)
        {
            param_1[a+i]=param_2[i];
        }

        return param_1;
}

char *my_strncpy(char *param_1, const char *param_2, int bytes)
{
    for (int i = 0; i < bytes || i < my_strlen(param_2); i++)
    {
        param_1[i] = param_2[i];
    }
    param_1[bytes] = 0;
    return param_1;
}

int my_strlen(const char *param_1)
{
    int i=0;
    while(*param_1 != '\0') {
    ++i;
    param_1++;
  }
  return i;
}

int my_strcmp(const char *param_1, const char *param_2)
{
	while(*param_1)
	{
		if (*param_1 != *param_2)
        {
            break;
        }
		param_1++;
		param_2++;
	}

	return *(const unsigned char*) param_1- *(const unsigned char*) param_2;
}

char *my_strcat(char* param_1, const char* param_2)
{
	int i = 0, j = 0;

	for (i = 0; param_1[i] != '\0'; i++);

	for (j = 0; param_2[j] != '\0'; j++)
		param_1[i + j] = param_2[j];
	param_1[i + j] = '\0';

	return param_1;
}
