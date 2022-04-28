OBJ = main.o file_service.o utility.o synchronize.o
all: Project
Project: $(OBJ)
	gcc $(OBJ) -o Project
$(obj): commons.h file_service.h utility.h synchronize.h
.PHONY: clean
clean:
	rm -f *.o
	rm -f *.txt
main.o: main.c commons.h file_service.h utility.h synchronize.h
	gcc -c main.c
file_service.o: file_service.c file_service.h
	gcc -c file_service.c
utility.o: utility.c utility.h
	gcc -c utility.c
synchronize.o: synchronize.c synchronize.h
	gcc -c synchronize.c
