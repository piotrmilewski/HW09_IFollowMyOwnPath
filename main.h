#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

char *prettyBytes( int, int, char *);
void ls( char *);
int sizeOfFile( char *);
int sizeOfDir( char *);
int main();

#endif
