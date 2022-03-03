#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void print(struct dirent** listDirs, int listSize)
{
    for (int i = 0; i < listSize; i++)
        printf("|_%s\n", listDirs[i]->d_name);
    printf("\n");
}

void sort(struct dirent** listDirs, int listSize)
{
    struct stat statbuf1, statbuf2;
    for (int i = 0; i < listSize; i++)
        for (int j = 0; j < listSize; j++)
        {
            lstat(listDirs[i]->d_name, &statbuf1);
            lstat(listDirs[j]->d_name, &statbuf2);
            if (statbuf1.st_mtim.tv_sec > statbuf2.st_mtim.tv_sec)
            {
                struct dirent* tmp = listDirs[j];
                listDirs[j] = listDirs[i];
                listDirs[i] = tmp;
            }

        }
}

int traverse(char* dirName)
{
    int maxListSize = 255;
    static int totalDirs = 0;
    DIR* dir_p = opendir(dirName);
    struct dirent* entry;
    struct stat statbuf;
    struct dirent** listDirs = malloc(sizeof(struct dirent*) * maxListSize);

    if (dir_p == NULL)
    {
        fprintf(stderr, "Can`t open directory %s\n", dirName);
        return -1;
    }
    chdir(dirName);
    int listSize = 0;
    while ((entry = readdir(dir_p)) != NULL)
    {
        if (listSize > maxListSize)
        {
            maxListSize *= 2;
            if (realloc(listDirs, sizeof(struct dirent*) * maxListSize) == NULL)
            {
                fprintf(stderr, "No memory");
                return -2;
            }
        }
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0)
                continue;
            listDirs[listSize++] = entry;
        }
    }
    if (listSize != 0)
    {
        printf("Directory name: %s\n", dirName);
        sort(listDirs, listSize);
        print(listDirs, listSize);

        for (int i = 0; i < listSize; i++)
        {
            traverse(listDirs[i]->d_name);
            totalDirs++;
        }

    }
    chdir("..");
    closedir(dir_p);
    free(listDirs);
    return totalDirs;
}



int main(int argc, char* argv[])
{
    char* topdir = ".";
    if (argc <= 2)
        topdir = argv[1];
    else
    {
        printf("Illegal number of parameters\n");
        return -1;
    }
    int count = traverse(topdir);
    if (count == -1) return -1;
    printf("\nTotal directories: %d\n", count);
    return 0;
}