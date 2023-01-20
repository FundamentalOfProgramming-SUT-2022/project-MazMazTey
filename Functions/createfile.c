#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15

void create_file()
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
    for (int i = 0; i < max_input; i++)
    {
        if (input[i] == '/')
        {
            char dirname[i];
            strncpy(dirname , input , i + 1);
            dirname[i + 1] = '\0';
            mkdir(dirname);
        }
    }
    if (access(input, F_OK) == 0)
    {
        printf("File already exists\n");
        return;
    }
    else
    {
        printf("%s\n", input);
        FILE * newfile = fopen(input, "w");
        printf("File Created Successfully\n");
        fclose(newfile);
    }
    
}