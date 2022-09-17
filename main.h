#ifndef BRAINFUCK_H
#define BRAINFUCK_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
extern unsigned int pointer;
unsigned char *arr;
void com(unsigned char *buff, int size_of_buff);
#endif