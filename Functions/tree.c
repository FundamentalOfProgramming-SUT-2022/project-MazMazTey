#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_input 50
#define max_command 15
#define max_line 1024
#include <dirent.h>

void listdir(const char *name , int depth , int indent)
{
    DIR *dir;
    struct dirent *entry;
    if (depth > -1)
    {
        if (!(dir = opendir(name)) || indent / 2 >= depth)
            return;
    }
    else if (depth == -1)
    {
        if (!(dir = opendir(name)))
        return;
    }
    else
    {
        printf("Invalid Depth\n");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, depth , indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

void tree()
{
    int depth;
    scanf("%d", &depth);
    listdir("./root", depth , 0);
}