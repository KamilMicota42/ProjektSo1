#include "file_service.h"
#include <sys/stat.h>

mode_t getMode(char *path){
    struct stat mode;

    if(stat(path, &mode) == 0)
        return mode.st_mode;

    else{
        exit(EXIT_FAILURE);
    }
}

time_t getDateOfModify(char *path){
    struct stat date;

    if(stat(path, &date) == 0)
        return date.st_mtim.tv_sec;

    else{
        exit(EXIT_FAILURE);
    }
}

void setDateOfModify(char *path, time_t newDate){

}

void setMode(char *path, mode_t newMode){

}

int isDirectory(char *path){
    struct stat statbuf;

    if(stat(path, &statbuf) == 0)
        return S_ISDIR(statbuf.st_mode);

    else{
        exit(EXIT_FAILURE);
    }
}

int existsInDirectory(DIR *directory, char *fileName){

}

char *appendToPath(char *path, char *attach){

}

void copyFile(char* src, char* dest, int size){

}

off_t getFileSize(char* path){

}

void removeFile(char *path){

}

void removeDirectory(char *path){

}

void startDaemon(){

}

void sync(DIR* src, DIR* dest, int recurence){
    DIR *d = opendir(dest);
    struct dirent *directory;
    if((isDirectory(src) == 1 && isDirectory(dest) == 1) || recurence){//isDir zwraca 0 jeśli jest dir'em? bo coś takiego mówiłeś
        while((directory = readdir(d))){
            if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0){
				continue;
			}
            //Tworzenie ścieżek joined_source_path i joined_target_path za pomocą appendToPath()
            if(isDirectory(joined_source_path) == 0 && !recursive){
				continue;
			}
            if(isDirectory(joined_target_path) == 0){
				sync(joined_source_path, joined_target_path, 1);
				if(isDirectory(joined_source_path) == -1 || (isDirectory(joined_source_path) != isDirectory(joined_target_path))){
					syslog(LOG_INFO, "Directory deleted %s", joined_target_path);
					rmdir(joined_target_path);
				}
			}
            else if(isDirectory(joined_source_path) == -1 || (isDirectory(joined_source_path) != isDirectory(joined_target_path))){
				syslog(LOG_INFO, "File deleted %s", joined_target_path);
				remove(joined_target_path);
			}
        }
    }
    DIR *d = opendir(src);
	struct dirent *directory;//nadpisywanie zmniennej nie wiem czy poprawne
    if(isDirectory(src) == 0 && isDirectory(dest) == 0){
		while((directory = readdir(d))){
			if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0){
				continue;
			}
			//Tworzenie ścieżek joined_source_path i joined_target_path za pomocą appendToPath()
			if(isDirectory(joined_source_path) == 0 && !recursive){
				continue;
			}
			if(isDirectory(joined_source_path) == 0 ){
				syslog(LOG_INFO, "Directory copied %s", joined_target_path);
				mkdir(joined_target_path , get_chmod(joined_source_path));
				sync(joined_source_path, joined_target_path);
			}
			else{
				syslog(LOG_INFO, "File copied %s", joined_target_path);
				sizeOfFile = getFileSize(joined_source_path);//size -> sizeOfFile?
				if(sizeOfFile < map_copy_size ){ //map_copy_size - zmienna globalna do dodania ig
					copyFile(joined_source_path, joined_target_path, size);//niezdefiniowane copyFile()
				}
				else{
					map_copy(joined_source_path, joined_target_path, size);//szczerze, to nie wiem o chuj chodzi.
				}
			}
		}
	}
    else{
        exit(EXIT_FAILURE);
    }
}

void signalHandler(int signal){

}
