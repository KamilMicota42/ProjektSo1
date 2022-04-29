#include "file_service.h"
#include "synchronize.h"
#include "utility.h"

int main(int argc, char *argv[]) {
    const char *src = argv[1];
    const char *dest = argv[2];
    if(!isDirectory(src) || !isDirectory(dest)){
    	syslog(LOG_ERR, "Not a directory!");
    	exit(EXIT_FAILURE);
    }
    
    int readSleepTime;
    int sleepTime = 5;
    int copyLimit;

    for (int i = 3; i < argc; ++i) {
        if (strcmp(argv[i], "-r") == 0)
            setAsRecursive();

        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            readSleepTime = atoi(argv[i + 1]);
            if (readSleepTime > 0)
                sleepTime = readSleepTime;
        }

        else if(strcmp(argv[i], "-cl") == 0 && i + 1 < argc){
            copyLimit = atoi(argv[i + 1]);
            if(copyLimit > 0)
                setFileCopyLimit(copyLimit);
        }
    }

    startDaemon();
    while (1) {
        sleep(sleepTime);
        syncDirectories(src, dest);
    }
}
