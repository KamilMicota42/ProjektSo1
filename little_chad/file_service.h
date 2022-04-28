#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

extern int isRecursive;

mode_t getMode(const char *path);

time_t getDateOfModify(const char *path);

void setDateOfModify(const char *path, time_t newDate);

void setMode(const char *path, mode_t newMode);

int isDirectory(const char *path);

int fileExists(const char* path, int shouldBeDirectory);

void copyFile(const char* src, const char* dest, int isDirectory);

off_t getFileSize(const char* path);

void removeFile(const char *path);

void deleteNotMatching(const char* srcPath, const char* destPath);

void copyNotMatching(const char* srcPath, const char* destPath);

void sync(const char* sourcePath, const char* destPath);


#endif //FILE_SERVICE_H
