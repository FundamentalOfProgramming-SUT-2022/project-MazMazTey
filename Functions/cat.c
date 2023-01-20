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
    char filename[max_input];
    char c = getchar(); // baraye gereftan / ghabl root
    int cot = 0;
    if (c == '"')
    {
        getchar();
        cot = 1;
    }
    char z = getchar();
    int i;
    for (i = 0 ; z != '\n' ; i++)
    {
        *(filename + i) = z;
        z = getchar();
    }
    *(filename + i - cot) = '\0';
    FILE * file_to_read = fopen(filename, "r");
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