#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
//#include "finding_cursor.c"


void input_string(FILE * tempfile)
{
    int cot = 0;
    char c = getchar();
    if (c == '"')
    {
        cot = 1;
    }
    else
        fputc(c , tempfile);
    while (1)
    {
        c = getchar();
        if (c == '"' && cot == 1)
            break;
        else if (c == '\n' && cot == 0)
            break;
        else if ((int)c == 92) // back slash
        {
            c = getchar();
            if (c == '"')
                fputc('"', tempfile);
            else if (c == 'n')
                fputc('\n' , tempfile);
            else if ((int)c == 92) // back slash
            {
                c = getchar();
                fputc((char)(92), tempfile);
                fputc(c , tempfile);                
            }
            else
                fputc(c , tempfile);
        }
        else
            fputc(c , tempfile);
    }
}

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
    FILE * tempfile = fopen("tempfile.txt" , "w"); // open temp file
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return;
    }
    if (z == '"')
    {
        getchar();
    }
    int line , pos;
    char dashpos[10];
    scanf("%s", dashpos);
    if (strcmp(dashpos , "--pos") == 0)
    {
        scanf("%d", &line);
        getchar();
        scanf("%d", &pos);
        getchar();
    }
    else
    {
        printf("Invalid Command\n");
        return;
    }
    char dashstr[10];
    char string[max_input];
    scanf("%s", dashstr);
    if (strcmp(dashstr , "--str") == 0)
    {
        getchar();
        char before_cursor[1024]; // insert before string
        for (int i = 1; i < line ; i++)
        {
            fgets(before_cursor , 1024 , file);
            fputs(before_cursor , tempfile);
        }
        for (int i = 0; i < pos ; i++)
        {
            char a = fgetc(file);
            fputc(a , tempfile);
        }
        input_string(tempfile); // insert string
        char b = fgetc(file); // insert after string
        while (b != EOF)
        {
            fputc(b , tempfile);
            b = fgetc(file);
        }
        fclose(file);
        fclose(tempfile);
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
        return;
    }


}