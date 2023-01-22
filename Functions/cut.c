#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
//#include "finding_cursor.c"


FILE * cut()
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

    FILE * file = fopen(input , "r");
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return file;
    }
    FILE * clipboard = fopen("clipboard.txt" , "w"); // create clipboard
    FILE * tempfile = fopen("tempfile.txt" , "w+"); // create temp file
    if (z == '"')
    {
        getchar();
    }
    
    char dashpos[10];
    scanf("%s", dashpos);
    if (strcmp(dashpos , "--pos") == 0)
    {
        int line , pos;
        scanf("%d", &line);
        getchar();
        scanf("%d", &pos);
        getchar();
        char dashsize[10];
        scanf("%s", dashsize);
        if (strcmp(dashsize , "-size") == 0)
        {
            getchar();
            int size;
            scanf("%d", &size);
            getchar();
            getchar();
            char a = getchar(); // f or b
            clipb(line , pos , size , a , file , clipboard);
            fill_temp(line , pos , size , a , file , tempfile , input);
            fclose(file);
            return clipboard;
        }
        else
        {
            printf("Invalid Command\n");
            return clipboard;
        }
    }
    else
    {
        printf("Invalid Command\n");
        return clipboard;
    }
}