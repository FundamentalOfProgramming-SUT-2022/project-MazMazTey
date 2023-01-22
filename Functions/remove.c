#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
//#include "finding_cursor.c"

void transfer_data_to_file(char * input , FILE * file , FILE * tempfile)
{
    file = fopen(input , "w");
    tempfile = fopen("tempfile.txt", "r");
    fseek(tempfile , 0 , SEEK_SET);
    char b = fgetc(tempfile);
    while (b != EOF)
    {
        fputc(b , file);
        b = fgetc(tempfile);
    }
    fclose(file);
    fclose(tempfile);
    remove("tempfile.txt");
}

void fill_temp(int line , int pos , int size , char a , FILE * file , FILE * tempfile , char * input)
{
    if (a == 'f')
    {
        fseek(file , 0 ,SEEK_SET);
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
        for (int i = 0; i < size || feof(stdin); i++)
        {
            fgetc(file);
        }
        char b = fgetc(file);
        while (b != EOF)
        {
            fputc(b , tempfile);
            b = fgetc(file);
        }
        fclose(file);
        fclose(tempfile);
        transfer_data_to_file(input ,file , tempfile);
    }
    else if (a == 'b')
    {
        int length_end;
        find_cursor(file , line , pos);
        length_end = ftell(file);
        int line_counterb = 0 , line_counters = 0;
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
        fseek(file , 0 , SEEK_SET);
        for (int i = 0; i < length_end - size ; i++)
        {
            char c = fgetc(file);
            if (c == '\n')
            {
                line_counters++;
                i--;
            }
            
        }
        fseek(file , 0 , SEEK_SET);
        if (length_end - size - line_counterb - line_counters > 0)
        {
            for (int i = 0; i < length_end - size - line_counterb - line_counters + 1; i++)
            {
                char c = fgetc(file);
                fputc(c , tempfile);
            }
            for (int i = 0; i < size; i++)
            {
                fgetc(file);
            }
        }
        else
        {
            find_cursor(file , line , pos);
            char d = fgetc(file);
            while (d != EOF)
            {
                fputc(d , tempfile);
                d = fgetc(file);
            }
            fclose(file);
            fclose(tempfile);
        }
        find_cursor(file , line , pos);
        char b = fgetc(file);
        while (b != EOF)
        {
            fputc(b , tempfile);
            b = fgetc(file);
        }
        fclose(file);
        fclose(tempfile);
        transfer_data_to_file(input , file , tempfile);        
    }
    else
    {
        printf("Not Valid Flag\n");
        return;
    }
    
}


FILE * remove1()
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
    if (file == NULL)
    {
        printf("This File Doesn't exist111\n");
        return file;
    }
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
            fill_temp(line , pos , size , a , file , tempfile , input);
            fclose(file);
            return file;
        }
        else
        {
            printf("Invalid Command\n");
            return file;
        }
    }
    else
    {
        printf("Invalid Command\n");
        return file;
    }
}