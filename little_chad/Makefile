OBJ = main.o file_service.o utility.o
all: Project
Project: $(OBJ)
	gcc $(OBJ) -o Project
$(obj): file_service.h utility.h
.PHONY: clean
clean:
	rm -f *.o
	rm -f *.txt
main.o: main.c file_service.h utility.h
	gcc -c main.c
file_service.o: file_service.c file_service.h
	gcc -c file_service.c
utility.o: utility.c utility.h
	gcc -c utility.c