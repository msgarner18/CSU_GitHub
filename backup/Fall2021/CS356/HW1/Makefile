CC = g++
OUT_EXE = hw1
FILES = Main.cc
TAR_NAME = Mark-Garner-HW1.tar

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
package: 
	tar cvzf $(TAR_NAME) $(FILES) Makefile README.txt
clean:
	rm -f $(OUT_EXE)