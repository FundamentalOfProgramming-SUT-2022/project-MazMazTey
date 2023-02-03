#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_line 1024

void find_str(FILE * , char * , int , int , int);

void attributes(FILE * file , char * string , int size)
{
    char input_attr[max_input];
    scanf("%s", input_attr);
    if (strcmp(input_attr , "-count") == 0)
    {
        find_str(file , string , size , 1 , 0);
    }
    else if (strcmp(input_attr , "-byword") == 0)
    {
        find_str(file , string , size , 2 , 0);
    }
    else if (strcmp(input_attr , "-at") == 0)
    {
        int at_num;
        scanf("%d", &at_num);
        find_str(file , string , size , 3 , at_num);
    }
    else if (strcmp(input_attr , "-all") == 0)
    {
        find_str(file , string , size , 4 , 0);
    }
    else
        printf("This Attribute Doesn't Exist\n");

}

int input_string2(char * string , FILE * file)
{
    int cot = 0 , size = 0 , i = 0;
    char c = getchar();
    if (c == '"')
    {
        cot = 1;
    }
    else
    {
        *(string) = c;
        size++;
        i++;
    }
    for (; ; i++)
    {
        c = getchar();
        if (c == '"' && cot == 1)
        {
            c = getchar();
            if (c == '\n')
            {
                *(string + size + 1) = '\0';
                find_str(file , string , size , 0 , 0);
                break;
            }
            else if (c == ' ')
            {
                attributes(file , string , size);
                break;
            }
            
        }
        else if (((c == ' ') || (c == '\n')) && cot == 0)
        {
            if (c == '\n')
            {
                *(string + size + 1) = '\0';
                find_str(file , string , size , 0 , 0);
                break;
            }
            else if (c == ' ')
            {
                attributes(file , string , size);
                break;
            }
        }
        else if ((int)c == 92) // back slash
        {
            size++;
            c = getchar();
            if (c == '"')
            {
                *(string + i) = '"';
            }
            else if ((int)c == 92) // back slash
            {
                c = getchar();
                *(string + i) = (char)(92);
                *(string + i + 1) = (char)(92);
                size ++;                
            }
            else
            {
                *(string + i) = c;
                size++;
            }
        }
        else
        {
            *(string + i) = c;
            size++;
        }
    }
    *(string + size + 1) = '\0';
    return size;
}

void find_str(FILE * file , char * string , int size_str , int attr , int at_num)
{
    int pos = 0,
    pos_byword = 1,
    count = 0,
    ans_pos = -1,
    ans_pos_byword = 0,
    length;
    fseek(file , 0 , SEEK_END);
    length = ftell(file);
    char c = 'a';
    for (pos = 0; pos < length ; pos++)
    {
        int match = 0;
        fseek(file , pos , SEEK_SET);
        for (int i = 0 ; i < size_str && c != EOF ; i++)
        {
            c = fgetc(file);
            if (c == ' ')
                pos_byword++;
            if (*(string + i) == '*')
            {
                if (*(string + i + 1) == ' ' || *(string + i + 1) == '\0')
                {
                    match++;
                    while (c != ' ' && c != EOF)
                    {
                        c = fgetc(file);
                    }
                    fseek(file , -1 , SEEK_CUR);
                }
                else
                {
                    while (1)
                    {
                        if (c == *(string + i + 1))
                        {
                            i++;
                            match += 2;
                            break;
                        }
                        else if (c == ' ' || c == EOF)
                        {
                            pos_byword++;
                            break;
                        }
                        c = fgetc(file);
                    }
                    
                }
            }
            else if (*(string + i) != '*' && *(string + i) != (char)(92))
            {
                if (*(string + i) == c)
                {
                    match++;
                }
                else
                {
                    break;
                }
            }
            else if (*(string + i) == (char)(92))
            {
                if (c == '*' && *(string + i + 1) == '*') // \*
                {
                    match += 2;
                    i++;
                }
                else if (*(string + i + 1) != '*' && c == (char)(92)) // \c
                    match++;
            }
        }
        if (match == size_str)
        {
            count++;
            if (attr == 0 || attr == 1 || attr == 2)
            {
                if (ans_pos != -1)
                {
                    continue;
                }
                ans_pos = pos;
                ans_pos_byword = pos_byword;
            }
            else if (attr == 3 && count == at_num) // at
            {
                printf("%d", pos);
            }
            else if (attr == 4)
            {
                printf("%d ", pos);
            }
        }
    }
    if (attr == 0) // no attribute
    {
        printf("%d", ans_pos);
    }
    else if (attr == 1) // count attribute
    {
        printf("%d", count);
    }
    else if (attr == 2) // byword
    {
        printf("%d", ans_pos_byword);
    }
    else if (attr == 3 && count < at_num) // at wrong
    {
        printf("-1\n");
    }
}

void find()
{
    char input[max_input];
    FILE * file = fopen(input_file_path(input) , "r");
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return;
    }
    create_undo_file(file , input); // for undo
    char dashstr[max_input];
    scanf("%s", dashstr);
    if (strcmp(dashstr , "--str") == 0)
    {
        getchar();
        char string[max_line];
        int size = input_string2(string , file);
    }
    else
    {
        printf("Invalid Command\n");
        return;
    }
}