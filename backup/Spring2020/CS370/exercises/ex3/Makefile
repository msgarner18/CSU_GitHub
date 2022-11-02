CC = gcc
OUT_EXE = ex3
FILES = Starter.c Fibb.c Prime.c Total.c
TAR_NAME = Mark-Garner-HW2.tar

prod: shm-posix-producer.c
	$(CC) -o $(OUT_EXE) shm-posix-producer.c
cons: shm-posix-consumer.c
	$(CC) -o $(OUT_EXE) shm-posix-consumer.c
pipe: unix_pipe.c
	$(CC) -o $(OUT_EXE) unix_pipe.c
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile *.h *.txt
clean:
	rm -f $(OUT_EXE)