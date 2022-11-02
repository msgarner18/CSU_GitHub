FILE1 = Invoker
FILE2 = Producer
FILE3 = Consumer
FILE4 = Bdbuffer
FILE5 = Tuple

TAR_NAME = Mark-Garner-HW5_EC.tar

FILES = $(FILE1).java $(FILE2).java $(FILE3).java $(FILE4).java $(FILE5).java

build: $(FILES)
	javac $(FILES)
clean:
	rm $(FILE1).class $(FILE2).class $(FILE3).class $(FILE4).class $(FILE5).class
package:
	tar cvzf $(TAR_NAME) $(FILES) Makefile README.txt