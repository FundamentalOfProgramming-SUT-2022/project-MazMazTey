#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
//#include "finding_cursor.c"

void insert()
{
    char c = getchar(); // baraye gereftan / ghabl root
    int cot = 0;
    if (c == '"')
    {
        getchar();
        cot = 1;
    }
    
    char input[max_input];
    char z = getchar();
    int i;
    for (i = 0 ; z != '\n' ; i++)
    {
        *(input + i) = z;
        z = getchar();
    }
    *(input + i - cot) = '\0';
    getchar();
    char dashstr[10];
    scanf("%s", dashstr);
    if (strcmp(dashstr , "--str") == 0)
    {
        
    }
    


    FILE * file_to_write = fopen(input , "r");
    FILE * copy = fopen("copy.txt" , "w");
}