#include "file_service.h"
#include "commons.h"
#include "utility.h"

int isRecursive = 0;
int fileCopyLimit = 5000;
git s
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

void aboveLimitCopy(const char *src, const char *dest) {
    int sourceFile = open(src, O_RDONLY);
    int destFile = open(dest, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (sourceFile < 0 || destFile < 0) {
        exit(EXIT_FAILURE);
    }

    char *buffer = (char *) malloc(getFileSize(src));

    int bytesRead;

    while ((bytesRead = read(sourceFile, buffer, sizeof(buffer))) > 0) {
        write(destFile, buffer, (ssize_t) bytesRead);
    }

    close(sourceFile);
    close(destFile);

    setDateOfModify(dest, getDateOfModify(src));
    setMode(dest, getMode(src));
}

void belowLimitCopy(const char *src, const char *dest) {
    int sourceFile = open(src, O_RDONLY);
    int destFile = open(dest, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (sourceFile < 0 || destFile < 0) {
        exit(EXIT_FAILURE);
    }

    int sourceFileSize = getFileSize(src);

    char *mappedSourceFile = (char *) mmap(0, sourceFileSize, PROT_READ, MAP_SHARED | MAP_FILE, sourceFile, 0);

    write(destFile, mappedSourceFile, sourceFileSize);

    close(sourceFile);
    close(destFile);
    munmap(mappedSourceFile, sourceFileSize);

    setDateOfModify(dest, getDateOfModify(src));
    setMode(dest, getMode(src));
}

void copyFile(const char *src, const char *dest, int isDirectory) {
    if (isDirectory)
        mkdir(dest, getMode(src));

    else if (getFileSize(src) <= fileCopyLimit) {
        belowLimitCopy(src, dest);

    } else {
        aboveLimitCopy(src, dest);
    }
}


void removeFile(const char *path) {
    if (isDirectory(path))
        rmdir(path);

    else remove(path);
}



