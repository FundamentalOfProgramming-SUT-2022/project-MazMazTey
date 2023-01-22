#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15

void find_cursor(FILE * file , int line , int pos)
{
    fseek(file , 0 ,SEEK_SET);
    //FILE * copy = fopen("copy.txt" , "w");
    char before_cursor[1024];
    for (int i = 1; i < line ; i++)
    {
        fgets(before_cursor , 1024 , file);
        //fputs(before_cursor , copy);
    }
    for (int i = 0; i < pos ; i++)
    {
        char c = fgetc(file);
        //fputc(c , copy);
    }
    //fclose(copy);
    //fclose(file);
    //remove("copy.txt");
}