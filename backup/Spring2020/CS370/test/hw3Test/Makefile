CC = gcc -lrt
OUT_EXE = hw2
FILES = Child.c Parent.c
EXE1 = Parent
EXE2 = Child
TAR_NAME = Mark-Garner-HW2.tar

build: $(FILES)
	$(CC) -o $(EXE1) $(EXE1).c
	$(CC) -o $(EXE2) $(EXE2).c
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile *.txt
clean:
	rm -f $(EXE1) $(EXE2)
