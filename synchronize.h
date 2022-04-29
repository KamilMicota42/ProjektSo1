#ifndef SOPROJECT_SYNCHRONIZE_H
#define SOPROJECT_SYNCHRONIZE_H

extern int isRecursive;

void setAsRecursive();

void deleteNotMatching(const char* srcPath, const char* destPath);

void copyNotMatching(const char* srcPath, const char* destPath);

void syncDirectories(const char* sourcePath, const char* destPath);

#endif
