#include "file_service.h"
#include <sys/stat.h>

mode_t getMode(char *path){
    struct stat mode;

    if(stat(path, &mode) == 0)
        return mode.st_mode;

    else{
        exit(EXIT_FAILURE);
    }
}

time_t getDateOfModify(char *path){
    struct stat date;

    if(stat(path, &date) == 0)
        return date.st_mtim.tv_sec;

    else{
        exit(EXIT_FAILURE);
    }
}

void setDateOfModify(char *path, time_t newDate){

}

void setMode(char *path, mode_t newMode){

}

int isDirectory(char *path){
    struct stat statbuf;

    if(stat(path, &statbuf) == 0)
        return S_ISDIR(statbuf.st_mode);

    else{
        exit(EXIT_FAILURE);
    }
}

int existsInDirectory(DIR *directory, char *fileName){

}

char *appendToPath(char *path, char *attach){

}

void copyFile(char* src, char* dest, int size){

}

off_t getFileSize(char* path){

}

void removeFile(char *path){

}

void removeDirectory(char *path){

}

void startDaemon(){

}

void sync(DIR* src, DIR* dest){

}

void signalHandler(int signal){

}
