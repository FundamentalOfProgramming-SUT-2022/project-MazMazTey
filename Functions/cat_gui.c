#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void cat_gui(FILE * file , char * input)
{
    echo();
    int line_num = 1;
    move (0 , 0);
    attron(COLOR_PAIR(4));
    printw("01 - ");
    attroff(COLOR_PAIR(4));
    fclose(file);
    file = fopen(input , "r");
    fseek(file , 0 , SEEK_SET);
    char c = fgetc(file);       
    while (c != EOF)
    {
        printw("%c", c);
        if (c == '\n')
        {
            line_num++;
            attron(COLOR_PAIR(4));
            printw("%02d - ", line_num);
            attroff(COLOR_PAIR(4));
        }
        c = fgetc(file);
    }
    printw("\n");
    //fclose(file);
    noecho();
}