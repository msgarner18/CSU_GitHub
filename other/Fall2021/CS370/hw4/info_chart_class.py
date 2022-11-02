#provides methods to calculate and print the information you need when the scheduling algorithm has finished running.
class Info_chart:
    #fills the chart with all the information it needs from each of the processes and give inputs
    def __init__(self, orig_table, done, title, finish_time):
        self.chart = []
        self.title = title
        self.finish_time = finish_time
        for i in range(0, len(orig_table)):
            pid = orig_table.get_nth_pid(i)
            wait = self.waiting_time(done[pid])
            turn = self.turnaround_time(done[pid])
            self.chart.append({'pid': pid, 'wait': wait, 'turn': turn})

    def turnaround_time(self, process):
        return process['completion_time'] - process['arr_time']

    def waiting_time(self, process):
        return self.turnaround_time(process) - process['bur_time']

    def avg_waiting_time(self):
        avg = 0
        for line in self.chart:
            avg += line['wait']

        return avg / len(self.chart)

    def avg_turnaround_time(self):
        avg = 0
        for line in self.chart:
            avg += line['turn']

        return avg / len(self.chart)

    def throughput(self, finish_time):
        return len(self.chart)/finish_time

    #prints the chart above the gantt chart
    def print_chart(self):
        print()
        print(self.title.center(50, '-'))
        print("Process ID | Waiting Time | Turnaround Time")
        for line in self.chart:
            print(str(line['pid']).center(11, ' '), end = "|")
            print(str(line['wait']).center(14, ' '), end = "|")
            print(str(line['turn']).center(17, ' '), end = "\n")
        print()

    #prints the results below the gantt chart
    def print_results(self):
        print("Average Waiting Time: ", round(self.avg_waiting_time(), 12))
        print("Average Turnaround Time: ", round(self.avg_turnaround_time(), 12))
        print("Throughput: ", round(self.throughput(self.finish_time), 12))
        print()
