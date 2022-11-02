CC = gcc
OUT_EXE = hw2
EXE1 = Initiator
EXE2 = Pell
EXE3 = Composite
EXE4 = Total
FILES = $(EXE1).c $(EXE2).c $(EXE3).c $(EXE4).c

TAR_NAME = Mark-Garner-HW2.tar

build: $(FILES)
	$(CC) -o $(EXE1) $(EXE1).c
	$(CC) -o $(EXE2) $(EXE2).c -lm
	$(CC) -o $(EXE3) $(EXE3).c
	$(CC) -o $(EXE4) $(EXE4).c
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile README.txt
clean:
	rm -f $(EXE1) $(EXE2) $(EXE3) $(EXE4)