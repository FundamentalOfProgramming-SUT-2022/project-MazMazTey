#include <ncurses.h>
#include <string.h>
#define max_input2 1000
#define max_command 1000
#define max_input 1000
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
    attron(COLOR_PAIR(1));
    mode = 'N';
    noecho();
    mvprintw(height - 2, 0 , "NORMAL");
    attroff(COLOR_PAIR(1));
    move(0 , 5);
    refresh();
    return mode;
}

char insert_mode(char mode , int height , int width)
{
    attron(COLOR_PAIR(2));
    mode = 'I';
    noecho();
    mvprintw(height - 2, 0 , "INSERT");
    attroff(COLOR_PAIR(2));
    echo();
    refresh();
    return mode;
}

char visual(char mode , int height , int width)
{
    attron(COLOR_PAIR(3));
    mode = 'V';
    noecho();
    mvprintw(height - 2, 0 , "VISUAL");
    attroff(COLOR_PAIR(3));
    refresh();
    return mode;
}

int main()
{
    WINDOW * win = initscr();
    FILE * file = NULL;
    FILE * tempfile = NULL;
    FILE * clipboard = NULL;
    char input_file_name[max_input2];
    start_color();
    init_pair(1 , COLOR_WHITE , COLOR_CYAN); // normal mode
    init_pair(2 , COLOR_WHITE , COLOR_GREEN); // insert mode
    init_pair(3 , COLOR_WHITE , COLOR_MAGENTA); // visual mode
    init_pair(4 , COLOR_RED , COLOR_BLACK); // line numbers
    cbreak();
    keypad(win , true);
    int height , width;
    int y , x;
    int ycopy , xcopy;
    getmaxyx(win , height , width);
    char mode = 'N'; // N = normal V = visual I = insert q = quit
    char input_char; 
    normal(mode , height , 0);
    char c;
    char flag;
    int size;
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
            move(height - 1 , 0);
            clrtoeol();
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
        else if (input_char == 'p' && mode == 'N') // paste
        {
                tempfile = fopen("./tempfile.txt", "w");
                clipboard = fopen("./clipboard.txt" , "r");
                fseek(clipboard , 0 , SEEK_SET);
                fseek(file , 0 , SEEK_SET);
                getyx(win , y , x);
                char before_cursor[1024];
                for (int i = 1; i < y ; i++)
                {
                    fgets(before_cursor , 1024 , file);
                    fputs(before_cursor , tempfile);
                }
                for (int i = 0; i < x ; i++)
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
                cat_gui(tempfile , "./tempfile.txt");
                refresh();
                mvprintw(height - 2 ,  8  , "+"); // not saved
            
        }
        else if (input_char == 'v' && mode == 'N') // press v to go to visual mode
        {
            if (file == NULL)
            {
                mvprintw(height - 1, 0 ,"Open a File First");
            }
            else
            {
                clipboard = fopen("./clipboard.txt", "w");
                getyx(win , ycopy , xcopy);
                find_cursor(file , ycopy + 1 , xcopy - 5);
                mode = visual(mode , height , 0);
                move(height - 1 , 0);
                clrtoeol();
                move(ycopy , xcopy);
                refresh();
            }
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
                if (file != NULL && tempfile != NULL)
                {
                    save(file , tempfile , input_file_name);
                    mvprintw(height - 2 , 8 , " "); // saved
                    move(height - 1 , 0);
                    file = NULL;
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
                    clear();
                    mvprintw(height - 2 , 10 , input_file_name);
                    mode = normal(mode , height , 0);
                    mvprintw(height - 2 , 10 , input_file_name);
                    int line_num = 1;
                    move (0 , 0);
                    attron(COLOR_PAIR(4));
                    printw("01 - ");
                    attroff(COLOR_PAIR(4));
                    c = fgetc(file);        
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
                    noecho();
                }
                move(0 , 5);
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
                    mvprintw(height - 2 , 10 , input_file_name);
                    mode = normal(mode , height , 0);
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
                save(file , tempfile , input_file_name);
                file = NULL;
                mvprintw(height - 2 , 8 , " "); // saved
                move(height - 1 , 0);
            }
            else if (strcmp(command , "save") == 0)
            {
                if (file == NULL)
                {
                    mvprintw(height - 1 , 0 , "Enter Name For File");
                }
                else if (tempfile != NULL)
                {
                    save(file , tempfile , input_file_name);
                    file = NULL;
                    noecho();
                }
                mvprintw(height - 2 , 8 , " "); // saved
                move(height - 1 , 0);
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
        else if ((input_char == 'l' || input_char == KEY_RIGHT) && mode == 'N') // navigation
        {
            getyx(win , y , x);
            move (y , x + 1);
        }
        else if ((input_char == 'h' || input_char == KEY_LEFT) && mode == 'N')
        {
            getyx(win , y , x);
            move (y , x - 1);
        }
        else if ((input_char == 'k' || input_char == KEY_UP) && mode == 'N')
        {
            getyx(win , y , x);
            move (y + 1, x);
        }
        else if ((input_char == 'j' || input_char == KEY_DOWN) && mode == 'N')
        {
            getyx(win , y , x);
            move (y - 1, x);
        }
        else if ((input_char == 'l' || input_char == KEY_RIGHT) && mode == 'V') // selection
        {
            flag = 'f';
            char a = fgetc(file);
            fputc(a , clipboard);
            size++;
            if (a == '\n')
            {
                getyx(win , y , x);
                move(y + 1 , 5);
            }
            else
            {
                getyx(win , y , x);
                move(y , x + 1);
            }
        }
        else if ((input_char == 'h' || input_char == KEY_LEFT) && mode == 'V')
        {
            flag = 'b';
            getyx(win , y , x);
            move (y , x - 1);
        }
        else if ((input_char == 'k' || input_char == KEY_UP) && mode == 'V')
        {
            getyx(win , y , x);
            move (y + 1, x);
        }
        else if ((input_char == 'j' || input_char == KEY_DOWN) && mode == 'V')
        {
            getyx(win , y , x);
            move (y - 1, x);
        }
        else if (input_char == 'y' && mode == 'V') // copy
        {
            getyx(win , y , x);
            if (flag == 'b')
            {
                chtype character;
                int d = xcopy - x;
                for (int i = 0; i <= d; i++)
                {
                    character = inch();
                    fputc(character , clipboard);
                    move(y , x + 1);
                    getyx(win , y , x);
                }
                
            }
            fclose(clipboard);
            mode = normal(mode , height , 0);
        }
        else if (input_char == 'd' && mode == 'V') // cut/delete
        {
            getyx(win , y , x);
            tempfile = fopen("./tempfile.txt" , "w");
            if (flag == 'f')
            {
                fseek(file , 0 , SEEK_SET);
                char before_cursor[1024];
                for (int i = 0; i < ycopy + 1; i++)
                {
                    fgets(before_cursor , 1024 , file);
                    fputs(before_cursor , tempfile);
                }
                for (int i = 0; i < xcopy - 5 ; i++)
                {
                    char c = fgetc(file);
                    fputc(c , tempfile);
                }
                find_cursor(file , y + 1 , x - 5);
                char a = fgetc(file);
                while (a != EOF)
                {
                    fputc(a , tempfile);
                    a = fgetc(file);
                }
                fseek(tempfile , 0 , SEEK_SET);
                clear();
                cat_gui(tempfile , "./tempfile.txt");
                refresh();
            }
            if (flag == 'b')
            {
                chtype character;
                int d = xcopy - x;
                for (int i = 0; i <= d; i++)
                {
                    character = inch();
                    fputc(character , clipboard);
                    move(y , x + 1);
                    getyx(win , y , x);
                }
                fseek(file , 0 , SEEK_SET);
                char before_cursor[1024];
                for (int i = 0; i < ycopy + 1; i++)
                {
                    fgets(before_cursor , 1024 , file);
                    fputs(before_cursor , tempfile);
                }
                for (int i = 0; i < xcopy - 5 ; i++)
                {
                    char c = fgetc(file);
                    fputc(c , tempfile);
                }
                find_cursor(file , y + 1 , x - 5);
                char a = fgetc(file);
                while (a != EOF)
                {
                    fputc(a , tempfile);
                    a = fgetc(file);
                }
                fseek(tempfile , 0 , SEEK_SET);
                clear();
                cat_gui(tempfile , "./tempfile.txt");
                refresh();
            }
            fclose(clipboard);
            mvprintw(height - 2 , 8 , "+"); // not saved
            mvprintw(height - 2 , 10 , input_file_name);
            mode = normal(mode , height , 0);
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