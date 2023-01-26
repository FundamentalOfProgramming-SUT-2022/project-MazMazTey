#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
#define max_line 1024

void create_undo_file(FILE * file , char * input)
{
    char input_undo[max_input];
    snprintf(input_undo , sizeof(input_undo) , "%s%s" , "undo/" , input);
    FILE * undo_file = fopen(input_undo , "w");
    char a = fgetc(file);
    while (a != EOF)
    {
        fputc(a , undo_file);
        a = fgetc(file);
    }
    fseek(file , 0 , SEEK_SET);
    fclose(undo_file);
}

void undo()
{
    char input[max_input]; // file be tempfile
    FILE * file = fopen(input_file_path(input) , "r");
    FILE * tempfile = fopen("tempfile.txt" , "w");
    fseek(file , 0 , SEEK_SET);
    char b = fgetc(file);
    while (b != EOF)
    {
        fputc(b , tempfile);
        b = fgetc(file);
    }
    fclose(file);
    fclose(tempfile);

    char input_undo[max_input]; // undo file be file
    snprintf(input_undo , sizeof(input_undo) , "%s%s" , "undo/" , input);
    FILE * undo_file = fopen(input_undo , "r");
    fseek(undo_file , 0 , SEEK_SET);
    file = fopen(input , "w");
    char a = fgetc(undo_file);
    while (a != EOF)
    {
        fputc(a , file);
        a = fgetc(undo_file);
    }
    fclose(file);
    fclose(undo_file);

    undo_file = fopen(input_undo , "w"); // temp file be undo
    tempfile = fopen("tempfile.txt" , "r");
    char c = fgetc(tempfile);
    while (c != EOF)
    {
        fputc(c , undo_file);
        c = fgetc(tempfile);
    }
    fclose(undo_file);
    fclose(tempfile);
    remove("tempfile.txt");
}