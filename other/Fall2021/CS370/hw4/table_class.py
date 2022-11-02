#a data structure that holds a list of processes
class Table:
    def __init__(self):
        self.table = []
    
    def append(self, process):
        self.table.append(process)

    #when I write table[pid], I want table to return the process with the given pid
    def __getitem__(self, subscript):
        for process in self.table:
            if process['pid'] == subscript:
                return process
        return None

    #returns the pid of the nth process if all the processes were sorted by pid
    def get_nth_pid(self, n):
        table = sorted(self.table, key=lambda process : process['pid'])
        return table[n]['pid']

    #returns an array of all processes whose arrival time is <= t and removes them from the table.
    #the list is sorted by pid before returning where the leftmost is the smallest pid
    def ready(self, t, sortBy = 'pid'):
        readyProcesses = []
        unaltered_table = self.table.copy()
        for process in unaltered_table:
            if process['arr_time'] <= t:
                readyProcesses.append(process)
                self.table.remove(process)

        return sorted(readyProcesses, key=lambda process : process[sortBy])
    
    def __len__(self):
        return len(self.table)

    def __bool__(self):
        return bool(self.table)

    #When I print table, I want it to show each element on a seperate line
    def __str__(self):
        output = ""
        for process in self.table:
            output += str(process) if output == "" else "\n" + str(process)
        return output