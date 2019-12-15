#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int getSizeStr(char *str)
{
    int size = 0;
    while (str[size] != '\0') size++;
    return size;
}

void readFile(char fileName[], char fileTXT_Copy[])
{
    char temp[100];
    FILE* file;
    file = fopen(fileName, "r");
    while (fgets(temp, 100, file) != NULL){
        strcat(fileTXT_Copy, temp);
    }
    fclose(file);
}

int find_index_element(char element, char str[])
{
    int i = 0;
    while (str[i] != element && i < getSizeStr(str)) i++;
    if (i == getSizeStr(str)) i = -1;
    return i;
}

int find_line_element(char element, char str[])
{
    int index = find_index_element(element, str), 
        line = 0;
    while (index != 0){
        if (str[index] == '\n') line += 1;
        index--;
    }
    return line;
}

void copy(char filename_source[], char filename_target[])
{
    FILE *ptrRead, *ptrWrite;
    char c;

    ptrRead = fopen(filename_source, "r");
    ptrWrite = fopen(filename_source, "w");
    while (c != EOF)
    {
        c = getc(ptrRead);
        putc(c, ptrWrite);
    }

    fclose(ptrRead);
    fclose(ptrWrite);
}

int replace_line(char filename[], int delete_line, char txt[])
{
    FILE *ptrRead, *ptrWrite;
    char c;
    int line = 0;

    ptrRead = fopen(filename, "r");
    ptrWrite = fopen("temp.txt", "w");

    while (c != EOF)
    {
        c = getc(ptrRead);
        if (line == delete_line){
            int i = 0;
            while (txt[i] != '\0')
            {
                putc(txt[i], ptrWrite);
                i++;
            }
            putc('\n', ptrWrite);
            while (c != '\n')
            {
                c = getc(ptrRead);
            }
            
        }
        else if (c != EOF)
        {
            putc(c, ptrWrite);
        }
        if (c == '\n'){
            line++;
        }
    }
    
    fclose(ptrRead);
    fclose(ptrWrite);

    int status = 0;
    if (line!=delete_line) status = 1;
    return status;
}