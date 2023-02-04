#include <ncurses.h>
#include <string.h>
#define max_input2 1000
#include "Functions/input_file_path.c"
#include "Functions/finding_cursor.c"
#include "Functions/clipboard.c"
#include "Functions/fill_temp.c"
#include "Functions/undo.c"
//#include "Functions/createfile.c"
// test
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
#include "Functions/replace.c"
#include "Functions/tree.c"
/////
#include "Functions/cat_gui.c"
#include "Functions/closing_pairs_gui.c"
#include "Functions/save_gui.c"
char normal(char mode , int height , int width)
{
    mode = 'N';
    noecho();
    mvprintw(height - 2, 0 , "NORMAL");
    refresh();
    return mode;
}

char insert_mode(char mode , int height , int width)
{
    mode = 'I';
    noecho();
    mvprintw(height - 2, 0 , "INSERT");
    echo();
    refresh();
    return mode;
}

char visual(char mode , int height , int width)
{
    mode = 'V';
    noecho();
    mvprintw(height - 2, 0 , "VISUAL");
    refresh();
    return mode;
}

int main()
{
    WINDOW * win = initscr();
    FILE * file = NULL;
    FILE * tempfile = NULL;
    char input_file_name[max_input2];
    cbreak();
    keypad(win , true);
    int height , width;
    int y , x;
    getmaxyx(win , height , width);
    char mode = 'N'; // N = normal V = visual I = insert q = quit
    char input_char; 
    normal(mode , height , 0);
    char c;
    while (1)
    {
        refresh();
        input_char = getch();
        if (input_char == 'q' && mode != 'I') // press q to quit
        {
            break;
        }
        else if ((int)input_char == 27 && mode == 'I') // press esc to go to normal mode
        {
            getyx(win , y , x); // deleting the esc symbol on screen
            mvprintw(y , x - 2 , "  ");
            mode = normal(mode , height , 0);
            move(height - 1 , 0);
        }
        else if (input_char == 'i' && mode == 'N') // press i to go to insert mode and insert
        {
            getyx(win , y , x);
            mode = insert_mode(mode , height , 0);
            move(y , x);
            refresh();
            tempfile = fopen("./tempfile.txt", "w"); // open tempfile (unsaved main file)
            if (file == NULL)
            {
                int line_num = 1;
                mvprintw(0 , 0 , "01 - ");
                char c = getch();
                while ((int)c != 27)
                {
                    fputc(c , tempfile);
                    c = getch();
                    if (c == '\n')
                    {
                        getyx(win , y , x);
                        move (y + 1 , 0);
                        line_num++;
                        printw("%02d - ", line_num);
                    }
                }
                getyx(win , y , x); // deleting the esc symbol on screen
                mvprintw(height - 2 , 8 , "+"); // not saved
                mvprintw(y , x - 2 , "  ");
                noecho();
                mode = normal(mode , height , 0);
                move(height - 1 , 0);
            }
            else
            {
                int y0 , x0;
                getyx(win , y0 , x0);
                move(y0 , x0);
                refresh();
                char before_cursor[1024]; // insert before string
                char insert_input[max_input2];
                noecho();
                c = getch();
                for (int j = 0 ; (int)c != 27 ; j++)
                {
                    getyx(win , y , x);
                    refresh();
                    tempfile = fopen("./tempfile.txt", "w");
                    insert_input[j] = c;    
                    fseek(file , 0 , SEEK_SET);
                    for (int i = 0; i < y0; i++)
                    {
                        fgets(before_cursor , 1024 , file);
                        fputs(before_cursor , tempfile);
                    }
                    for (int i = 0; i < x0 ; i++)
                    {
                        char a = fgetc(file);
                        fputc(a , tempfile);
                    }
                    for (int k = 0; k < j; k++)
                    {
                        fputc(insert_input[k], tempfile);
                    }                   
                    getyx(win , y , x);
                    char b = fgetc(file); // insert after string
                    while (b != EOF)
                    {
                        fputc(b , tempfile);
                        b = fgetc(file);
                    }
                    cat_gui(tempfile , "./tempfile.txt");
                    refresh(); // new
                    fclose(tempfile);
                    if (c == '\n')
                    {
                        move(y + 1 , 5);
                    }
                    else
                        move(y , x + 1);
                    refresh();
                    c = getch();
                }
                getyx(win , y , x); // deleting the esc symbol on screen
                mvprintw(height - 2 ,  8  , "+"); // not saved
                mvprintw(y , x - 2 , "  ");
                mode = normal(mode , height , 0);
                move(height - 1 , 0);
                char b = fgetc(file); // insert after string
                while (b != EOF)
                {
                    fputc(b , tempfile);
                    b = fgetc(file);
                }
                tempfile = fopen("./tempfile.txt", "r");
            }

        }
        else if (input_char == 'v' && mode == 'N') // press v to go to visual mode
        {
            mode = visual(mode , height , 0);
            move(0 , 0);
            refresh();
        }
        else if ((input_char == ':' || input_char == '/') && mode == 'N') // commands
        {
            echo();
            move(height - 1 , 0);
            clrtoeol();
            refresh();
            printw(":");
            char command[max_input2];
            char c = getch();
            int i;
            for (i = 0 ; c != ' ' && c != '\n'; i++)
            {
                command[i] = c;
                c = getch();
            }
            command[i] = '\0';
            if (strcmp(command , "open") == 0) // opening file command
            {
                if (file != NULL)
                {
                    save(file , tempfile , input_file_name);
                }
                char c = getch();
                int i;
                for (i = 0;c != ' ' && c != '\n'; i++)
                {
                    input_file_name[i] = c;
                    c = getch();
                }
                input_file_name[i] = '\0';    
                file = fopen(input_file_name , "r"); // open main file
                if (file == NULL)
                {
                    mvprintw(height - 1 , 0 ,"This File Doesn't Exist\n");
                }
                else
                {
                    mvprintw(height - 2 , 10 , input_file_name);
                    int line_num = 1;
                    move (0 , 0);
                    printw("01 - ");
                    c = fgetc(file);        
                    while (c != EOF)
                    {
                        printw("%c", c);
                        if (c == '\n')
                        {
                            line_num++;
                            printw("%02d - ", line_num);
                        }
                        c = fgetc(file);
                    }
                    printw("\n");
                    //fclose(file);
                    //file = NULL;
                    noecho();
                }
            }
            else if (strcmp(command , "auto-indent") == 0) // auto indent
            {
                if (file == NULL)
                {
                    mvprintw(height - 1 , 0 ,"This File Doesn't Exist\n");
                }
                else
                {
                    file = fopen(input_file_name , "r");
                    tempfile = fopen("./tempfile.txt", "w");
                    closing_pairs_gui(file , tempfile , input_file_name);
                    mvprintw(height - 2 ,  8  , "+"); // not saved
                    //file = NULL;
                }              
            }
            else if (strcmp(command , "saveas") == 0) // save as command
            {
                char c = getch();
                int i;
                for (i = 0;c != ' ' && c != '\n'; i++)
                {
                    input_file_name[i] = c;
                    c = getch();
                }
                input_file_name[i] = '\0';
                //file = fopen(input_file_name , "r"); // open main file
                save(file , tempfile , input_file_name);
                file = NULL;
                mvprintw(height - 2 , 8 , " "); // saved
            }
            else if (strcmp(command , "save") == 0)
            {
                if (file == NULL)
                {
                    mvprintw(height - 1 , 0 , "Enter Name For File");
                }
                else
                {
                    //file = fopen(input_file_name , "r");
                    //tempfile = fopen("./tempfile.txt" , "r");
                    save(file , tempfile , input_file_name);
                    file = NULL;
                }
                mvprintw(height - 2 , 8 , " "); // saved
            }
            else
            {
                move(height - 1 , 0);
                printw("Invalid Command");
            }
        }
        else if (input_char == 'n' && mode == 'V')
        {
            mode = normal(mode , height , 0);
            move(height - 1 , 0);
            refresh();
        }
        else if ((input_char == 'l' || input_char == KEY_RIGHT) && (mode == 'V' || mode == 'N')) // navigation
        {
            getyx(win , y , x);
            move (y , x + 1);
        }
        else if ((input_char == 'h' || input_char == KEY_LEFT) && (mode == 'V' || mode == 'N'))
        {
            getyx(win , y , x);
            move (y , x - 1);
        }
        else if ((input_char == 'k' || input_char == KEY_UP) && (mode == 'V' || mode == 'N'))
        {
            getyx(win , y , x);
            move (y + 1, x);
        }
        else if ((input_char == 'j' || input_char == KEY_DOWN) && (mode == 'V' || mode == 'N'))
        {
            getyx(win , y , x);
            move (y - 1, x);
        }
        else if (input_char == '\n' && (mode == 'I')) // new line 
        {
            getyx(win , y , x);
            move (y + 1 , 0);
        }
    }
    
    endwin();  
    return 0;
}