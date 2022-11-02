#a data structure that represents a process. It's data can be altered, and it can be ran
class Process(dict):
    def __init__(self, pid, arr_time, bur_time, prior):
        self['pid'] = int(pid)
        self['arr_time'] = int(arr_time)
        self['bur_time'] = int(bur_time)
        self['bur_time_left'] = int(bur_time)
        self['prior'] = int(prior)
        self['completion_time'] = None
    
    #runs to completion or until end of tq
    #Also updates and returns time(t)
    def run(self, t, tq):
        run_time= self['bur_time_left'] if tq > self['bur_time_left'] else tq
        t += run_time
        self['bur_time_left'] -= run_time
        
        return t