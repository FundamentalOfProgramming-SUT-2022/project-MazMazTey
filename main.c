#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
#include "Functions/createfile.c"
#include "Functions/cat.c"
#include "Functions/finding_cursor.c"
#include "Functions/insert.c"
////////////////////////////////////////////

void input_command()
{
    char command[max_command];
    scanf("%s", command);
    if (strcmp(command , "createfile") == 0)
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            create_file();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    if (strcmp(command , "cat") == 0)
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            cat();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    } 
    if (strcmp(command , "insertstr") == 0)
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            insert();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
        
    }
    
    else
        printf("Invalid Command\n");
    
}







////////////////////////////////////////////



int main()
{
    //while (1)
    {
        //input_command();
        FILE * file1 = fopen("root/file.txt" , "r");
        find_cursor(file1 , 5 , 7);
    }
    return 0;
}