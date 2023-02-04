#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_line 1024

void replace(FILE * file , FILE * tempfile , char * string_start , char * string_final , int size_str , int attr , int at_num)
{
    int pos = 0,
    count = 0,
    ans_pos = -1,
    wildcard = 0,
    temptemplength,
    length;
    fseek(file , 0 , SEEK_END);
    length = ftell(file);
    char c = 'a';
    for (pos = 0; pos < length ; pos++)
    {
        int match = 0;
        fseek(file , pos , SEEK_SET);
        FILE * temptempfile = fopen("temptempfile.txt", "w+");
        for (int i = 0 ; i < size_str && c != EOF ; i++)
        {
            c = fgetc(file);
            if (*(string_start + i) == '*')
            {
                wildcard = 1;
                if (*(string_start + i + 1) == ' ' || *(string_start + i + 1) == '\0')
                {
                    match++;
                    while (c != ' ' && c != EOF)
                    {
                        fputc(c , temptempfile);
                        c = fgetc(file);
                    }
                    fseek(file , -1 , SEEK_CUR);
                }
                else
                {
                    while (1)
                    {
                        if (c == *(string_start + i + 1))
                        {
                            fputc(c , temptempfile);
                            i++;
                            match += 2;
                            if (attr == 0 && wildcard == 1 && ans_pos != -1 && match == size_str)
                            {
                                fseek(temptempfile , 0 , SEEK_END);
                                temptemplength = ftell(temptempfile);
                                fseek(temptempfile , 0 , SEEK_SET);
                                char d = fgetc(temptempfile);
                                while (d != EOF)
                                {
                                    fputc(d , tempfile);
                                    d = fgetc(temptempfile);
                                }
                                pos += temptemplength - 1;
                                fclose(temptempfile);                
                            }
                            break;
                        }
                        else if (c == ' ' || c == EOF)
                        {
                            break;
                        }
                        fputc(c , temptempfile);
                        c = fgetc(file);
                    }
                    
                }
            }
            else if (*(string_start + i) != '*' && *(string_start + i) != (char)(92))
            {
                if (*(string_start + i) == c)
                {
                    match++;
                    if ((attr == 0 && match < size_str) || attr == 2)
                    {
                        fputc(c , temptempfile);
                    }
                    if ((attr == 0 && ans_pos != -1 && match == size_str))
                    {
                        fseek(temptempfile , 0 , SEEK_SET);
                        char b = fgetc(temptempfile);
                        while (b != EOF)
                        {
                            fputc(b , tempfile);
                            b = fgetc(temptempfile);
                        }
                        fclose(temptempfile);
                    }
                    else if ((attr == 1 && count != at_num - 1 && match == size_str))
                    {
                        fputc(c , temptempfile);
                        fseek(temptempfile , 0 , SEEK_END);
                        temptemplength = ftell(temptempfile);
                        fseek(temptempfile , 0 , SEEK_SET);
                        char b = fgetc(temptempfile);
                        while (b != EOF)
                        {
                            fputc(b , tempfile);
                            b = fgetc(temptempfile);
                        }
                        pos += temptemplength - 1;  // change
                        fclose(temptempfile);
                    }
                    
                    else if (attr == 1 && match < size_str)
                    {
                        fputc(c , temptempfile);
                    }
                }
                else
                {
                    if (match == 0)
                    {
                        fputc(c , tempfile);    
                    }
                    else
                    {
                         ////////////////////////////////
                        fseek(temptempfile , 0 , SEEK_END);
                        temptemplength = ftell(temptempfile);
                        fseek(temptempfile , 0 , SEEK_SET);
                        char a = fgetc(temptempfile);
                        while (a != EOF)
                        {
                            fputc(a , tempfile);
                            a = fgetc(temptempfile);
                        }
                        pos += temptemplength - 1;
                        fclose(temptempfile); ///////////////////////////
                    }
                    break;
                }
            }
            else if (*(string_start + i) == (char)(92))
            {
                if (c == '*' && *(string_start + i + 1) == '*') // \*
                {
                    match += 2;
                    i++;
                }
                else if (*(string_start + i + 1) != '*' && c == (char)(92)) // \c
                    match++;
                else
                    fputc(c , tempfile);
            }
            //printf("ans_pos = %d\n", ans_pos);
        }
        if (match == size_str)
        {
            count++;
            if (attr == 0)
            {
                if (ans_pos != -1)
                {
                    /*for (int i = 0; *(string_start + i) != '\0'; i++)
                    {
                        fputc(*(string_start + i) , tempfile);
                    }*/
                    pos += size_str - 1;
                    continue;
                }
                
                for (int i = 0; *(string_final + i) != '\0'; i++)
                {
                    fputc(*(string_final + i) , tempfile);
                }
                pos += size_str - 1;
                ans_pos = pos;
            }
            else if (attr == 1 && count == at_num) // at
            {
                for (int i = 0; *(string_final + i) != '\0'; i++)
                {
                    fputc(*(string_final + i) , tempfile);
                }
                pos += size_str - 1;
            }
            else if (attr == 2) // all
            {
                for (int i = 0; *(string_final + i) != '\0'; i++)
                {
                    fputc(*(string_final + i) , tempfile);
                }
                pos += size_str - 1;
            }
        }
    }
    if (attr == 1 && count < at_num) // at wrong
    {
        printf("-1\n");
    }
    
    fclose(tempfile);
    fclose(file);
    remove("temptempfile.txt");
}

void attributes2(FILE * file , FILE * tempfile , char * string_start , char * string_final , int size)
{
    char input_attr[max_input];
    scanf("%s", input_attr);
    if (strcmp(input_attr , "-at") == 0)
    {
        int at_num;
        scanf("%d", &at_num);
        replace(file , tempfile , string_start , string_final , size , 1 , at_num);
    }
    else if (strcmp(input_attr , "-all") == 0)
    {
        replace(file, tempfile , string_start , string_final , size , 2 , 0);
    }
    else
        printf("This Attribute Doesn't Exist\n");   
}

int input_string4(FILE * file , FILE * tempfile , char * string_start , char * string_final)
{
    int cot = 0 , size = 0 , i = 0;
    char c = getchar();
    if (c == '"')
    {
        cot = 1;
    }
    else
    {
        *(string_start) = c;
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
                *(string_start + size + 1) = '\0';
                replace(file , tempfile , string_start , string_final , size , 0 , 0);
                break;
            }
            else if (c == ' ')
            {
                attributes2(file, tempfile , string_start , string_final , size);
                break;
            }
            
        }
        else if (((c == ' ') || (c == '\n')) && cot == 0)
        {
            if (c == '\n')
            {
                *(string_start + size + 1) = '\0';
                replace(file , tempfile , string_start , string_final , size , 0 , 0);
                break;
            }
            else if (c == ' ')
            {
                attributes2(file , tempfile , string_start , string_final , size);
                break;
            }
        }
        else if ((int)c == 92) // back slash
        {
            size++;
            c = getchar();
            if (c == '"')
            {
                *(string_start + i) = '"';
            }
            else if ((int)c == 92) // back slash
            {
                c = getchar();
                *(string_start + i) = (char)(92);
                *(string_start + i + 1) = (char)(92);
                size ++;                
            }
            else
            {
                *(string_start + i) = c;
                size++;
            }
        }
        else
        {
            *(string_start + i) = c;
            size++;
        }
    }
    *(string_start + size) = '\0';
    return size;
}

int input_string3(char * string)
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
        if ((c == '"' && cot == 1)) // change
        {
            c = getchar(); 
            break;          
        }
        if (c == ' ' && cot == 0)
        {
            break;
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
    *(string + size) = '\0';
    return size;
}

void replace_input() // aval stringi ke gharare biad baad stringi ke gharare replace she
{
    char input[max_input];
    FILE * file = fopen(input_file_path(input) , "r");
    if (file == NULL)
    {
        printf("This File Doesn't exist\n");
        return;
    }
    FILE * tempfile = fopen("tempfile.txt", "w");
    create_undo_file(file , input); // for undo
    char dashstr1[max_input];
    char dashstr2[max_input];
    char string_start[max_line];
    char string_final[max_line];
    scanf("%s", dashstr1);
    if (strcmp(dashstr1 , "--str1") == 0)
    {
        getchar();
        input_string3(string_final);
    }
    else
    {
        printf("Invalid Command\n");
        return;
    }
    scanf("%s", dashstr2);
    if (strcmp(dashstr2 , "--str2") == 0)
    {
        getchar();
        int size = input_string4(file , tempfile , string_start , string_final);
    }    
    else
    {
        printf("Invalid Command\n");
        return;
    }
    file = fopen(input , "w"); // moving data to main file
    tempfile = fopen("tempfile.txt", "r");
    fseek(file , 0 , SEEK_SET);
    char t = fgetc(tempfile);
    while (t != EOF)
    {
        fputc(t , file);
        t = fgetc(tempfile);
    }
    fclose(file);
    fclose(tempfile);
    remove("tempfile.txt");
}