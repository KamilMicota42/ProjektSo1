
#ifndef SOPROJECT_UTILITY_H
#define SOPROJECT_UTILITY_H

char *appendToPath(const char *path, const char *attach);

void signalHandler(int signal);

void startDaemon();

#endif
