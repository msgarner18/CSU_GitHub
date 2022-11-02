CC = gcc
OUT_EXE = hw2
EXE1 = Initiator
EXE2 = Pell
EXE3 = Composite
EXE4 = Total
EXE5 = Reader
FILES = $(EXE1).c $(EXE2).c $(EXE3).c $(EXE4).c $(EXE5).c Shared.h

TAR_NAME = Mark-Garner-HW3.tar

build: $(FILES)
	$(CC) -o $(EXE1) $(EXE1).c -lrt
	$(CC) -o $(EXE2) $(EXE2).c -lrt -lm
	$(CC) -o $(EXE3) $(EXE3).c -lrt
	$(CC) -o $(EXE4) $(EXE4).c -lrt
	$(CC) -o $(EXE5) $(EXE5).c -lrt
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile README.txt
clean:
	rm -f $(EXE1) $(EXE2) $(EXE3) $(EXE4) $(EXE5)