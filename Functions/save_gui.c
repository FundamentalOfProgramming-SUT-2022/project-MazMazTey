#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void save(FILE * file , FILE * tempfile , char * input)
{
    fclose(file);
    fclose(tempfile);
    file = fopen(input , "w");
    tempfile = fopen("./tempfile.txt", "r");
    fseek(tempfile , 0 , SEEK_SET);
    char c = fgetc(tempfile);
    while (c != EOF)
    {
        fputc(c , file);
        c = fgetc(tempfile);
    }
    fclose(file);
    fclose(tempfile);
    remove("./tempfile.txt");
}