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

void copyDirectory(char* src, char* dest, int size){
}

off_t getFileSize(char* path){

}

void removeFile(char *path){

}

void removeDirectory(char *path){

}

void startDaemon(){
    pid_t pid;
    pid = fork();
    if(pid < 0){
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void deleteNotMatching(char* srcPath, char* destPath){
    DIR *destDir = opendir(destPath);
    struct dirent *file;

    while((file = readdir(destDir))){
        char* fileInSource = appendToPath(srcPath, file->d_name);
        char* fileInDest = appendToPath(destPath, file->d_name);

        if(!existsInDirectory(src, file->d_name) && isDirectory(fileInDest)){
            removeDirectory(fileInDest);
        }
        else if(!existsInDirectory(src, file->d_name)){
            removeFile(fileInDest);
        }
        else if(isDirectory(fileInDest)){
            sync(fileInSource, fileInDest);
        }
    }
}

void copyNotMatching(char* srcPath, char* destPath){
    DIR *srcDir = opendir(srcPath);
    struct dirent *file;

    while((file = readdir(srcDir))){
        char* fileInSource = appendToPath(srcPath, file->d_name);
        char* fileInDest = appendToPath(destPath, file->d_name);

        if(!existsInDirectory(dest, file->d_name) && isDirectory(fileInSource)){
            copyDirectory(fileInSource, fileInDest, getFileSize(fileInSource));
            sync(fileInSource, fileInDest);
        }
        else if(!existsInDirectory(dest, file->d_name) || getDateOfModify(srcPath) < getDateOfModify(destPath)){
            copyFile(fileInSource, fileInDest, getFileSize(fileInSource));
        }
        else if(isDirectory(fileInDest)){
            sync(fileInSource, fileInDest);
        }
    }
}


void sync(char* srcPath, char* destPath){

    deleteNotMatching(srcPath, destPath);
    copyNotMatching(srcPath, destPath);

}



void signalHandler(int signal){

}
