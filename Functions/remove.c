#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
//#include "finding_cursor.c"



FILE * remove1()
{
    char input[max_input];
    FILE * file = fopen(input_file_path(input) , "r"); // open main file
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return file;
    }
    FILE * tempfile = fopen("tempfile.txt" , "w+"); // create temp file
    
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