CC = gcc
OUT_EXE = ex2
FILES = Starter.c Fibb.c Prime.c Total.c
TAR_NAME = Mark-Garner-HW2.tar

fork: Fork.c
	$(CC) -o $(OUT_EXE) Fork.c
mfork: 
	$(CC) -o $(OUT_EXE) multi-fork.c
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile *.h *.txt
clean:
	rm -f $(OUT_EXE)