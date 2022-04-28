#ifndef SOPROJECT_FILE_SERVICE_H
#define SOPROJECT_FILE_SERVICE_H
#include "commons.h"

extern int fileCopyLimit;

mode_t getMode(const char *path);

time_t getDateOfModify(const char *path);

void setDateOfModify(const char *path, time_t newDate);

void setMode(const char *path, mode_t newMode);

int isDirectory(const char *path);

int fileExists(const char* path, int shouldBeDirectory);

void aboveLimitCopy(const char* src, const char* dest);

void belowLimitCopy(const char* src, const char* dest);

void copyFile(const char* src, const char* dest, int isDirectory);

off_t getFileSize(const char* path);

void removeFile(const char *path);



#endif //SOPROJECT_FILE_SERVICE_H
