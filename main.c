
#include "file_service.h"
#include "synchronize.h"
#include "utility.h"

int main(int argc, char* argv[]){
  
	const char* src = argv[1];
	const char* dest = argv[2];
	
	startDaemon();
	while(1){
	syncDirectories(src, dest);
	sleep(10);
	}
}
