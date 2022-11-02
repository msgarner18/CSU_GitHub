FILES = Coordinator.java Buffer.java Producer.java Consumer.java
EXEC = Coordinator
MAIN = $(EXEC).java
ARGS = 7 21 3 3 7

TAR_NAME = Mark-Garner-HW5.tar

build:
	javac $(MAIN)
run:
	java $(EXEC) $(ARGS)
package: 
	tar cvzf $(TAR_NAME) $(FILES) *.txt Makefile
clean:
	rm -f $(TAR_NAME) Coordinator.class Buffer.class Producer.class Consumer.class