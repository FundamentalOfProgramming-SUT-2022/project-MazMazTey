#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat()
{
    char input[max_input];
    FILE * file_to_read = fopen(input_file_path(input), "r");
    if (file_to_read == NULL)
    {
        printf("This File Doesn't exist\n");
        return;
    }
    create_undo_file(file_to_read , input); // for undo
    char a;
    do
    {
        a = fgetc(file_to_read);
        printf("%c", a);
    } while (a != EOF);
    printf("\n");
    fclose(file_to_read);
}