
#ifndef SOPROJECT_SYNCHRONIZE_H
#define SOPROJECT_SYNCHRONIZE_H

void deleteNotMatching(const char* srcPath, const char* destPath);

void copyNotMatching(const char* srcPath, const char* destPath);

void sync(const char* sourcePath, const char* destPath);

#endif
