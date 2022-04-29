#include "utility.h"
#include"commons.h"

char *appendToPath(const char *path, const char *attach) {
    char *newPath = malloc(strlen(path) + strlen(attach) + 2);

    strcpy(newPath, path);
    strcat(newPath, "/");
    strcat(newPath, attach);

    return newPath;
}

void signalHandler(int sig) {

    if (sig == SIGUSR1) {
        syslog(LOG_INFO, "The daemon was awakened.");
    }
    if (sig == SIGTERM) {
        syslog(LOG_INFO, "The daemon has been stopped");
        exit(EXIT_SUCCESS);
    }

    signal(sig, signalHandler);
}

void startDaemon() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        syslog(LOG_ERR, "Fork failure - in startDaemon");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        syslog(LOG_INFO, "Fork success - parent process exits");
        exit(EXIT_SUCCESS);
    } else {
        signal(SIGUSR1, signalHandler);
        signal(SIGTERM, signalHandler);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
