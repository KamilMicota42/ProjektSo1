#include "synchronize.h"
#include "commons.h"
#include "utility.h"

int isRecursive = 0;

void setAsRecursive(){
    isRecursive = 1;
}

void deleteNotMatching(const char *srcPath, const char *destPath) {
    DIR *destDir = opendir(destPath);
    struct dirent *file;

    while ((file = readdir(destDir))) {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;

        const char *fileInSource = appendToPath(srcPath, file->d_name);
        const char *fileInDest = appendToPath(destPath, file->d_name);
        const int isDestFileDirectory = isDirectory(fileInDest);

        if (!fileExists(fileInSource, isDestFileDirectory)) {
            removeFile(fileInDest, isRecursive);
        }

    }
    closedir(destDir);
}

void copyNotMatching(const char *srcPath, const char *destPath) {
    DIR *srcDir = opendir(srcPath);
    struct dirent *file;

    while ((file = readdir(srcDir))) {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;

        const char *fileInSource = appendToPath(srcPath, file->d_name);
        const char *fileInDest = appendToPath(destPath, file->d_name);
        const int isSourceFileDirectory = isDirectory(fileInSource);

        if (!fileExists(fileInDest, isSourceFileDirectory) ||
            compareDates(getDateOfModify(srcPath), getDateOfModify(destPath)) < 0) {

            copyFile(fileInSource, fileInDest, isRecursive);
        }

        if (isSourceFileDirectory && isRecursive)
            syncDirectories(fileInSource, fileInDest);

    }
    closedir(srcDir);
}

void syncDirectories(const char *sourcePath, const char *destPath) {
    deleteNotMatching(sourcePath, destPath);
    copyNotMatching(sourcePath, destPath);
}
