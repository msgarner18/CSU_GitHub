CC = gcc
FILE1 = shm-posix-producer.c
FILE2 = shm-posix-consumer.c
FILES = $(FILE1) $(FILE2)
EXE1 = shm-posix-producer
EXE2 = shm-posix-consumer

build: $(FILES)
	$(CC) -lrt -o $(EXE1) $(FILE1)
	$(CC) -lrt -o $(EXE2) $(FILE2)