#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15

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
        //fclose(file);
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
        //fclose(file);
        fclose(clipboard);
        return;
    }
}