#ifndef UTILITY_H
#define UTILITY_H

char *appendToPath(const char *path, const char *attach);

void signalHandler(int signal);

void startDaemon();

#endif //UTILITY_H