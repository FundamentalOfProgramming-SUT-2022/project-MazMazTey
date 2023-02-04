#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * paste()
{
    char input[max_input];
    FILE * file = fopen(input_file_path(input) , "r"); // open main file
    FILE * tempfile = fopen("tempfile.txt", "w"); // open temp file
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return file;
    }
    create_undo_file(file , input); // for undo
    char dashpos[10];
    scanf("%s", dashpos);
    if (strcmp(dashpos , "--pos") == 0)
    {
        int line , pos;
        scanf("%d", &line);
        getchar();
        scanf("%d", &pos);
        FILE * clipboard = fopen("clipboard.txt" , "r"); // open clipboard
        if (clipboard == NULL)
        {
            printf("Nothing Has Been Copied Yet\n");
            return file;
        }
        char before_cursor[1024];
        for (int i = 1; i < line ; i++)
        {
            fgets(before_cursor , 1024 , file);
            fputs(before_cursor , tempfile);
        }
        for (int i = 0; i < pos ; i++)
        {
            char c = fgetc(file);
            fputc(c , tempfile);
        }
        char a = fgetc(clipboard);
        while (a != EOF)
        {
            fputc(a , tempfile);
            a = fgetc(clipboard);
        }
        char b = fgetc(file);
        while (b != EOF)
        {
            fputc(b , tempfile);
            b = fgetc(file);
        }
        fclose(file);
        fclose(tempfile);
        fclose(clipboard);      
        file = fopen(input , "w");
        tempfile = fopen("tempfile.txt", "r");
        fseek(tempfile , 0 , SEEK_SET);
        char c = fgetc(tempfile);
        while (c != EOF)
        {
            fputc(c , file);
            c = fgetc(tempfile);
        }
        fclose(file);
        fclose(tempfile);
        remove("tempfile.txt");
    }
    else
    {
        printf("Invalid Command\n");
        return file;
    }
}