#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE * cut()
{
    char input[max_input];
    FILE * file = fopen(input_file_path(input) , "r");
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return file;
    }
    create_undo_file(file , input); // for undo
    FILE * clipboard = fopen("clipboard.txt" , "w"); // create clipboard
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
            clipb(line , pos , size , a , file , clipboard);
            fill_temp(line , pos , size , a , file , tempfile , input);
            fclose(file);
            return clipboard;
        }
        else
        {
            printf("Invalid Command\n");
            return clipboard;
        }
    }
    else
    {
        printf("Invalid Command\n");
        return clipboard;
    }
}