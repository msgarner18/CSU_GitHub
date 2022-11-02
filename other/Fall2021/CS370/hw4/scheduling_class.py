from infinite_class import Infinite
from gantt_chart_class import Gantt_chart
from queue_class import Queue
from table_class import Table
from info_chart_class import Info_chart
from copy import deepcopy

#contains methods to run all 3 scheduling algorithms and print their outputs
class Scheduler:
    def __init__(self, orig_table):
        self.orig_table = orig_table
        
    #call this before running each algorithm
    def reset(self):
        self.table = deepcopy(self.orig_table)
        self.waitQueue = Queue()
        self.gantt_chart = Gantt_chart()
        self.t = 0
        self.done = Table()

    #runs the process, adds outcome to gantt chart, updates state
    def runProcess(self, running_process, tq):
        #run process until it finishes, or tq is up
        start = self.t
        self.t = running_process.run(self.t, tq)

        #record what happened in gantt_chart
        self.gantt_chart.add(start, running_process['pid'], self.t)

        #if process didn't finish it, save it in hold to be added to queue later
        if running_process['bur_time_left'] != 0:
            self.waitQueue.hold.append(running_process)
        else:
            running_process['completion_time'] = self.t
            self.done.append(running_process)

    #runs an algorithm
    #title is the label that will be used when printing out th output
    #sortBy is which attribute takes priority when more than 1 process are added to the wait queue
    #tq is the time quotient
    def run(self, title, sortBy = 'pid', tq = Infinite()):
        self.reset()
        while self.waitQueue or self.table:
            # if wait queue is empty after pulling all ready processes from table,
            if not self.waitQueue.push(self.table.ready(self.t, sortBy)):
                self.t = self.gantt_chart.wait(self.t)
            else:
                self.runProcess(self.waitQueue.pop(), tq)
        self.print(title)

    def fcfs(self):
        self.run("FCFS")

    def priority(self):
        self.run("PS", 'prior')

    def round_robin(self, tq):
        self.run("Round Robin", 'pid', tq)
        

    #prints the output of the last ran algorithm
    def print(self, title):
        info_chart = Info_chart(self.orig_table, self.done, title, self.t)
        info_chart.print_chart()
        self.gantt_chart.print()
        info_chart.print_results()

