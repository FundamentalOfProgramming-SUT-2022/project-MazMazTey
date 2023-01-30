// Libraries
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
#define max_line 1024
#include "Functions/input_file_path.c"
#include "Functions/finding_cursor.c"
#include "Functions/clipboard.c"
#include "Functions/fill_temp.c"
#include "Functions/undo.c"
#include "Functions/createfile.c"
#include "Functions/cat.c"
#include "Functions/insert.c"
#include "Functions/copy.c"
#include "Functions/remove.c"
#include "Functions/cut.c"
#include "Functions/paste.c"
#include "Functions/closing_pairs.c"
#include "Functions/text_comparator.c"
#include "Functions/find.c"
#include "Functions/grep.c"
////////////////////////////////////////////

void input_command()
{
    char command[max_command];
    scanf("%s", command);
    if (strcmp(command , "createfile") == 0) // create file
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
    else if (strcmp(command , "cat") == 0) // cat
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
    else if (strcmp(command, "insertstr") == 0) // insert
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
    else if (strcmp(command , "copystr") == 0) // copy
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            copy();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    else if (strcmp(command , "removestr") == 0) // remove
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            remove1();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    else if (strcmp(command , "cutstr") == 0) // cut
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            cut();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    else if (strcmp(command , "pastestr") == 0) // paste
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            paste();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    else if (strcmp(command , "auto-indent") == 0) // closing pairs
    {
        getchar();
        closing_pairs();
    }
    else if (strcmp(command , "compare") == 0) // text comparator
    {
        getchar();
        textcmp();
    }
    else if (strcmp(command , "undo") == 0) // undo
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            undo();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    else if (strcmp(command , "find") == 0) // find
    {
        getchar();
        char dashf[10];
        scanf("%s", dashf);
        if (strcmp(dashf , "--file") == 0)
        {
            getchar();
            find();
        }
        else
        {
            printf("Invalid Command\n");
            return;
        }
    }
    else if (strcmp(command , "grep") == 0) // grep
    {
        getchar();
        grep_type();
    }
    else
        printf("Invalid Command\n");
    
}


////////////////////////////////////////////



int main()
{
    //while (1)
    {
        input_command();
    }
    return 0;
}