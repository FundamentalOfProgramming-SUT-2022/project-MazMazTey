#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_line 1024

void textcmp()
{
    char input1[max_input];
    char input2[max_input];
    FILE * file1 = fopen(input_file_path(input1) , "r");
    FILE * file2 = fopen(input_file_path(input2) , "r");
    if (file1 == NULL)
    {
        printf("File 1 Doesn't Exist\n");
        return;
    }
    if (file2 == NULL)
    {
        printf("File 2 Doesn't Exist\n");
        return;
    }
    
    int line_counter = 1;
    char sfile1[max_line];
    char sfile2[max_line];
    int file1_line = 1;
    int file2_line = 1;
    while (fgets(sfile1 , max_line , file1) != NULL)
    {
        file1_line++;
    }
    fseek(file1 , 0 , SEEK_SET);
    while (fgets(sfile2 , max_line , file2) != NULL)
    {
        file2_line++;
    }
    fseek(file2 , 0 , SEEK_SET);
    
    while (fgets(sfile1 , max_line , file1) != NULL && fgets(sfile2 , max_line , file2) != NULL)
    {
        if (strcmp(sfile1 , sfile2) != 0)
        {
            printf("=========== #%d ===========\n", line_counter);
            printf("%s", sfile1);
            printf("%s", sfile2);
        }
        line_counter++;
    }
    if (fgets(sfile1 , max_line , file1) == NULL)
    {
        printf("\nFile 2 is bigger\n");
        printf(">>>>>>>>>> #%d - #%d >>>>>>>>>>\n", line_counter , file2_line);
        fseek(file2 , 0 , SEEK_SET);
        for (int i = 0; i < line_counter - 1; i++)
        {
            fgets(sfile2 , max_line , file2);
        }
        while (fgets(sfile2 , max_line , file2) != NULL)
        {
            printf("%s", sfile2);
        }
    }
    if (fgets(sfile2 , max_line , file2) == NULL)
    {
        printf("\nFile 1 is bigger\n");
        printf(">>>>>>>>>> #%d - #%d >>>>>>>>>>\n", line_counter , file1_line);
        fseek(file1 , 0 , SEEK_SET);
        for (int i = 0; i < line_counter - 1; i++)
        {
            fgets(sfile1 , max_line , file1);
        }
        while (fgets(sfile1 , max_line , file1) != NULL)
        {
            printf("%s", sfile1);
        }
    }
    fclose(file1);
    fclose(file2);
}