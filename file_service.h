#ifndef SOPROJECT_FILE_SERVICE_H
#define SOPROJECT_FILE_SERVICE_H

mode_t getMode(char *path);

time_t getDateOfModify(char *path);

void setDateOfModify(char *path, time_t newDate);

void setMode(char *path, mode_t newMode);

int isDirectory(char *path);

int existsInDirectory(DIR *directory, char *fileName);

char *appendToPath(char *path, char *attach);

void copyFile(char* src, char* dest, int size);

off_t getFileSize(char* path);

void removeFile(char *path);

void removeDirectory(char *path);

void startDaemon();

void sync(DIR* src, DIR* dest);

void signalHandler(int signal);


#endif //SOPROJECT_FILE_SERVICE_H
