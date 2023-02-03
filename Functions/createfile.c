#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_file()
{
    char input[max_input];
    char c = getchar(); // baraye gereftan / ghabl root
    int cot = 0;
    if (c == '"')
    {
        getchar();
        cot = 1;
    }
    char z = getchar();
    int i;
    for (i = 0 ; z != '\n' ; i++)
    {
        *(input + i) = z;
        z = getchar();
        if (z == ' ' && cot == 0)
        {
            i++;
            break;
        }
        if (z == '"' && cot == 1)
        {
            i++;
            break;
        }
    }
    *(input + i) = '\0';
    if (z == '"')
    {
        getchar();
    }
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
        FILE * newfile = fopen(input, "w");
        printf("File Created Successfully\n");
        fclose(newfile);
    }

    /// undo file
    char input_undo[max_input];
    snprintf(input_undo , sizeof(input_undo) , "%s%s" , "undo/" , input);
    for (int i = 0; i < max_input; i++)
    {
        if (input_undo[i] == '/')
        {
            char dirname[i];
            strncpy(dirname , input_undo , i + 1);
            dirname[i + 1] = '\0';
            mkdir(dirname);
        }
    }
    FILE * newfile = fopen(input_undo, "w");
    fclose(newfile);
    
}