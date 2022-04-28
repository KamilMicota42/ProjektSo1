#include "synchronize.h"
#include "commons.h"
#include "utility.h"


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

            copyFile(fileInSource, fileInDest, isSourceFileDirectory);
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