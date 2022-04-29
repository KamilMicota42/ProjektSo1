#ifndef SOPROJECT_FILE_SERVICE_H
#define SOPROJECT_FILE_SERVICE_H
#include "commons.h"

extern int fileCopyLimit;

void setFileCopyLimit(int limit);

mode_t getMode(const char *path);

time_t getDateOfModify(const char *path);

int compareDates(const struct timespec dateOne, const struct timespec dateTwo);

void setDateOfModify(const char *path, time_t newDate);

void setMode(const char *path, mode_t newMode);

int isDirectory(const char *path);

int fileExists(const char* path, int shouldBeDirectory);

void aboveLimitCopy(const char* src, const char* dest);

void belowLimitCopy(const char* src, const char* dest);

void copyFile(const char* src, const char* dest, int isRecursive);

off_t getFileSize(const char* path);

void recursiveDeleteDirectory(const char* path);

void removeFile(const char *path, int isRecursive);



#endif //SOPROJECT_FILE_SERVICE_H
