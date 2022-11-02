CC = gcc -lrt
FILES = Starter.c Fibb.c Prime.c Total.c CharacterReader.c
EXE1 = Starter
EXE2 = Fibb
EXE3 = Prime
EXE4 = Total
EXE5 = CharacterReader
TAR_NAME = Mark-Garner-HW3.tar

build: $(FILES)
	$(CC) -o $(EXE1) $(EXE1).c
	$(CC) -o $(EXE2) $(EXE2).c
	$(CC) -o $(EXE3) $(EXE3).c
	$(CC) -o $(EXE4) $(EXE4).c
	$(CC) -o $(EXE5) $(EXE5).c
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile *.txt
clean:
	rm -f $(EXE1) $(EXE2) $(EXE3) $(EXE4) $(EXE5)
