#provides methods to update your gantt chart as your processes run
class Gantt_chart:
    def __init__(self):
        self.table=[]
        self.wait_time = 0
    
    #while waiting, call this function and the idle row will automatically be added when done waiting
    def wait(self, t):
        self.wait_time += 1
        t += 1

        return t

    # if any wait time has been accumulated, add it to your gantt chart
    def flush_wait(self, start):
        if self.wait_time > 0:
            entry = {
                'start': start-self.wait_time,
                'pid': 'IDLE',
                'end': start
            }
            self.table.append(entry)
            self.wait_time = 0

    #adds a row to gantt chart
    def add(self, start, pid, end):
        self.flush_wait(start)

        entry = {
            'start': start,
            'pid': pid,
            'end': end
        }
        self.table.append(entry)

    # string representation of this data
    def __str__(self):
        output = ""
        for row in self.table:
            output += str(row) if output == "" else "\n" + str(row)
        return output

    #prints gantt chart in proper format
    def print(self):
        print("Gantt Chart is:")
        for row in self.table:
            arg1 = str(row['start']).center(7)
            arg2 = str(row['pid']).center(7)
            arg3 = str(row['end']).center(7)
            print("[{}]--{}--[{}]".format(arg1, arg2, arg3))
        print()