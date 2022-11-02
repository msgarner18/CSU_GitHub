
FILES = scheduler.py
CSV = processes.csv

TAR_NAME = Mark-Garner-HW4.tar

build:
	python3 $(FILES) $(CSV) 4
package: 
	tar cvzf $(TAR_NAME) $(FILES) *.txt
clean:
	rm -f $(TAR_NAME)
