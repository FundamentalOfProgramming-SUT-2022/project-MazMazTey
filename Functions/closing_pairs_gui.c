#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void closing_pairs_gui(FILE * file , FILE * tempfile , char * input)
{
    //create_undo_file(file , input); // for undo
    //FILE * tempfile = fopen("./tempfile.txt" , "w");
    int space_from_start = 0;
    int first_nws_char = 0;
    int open_angel_bracket = -1;
    char last_ns_char;
    char c = fgetc(file);
    while (c != EOF)
    {
        if (c == ' ')
        {
            if (first_nws_char == 1)
            {
                int i = 1;
                for (i = 1 ; c == ' '; i++)
                {
                    c = fgetc(file);
                    if (c == EOF)
                    {
                        break;
                    }
                    else if (c != ' ' && c != '{' && c != '}')
                    {
                        for (int j = 0; j < i; j++)
                        {
                            fputc(' ' , tempfile);
                        }
                        if (c == '\n')
                        {
                            first_nws_char = 0;
                        }
                        else
                        {
                            fputc(c, tempfile);
                            last_ns_char = c;
                        }
                        break;
                    }
                    else if (c == '{')
                    {
                        fputc(' ', tempfile);
                        fputc('{', tempfile);
                        fputc('\n', tempfile);
                        space_from_start += 4;
                        first_nws_char = 0;
                        open_angel_bracket = 1;
                        for (int j = 0; j < space_from_start; j++)
                        {
                            fputc(' ', tempfile);
                        }
                        last_ns_char = '{';
                        break;
                    }
                    else if (c == '}')
                    {
                        if (last_ns_char != '}')
                        {
                            fputc('\n', tempfile);
                        }
                        space_from_start -= 4;
                        if (space_from_start < 0)
                        {
                            space_from_start = 0;
                        }
                        first_nws_char = 0;
                        open_angel_bracket = 0;
                        for (int j = 0; j < space_from_start; j++)
                        {
                            fputc(' ', tempfile);
                        }
                        fputc('}', tempfile);
                        fputc('\n', tempfile);
                        last_ns_char = '}';
                        break;
                    }
                }
            }
        }
        else if (c != ' ' && c != '{' && c != '}')
        {
            first_nws_char = 1;
            if (c == '\n')
            {
                first_nws_char = 0;
                if (open_angel_bracket == 1 && last_ns_char != '{')
                {
                    fputc('\n', tempfile);
                    for (int i = 0; i < space_from_start; i++)
                    {
                        fputc(' ', tempfile);
                    }
                    
                }
                
            }
            else
            {
                fputc(c, tempfile);
                last_ns_char = c;
            }
        }
        else if (c == '{')
        {
            if (first_nws_char == 1)
            {
                fputc(' ', tempfile);
            }
            fputc('{', tempfile);
            fputc('\n', tempfile);
            space_from_start += 4;
            first_nws_char = 0;
            open_angel_bracket = 1;
            for (int j = 0; j < space_from_start; j++)
            {
                fputc(' ', tempfile);
            }
            last_ns_char = '{';
        }
        else if (c == '}')
        {
            if (last_ns_char != '}')
            {
                fputc('\n' , tempfile);
            }
            space_from_start -= 4;
            if (space_from_start < 0)
            {
                space_from_start = 0;
            }
            
            first_nws_char = 0;
            open_angel_bracket = 0;
            for (int j = 0; j < space_from_start; j++)
            {
                fputc(' ', tempfile);
            }
            fputc('}', tempfile);
            fputc('\n', tempfile);
            last_ns_char = '}';
        }
        c = fgetc(file);   
    }
    cat_gui(tempfile , "./tempfile.txt");
    //remove("./tempfile.txt");
}