#include "file_service.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int isRecursive = 0;

mode_t getMode(const char *path) {
    struct stat mode;

    if (stat(path, &mode) == 0)
        return mode.st_mode;

    else return 0;
}

time_t getDateOfModify(const char *path) {
    struct stat date;

    if (stat(path, &date) == 0)
        return date.st_mtime;

    else return 0;
}

off_t getFileSize(const char *path) {
    struct stat fileSizeBuf;

    if (stat(path, &fileSizeBuf) == 0)
        return fileSizeBuf.st_size;

    else return -1;
}

void setDateOfModify(const char *path, time_t newDate) {
    struct utimbuf newDateBuf;
    newDate.actime = 0;
    newDate.modtime = newDate;

    if (utime(path, &newDateBuf) != 0)
        exit(EXIT_FAILURE);

}

void setMode(const char *path, mode_t newMode) {
    if (chmod(path, newMode) != 0)
        exit(EXIT_FAILURE);
}

int isDirectory(const char *path) {
    struct stat isDirBuf;

    if (stat(path, &isDirBuf) == 0)
        return S_ISDIR(isDirBuf.st_mode) > 0 ? 1 : 0;

    else return 0;

}

int fileExists(const char *path, int shouldBeDirectory) {
    int exists = access(path, F_OK) == 0 ? 1 : 0;

    if (shouldBeDirectory && !isDirectory(path)) {
        exists = 0;
    }

    return exists;

}


void copyFile(const char *src, const char *dest, int isDirectory) {
    if (isDirectory)
        mkdir(dest, getMode(src));

        //todo
        //copy file which is not directory
    else {

    }
}



void removeFile(const char *path) {
    if (isDirectory(path))
        rmdir(path);

    else remove(path);
}

void deleteNotMatching(const char *srcPath, const char *destPath) {
    DIR *destDir = opendir(destPath);
    struct dirent *file;

    while ((file = readdir(destDir))) {
        const char *fileInSource = appendToPath(srcPath, file->d_name);
        const char *fileInDest = appendToPath(destPath, file->d_name);
        const int isDestFileDirectory = isDirectory(fileInDest);

        if (!fileExists(fileInSource, isDestFileDirectory))
            removeFile(fileInDest);
    }
}

void copyNotMatching(const char *srcPath, const char *destPath) {
    DIR *srcDir = opendir(srcPath);
    struct dirent *file;

    while ((file = readdir(srcDir))) {
        const char *fileInSource = appendToPath(srcPath, file->d_name);
        const char *fileInDest = appendToPath(destPath, file->d_name);
        const int isSourceFileDirectory = isDirectory(fileInSource);

        if (!fileExists(fileInDest, isSourceFileDirectory) ||
            getDateOfModify(srcPath) < getDateOfModify(destPath)) {

            copyFile(fileInSource, fileInDest, isDirectory(fileInSource));
        }

        if (isSourceFileDirectory && isRecursive)
            sync(fileInSource, fileInDest);

    }
}

void sync(const char *sourcePath, const char *destPath) {
    //sleep for x seconds

    deleteNotMatching(sourcePath, destPath);
    copyNotMatching(sourcePath, destPath);
}


