import sys
import csv
from scheduling_class import Scheduler
from process_class import Process
from table_class import Table

#checks if there are headers to skip before skipping headers
def skipHeaders(csv_reader):
    try:
        next(csv_reader)
    except StopIteration:
        sys.stderr.write("Must provide headers \"ProcessID,Arrival Time,Burst Time,Priority\"!\n")
        exit(1)

#error checks each line that is read so that it is in proper format
def checkedLine(i, line):
    try:
        int(line[0])
        int(line[1])
        int(line[2])
        int(line[3])
    except ValueError:
        sys.stderr.write("Line " + str(i+2) + ": " + str(line) + " in " + sys.argv[1] + " must contain only integers!\n")
        exit(1)
    if len(line) == 4:
        return line
    
    sys.stderr.write("Line " + str(i+2) + ": " + str(line) + " in " + sys.argv[1] + " must have exactly 4 elements!\n")
    exit(1)

#error checks filling table with csv_reader
def table_from_reader(csv_reader):
    table = Table()
    for i, line in enumerate(csv_reader):
        table.append(Process(*checkedLine(i, line)))

    if len(table) == 0:
        sys.stderr.write("Must provide at least 1 process!\n")
        exit(1)

    return table

#returns table filled with the elements from file and returns errors if anything is wrong with the file
def fill_orig_table(file):
    try:
        with open(file, 'r', encoding='utf-8-sig') as csv_file:
            csv_reader = csv.reader(csv_file)

            skipHeaders(csv_reader)
            table = table_from_reader(csv_reader)
            
    except IOError:
        sys.stderr.write("Could not open file \"" + file + '\"!\n')
        exit(1)
    
    return table

def main():
    if len(sys.argv) != 3:
        sys.stderr.write("You must provide exactly 2 arguments!\n")
        exit(1)
    if int(sys.argv[2]) <= 0:
        sys.stderr.write("Time Quantum must be greater than 0!\n")
        exit(1)

    scheduler = Scheduler(fill_orig_table(sys.argv[1]))
    scheduler.fcfs()
    scheduler.priority()
    scheduler.round_robin(int(sys.argv[2]))

if __name__ == "__main__":
    main()