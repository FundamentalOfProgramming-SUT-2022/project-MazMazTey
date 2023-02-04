#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    fseek(file , 0 ,SEEK_SET);
    if (a == 'f')
    {
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
        fclose(file);
        fclose(tempfile);
        return;
    }
    
}