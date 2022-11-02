CC = gcc
OUT_EXE = test
FILES = test.c
TAR_NAME = Mark-Garner-test.tar

build: $(FILES)
	$(CC) -pthread -o $(OUT_EXE) $(FILES)
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile
clean:
	rm -f $(OUT_EXE)