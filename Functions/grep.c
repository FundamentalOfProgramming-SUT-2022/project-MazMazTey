#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_line 1024

void grep(char * string , int type , int size_str)
{
    char z = getchar();
    int match_count = 0;
    while (z != '\n')
    {
        int already_match = 0;
        char input[max_input]; // input address
        char c = getchar(); // baraye gereftan / ghabl root
        int cot = 0;
        if (c == '"')
        {
            getchar();
            cot = 1;
        }
        z = getchar();
        int i;
        for (i = 0 ; z != '\n' ; i++)
        {
            *(input + i) = z;
            z = getchar();
            if (z == ' ' && cot == 0)
            {
                i++;
                break;
            }
            if (z == '"' && cot == 1)
            {
                i++;
                break;
            }
        }
        *(input + i) = '\0';
        if (z == '"')
        {
            z = getchar();
        }

        FILE * file = fopen(input , "r"); // begin grep
        if (file == NULL)
        {
            printf("This File Doesn't Exist\n");
            return;
        }
        int pos = 0 , length;
        fseek(file , 0 , SEEK_END);
        length = ftell(file);
        char e = 'a';
        for (pos = 0; pos < length && e != EOF ; pos++)
        {
            int match = 0;
            if (e == '\n')
            {
                fseek(file , pos + 2 , SEEK_SET);
            }
            else
                fseek(file , pos , SEEK_SET);
            for (int j = 0 ; j < size_str && e != EOF ; j++)
            {
                e = fgetc(file);
                if (*(string + j) == e)
                {
                    match++;
                }
                else
                    break;
            }
            if (match == size_str)
            {
                match_count++;
                while (e != '\n' && e != EOF)
                {
                    fseek(file, -2 , SEEK_CUR);
                    e = fgetc(file);
                }
                if (e == EOF)
                {
                    fseek(file , 0 , SEEK_SET);
                }
                char input_line[max_line];
                fgets(input_line , max_line , file);
                e = fgetc(file);
                if (type == 0)
                {
                    printf("%s: %s", input , input_line);
                    if (ftell(file) == length)
                    {
                        printf("\n");
                    }
                }
                if (type == 2 && already_match == 0)
                {
                    printf("%s\n", input);
                }
                already_match = 1;
            }
        }
        fclose(file);
    }
    if (type == 1)
    {
        printf("%d\n", match_count);
    }
    
}

void grep_input(int type)
{
    char string[max_line]; // input string pattern
    int size = 0;
    char c = getchar();
    int cot = 0;
    int i;
    if (c == '"')
    {
        i = 0;
        cot = 1;
    }
    else
    {
        *(string) = c;
        size++;
        i = 1;
    }
    char z = getchar();
    if (z == ' ' && cot == 0)
    {
        string[1] = '\0';
    }
    else
    {
        for (; z != '\n' ; i++)
        {
            *(string + i) = z;
            size++;
            z = getchar();
            if (z == ' ' && cot == 0)
            {
                i++;
                break;
            }
            if (z == '"' && cot == 1)
            {
                i++;
                break;
            }
        }
        *(string + i) = '\0';
        if (z == '"')
        {
            getchar();
        }
    }
    char input_command[max_command];
    scanf("%s", input_command);
    if (strcmp(input_command, "--files") == 0)
    {
        grep(string , type , size);
    }
    else
    {
        printf("Invalid Command\n");
        return;
    }

}

void grep_type()
{
    char type[max_command];
    scanf("%s", type);
    if (strcmp(type , "--str") == 0)
    {
        getchar();
        grep_input(0);
    }
    else if (strcmp(type , "-C") == 0)
    {
        getchar();
        scanf("%s", type);
        if (strcmp(type, "--str") == 0)
        {
            getchar();
            grep_input(1);
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    else if (strcmp(type , "-I") == 0)
    {
        getchar();
        scanf("%s", type);
        if (strcmp(type, "--str") == 0)
        {
            getchar();
            grep_input(2);
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    else
    {
        printf("Invalid Command\n");
        return;
    }
}