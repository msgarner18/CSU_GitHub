CC = gcc
OUT_EXE = hw1
FILES = Starter.c Executor.c
TAR_NAME = Mark-Garner-HW1.tar

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile *.h *.txt
clean:
	rm -f $(OUT_EXE)