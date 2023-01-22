#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
//#include "finding_cursor.c"

FILE * paste()
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

    FILE * file = fopen(input , "r"); // open main file
    FILE * tempfile = fopen("tempfile.txt", "w"); // open temp file
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return file;
    }
    char dashpos[10];
    scanf("%s", dashpos);
    if (strcmp(dashpos , "--pos") == 0)
    {
        int line , pos;
        scanf("%d", &line);
        getchar();
        scanf("%d", &pos);
        FILE * clipboard = fopen("clipboard.txt" , "r"); // open clipboard
        if (clipboard == NULL)
        {
            printf("Nothing Has Been Copied Yet\n");
            return file;
        }
        char before_cursor[1024];
        for (int i = 1; i < line ; i++)
        {
            fgets(before_cursor , 1024 , file);
            fputs(before_cursor , tempfile);
        }
        for (int i = 0; i < pos ; i++)
        {
            char c = fgetc(file);
            fputc(c , tempfile);
        }
        char a = fgetc(clipboard);
        while (a != EOF)
        {
            fputc(a , tempfile);
            a = fgetc(clipboard);
        }
        char b = fgetc(file);
        while (b != EOF)
        {
            fputc(b , tempfile);
            b = fgetc(file);
        }
        fclose(file);
        fclose(tempfile);
        fclose(clipboard);      
        file = fopen(input , "w");
        tempfile = fopen("tempfile.txt", "r");
        fseek(tempfile , 0 , SEEK_SET);
        char c = fgetc(tempfile);
        while (c != EOF)
        {
            fputc(c , file);
            c = fgetc(tempfile);
        }
        fclose(file);
        fclose(tempfile);
        remove("tempfile.txt");
    }
    else
    {
        printf("Invalid Command\n");
        return file;
    }
}