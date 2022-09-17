#include "main.h"
#define HEAP_SIZE 30000
unsigned int pointer = 0;
unsigned char *arr = 0;
int main(int ac, char **av)
{
    int file = 0, r = 0;
    unsigned char buff[HEAP_SIZE];

    if (ac < 2 || strcmp(&av[1][strlen(av[1])-3], ".bf") != 0)
    {
        fprintf(stderr, "USAGE: bf <filename>\nFile should end in '.bf'\n");
        return 1;
    }
    if ((arr = malloc(HEAP_SIZE)) == 0)
    {
        fprintf(stderr, "Malloc failed\n");
        return 1;
    }
    memset(arr, 0, HEAP_SIZE);
    file = open(av[1], O_RDONLY);

    memset(buff, 0, sizeof(buff));
    while((r = read(file, buff, sizeof(buff))) > 0)
    {
        com(buff, sizeof(buff));
        memset(buff, 0, sizeof(buff));
    }
    free(arr);
    close(file);
    return 0;
}

void com(unsigned char *buff, int size_of_buff)
{
    int i = 0, j, temp = 0, depth = 0;
    while(buff[i] && i < size_of_buff)
    {
        switch(buff[i])
        {
            case '+':
                if (arr[pointer] < 255)
                    arr[pointer]++;
                else
                    arr[pointer] = 0;
                break;
            case '-':
                if (arr[pointer] > 0)
                    arr[pointer]--;
                else
                    arr[pointer] = 255;
                break;
            case '>':
                if (pointer < HEAP_SIZE)
                    pointer++;
                else
                    pointer = 0;
                break;
            case '<':
                if (pointer > 0)
                    pointer--;
                else
                    pointer = HEAP_SIZE;
                break;
            case '.':
                write(1, &arr[pointer], 1);
                break;
            case ',':
                read(1, &arr[pointer], 1);
                break;
            case '[':
                    j = i + 1;
                    depth++;
                    while (buff[j])
                    {
                        if (buff[j] == ']')
                        {
                            depth--;
                            temp = j;
                        }
                        if (buff[j] == '[')
                            depth++;
                        if (depth == 0)
                            break;
                        j++;
                    }
                    j = temp;
                    while (arr[pointer] != 0)
                        com(&buff[i + 1], j - i);
                    i = j;
                break;
        }
        i++;
    }
}