/*Piotr Milewski
  Systems pd10
  HW09 -- Please follow the DIRections
  2017-11-02*/

//#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

void print_error(int err){
  if (err == -1){
    printf("%s\n", strerror(errno));
    exit(1);
  }
}

char *prettyBytes( int buff, int B, char *retStr){
  if (buff / 1024 >= 1){
    prettyBytes( buff / 1024, ++B, retStr);
  }
  else{
    sprintf( retStr, "%d", buff);
    if (B == 0){
      strcat( retStr, "B");
    }
    else if (B == 1){
      strcat( retStr, "KB");
    }
    else if (B == 2){
      strcat( retStr, "MB");
    }
    else if (B == 3){
      strcat( retStr, "GB");
    }
    else if (B == 4){
      strcat( retStr, "TB");
    }
  }
  return retStr;
}

void ls( char *fileName){
  DIR *dir;
  dir = opendir(fileName);
  struct dirent *entry;

  printf("Directories:\n");
  while (entry = readdir(dir)){
    if (entry->d_type == DT_DIR)
      printf("\t%s\n", entry->d_name);
  }
  closedir(dir);
  
  dir = opendir(fileName);
  printf("Regular files:\n");
  while (entry = readdir(dir)){
    if (entry->d_type == DT_REG)
      printf("\t%s\n", entry->d_name);
  }
  closedir(dir);
}

int sizeOfFile( char *fileName){
  struct stat buff;
  stat(fileName, &buff);
  return buff.st_size;

}

int sizeOfDir( char *dirName){
  int size = 0;
  DIR *dir;
  dir = opendir(dirName);
  struct dirent *entry;

  while (entry = readdir(dir)){
    if (entry->d_type == DT_REG)
      size += sizeOfFile(entry->d_name);
  }
  char retStr[256];
  printf("Total Directory Size: %s\n", prettyBytes(size, 0, retStr));
  closedir(dir);
}

int main(){

  sizeOfDir("./");
  ls("./");
  return 0;
}
