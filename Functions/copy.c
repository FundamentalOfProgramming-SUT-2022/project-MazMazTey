#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
//#include "finding_cursor.c"


FILE * copy()
{
    char input[max_input];
    FILE * file = fopen(input_file_path(input) , "r");
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return file;
    }
    FILE * clipboard = fopen("clipboard.txt" , "w");
    
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
            clipb(line , pos , size , a , file , clipboard);
            fclose(file);
            fclose(clipboard);
            return clipboard;
        }
        else
        {
            printf("Invalid Command\n");
            fclose(file);
            fclose(clipboard);
            return clipboard;
        }
    }
    else
    {
        printf("Invalid Command\n");
        fclose(file);
        fclose(clipboard);
        return clipboard;
    }
}