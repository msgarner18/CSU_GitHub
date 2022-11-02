CC = gcc
OUT_EXE = hw2
FILES = Starter.c Fibb.c Prime.c Total.c
EXE1 = Starter
EXE2 = Fibb
EXE3 = Prime
EXE4 = Total
TAR_NAME = Mark-Garner-HW2.tar

build: $(FILES)
	$(CC) -o $(EXE1) $(EXE1).c
	$(CC) -o $(EXE2) $(EXE2).c
	$(CC) -o $(EXE3) $(EXE3).c
	$(CC) -o $(EXE4) $(EXE4).c
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile *.txt
clean:
	rm -f $(EXE1) $(EXE2) $(EXE3) $(EXE4)
