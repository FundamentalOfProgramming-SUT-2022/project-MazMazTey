#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15

void cat()
{
    char input[max_input];
    FILE * file_to_read = fopen(input_file_path(input), "r");
    if (file_to_read == NULL)
    {
        printf("This File Doesn't exist\n");
        return;
    }
    char a;
    do
    {
        a = fgetc(file_to_read);
        printf("%c", a);
    } while (a != EOF);
    printf("\n");
    fclose(file_to_read);
}