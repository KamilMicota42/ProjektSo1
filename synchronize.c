#include "synchronize.h"
#include "commons.h"
#include "utility.h"

int isRecursive = 1;

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
            syslog(LOG_INFO, "File removed %s", fileInDest);
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
            getDateOfModify(srcPath) < getDateOfModify(destPath)) {

            copyFile(fileInSource, fileInDest, isSourceFileDirectory);
            syslog(LOG_INFO, "File created %s", fileInDest);
        }

        if (isSourceFileDirectory && isDirectory(fileInDest) && isRecursive)
            syncDirectories(fileInSource, fileInDest);

    }
    closedir(srcDir);
}

void syncDirectories(const char *sourcePath, const char *destPath) {
    //sleep for x seconds
    deleteNotMatching(sourcePath, destPath);
    copyNotMatching(sourcePath, destPath);
}
