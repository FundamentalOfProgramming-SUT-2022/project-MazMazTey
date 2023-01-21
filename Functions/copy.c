#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
//#include "finding_cursor.c"

void clipb(int line , int pos , int size , char a , FILE * file , FILE * clipboard)
{
    if (a == 'f')
    {
        fseek(file , 0 , SEEK_END);
        int totlength = ftell(file);        
        find_cursor(file, line , pos);
        int length = ftell(file);
        int line_counterf = 0;
        for (int i = 0; i < size; i++)
        {
            char c = fgetc(file);
            if (c == '\n')
            {
                line_counterf++;
            }
        }
        if (totlength - length - line_counterf < size)
        {
            printf("Not Enough Space\n");
            return;
        }
        find_cursor(file , line , pos);
        for (int i = 0; i < size; i++)
        {
            char c = fgetc(file);
            fputc(c , clipboard);
        }
        fclose(file);
        fclose(clipboard);
    }
    else if (a == 'b')
    {
        int line_counterb = 0; // new line handling
        find_cursor(file , line , pos);
        int length = ftell(file);
        for (int i = 0; i < size; i++)
        {
            char c = fgetc(file);
            if (c == '\n')
            {
                line_counterb++;
                fseek(file , -3 , SEEK_CUR);
            }
            else
                fseek(file , -2 , SEEK_CUR);
        }
        if (size + line_counterb > length)
        {
            printf("Not Enough Space\n");
            return;
        }
        find_cursor(file , line , pos);
        fseek(file , -(size + line_counterb) , SEEK_CUR);
        for (int i = 0; i < size; i++)
        {
            char c = fgetc(file);
            fputc(c , clipboard);
        }
        fclose(file);
        fclose(clipboard);
    }
    else
    {
        printf("Not Valid Flag\n");
        return;
    }
}

FILE * copy()
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
    FILE * clipboard = fopen("clipboard.txt" , "w");
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
            fclose(file);
            return clipboard;
        }
        else
        {
            printf("Invalid Command3\n");
            return clipboard;
        }
    }
    else
    {
        printf("Invalid Command4\n");
        return clipboard;
    }
}