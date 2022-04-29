#include "file_service.h"
#include "utility.h"

int fileCopyLimit = 5000;

void setFileCopyLimit(int limit){
    fileCopyLimit = limit;
}

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
    newDateBuf.actime = 0;
    newDateBuf.modtime = newDate;

    if (utime(path, &newDateBuf) != 0) {
        syslog(LOG_ERR, "%s %s\n", getCurrentTime(), "Exception - in setDateOfModify");
        exit(EXIT_FAILURE);
    }
}

void setMode(const char *path, mode_t newMode) {
    if (chmod(path, newMode) != 0) {
        syslog(LOG_ERR, "%s %s\n", getCurrentTime(), "Exception - in setMode");
        exit(EXIT_FAILURE);
    }
}

int isDirectory(const char *path) {
    struct stat isDirBuf;

    if (stat(path, &isDirBuf) == 0)
        return S_ISDIR(isDirBuf.st_mode) > 0 ? 1 : 0;

    else return 0;
}

int fileExists(const char *path, int shouldBeDirectory) {
    int exists = access(path, F_OK) == 0 ? 1 : 0;

    if ((shouldBeDirectory && !isDirectory(path)) || (!shouldBeDirectory && isDirectory(path))) {
        exists = 0;
    }

    return exists;
}

void belowLimitCopy(const char *src, const char *dest) {
    int sourceFile = open(src, O_RDONLY);
    int destFile = open(dest, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (sourceFile < 0 || destFile < 0) {
        syslog(LOG_ERR, "%s %s\n", getCurrentTime(), "No such file exception - in belowLimitCopy");
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

void aboveLimitCopy(const char *src, const char *dest) {
    int sourceFile = open(src, O_RDONLY);
    int destFile = open(dest, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (sourceFile < 0 || destFile < 0) {
        syslog(LOG_ERR, "%s %s\n", getCurrentTime(), "No such file exception - in aboveLimitCopy");
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


void recursiveDeleteDirectory(const char *path) {
    DIR *dirBeingDeleted = opendir(path);
    struct dirent *file;

    while ((file = readdir(dirBeingDeleted))) {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;

        const char *currFilePath = appendToPath(path, file->d_name);
        if (isDirectory(currFilePath))
            recursiveDeleteDirectory(currFilePath);

        else remove(currFilePath);
    }

    closedir(dirBeingDeleted);
    rmdir(path);
}

void removeFile(const char *path, int isRecursive) {
    if (isDirectory(path) && isRecursive) {
        recursiveDeleteDirectory(path);
    } else if (!isDirectory(path))
        remove(path);
}



