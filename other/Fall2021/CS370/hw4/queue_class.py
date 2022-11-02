#a data structure that holds a queue of processes
class Queue(list):
    def __init__(self):
        self.queue = []
        self.hold = []

    #pushes a list of process into the queue. Processes are added from left to right
    #returns true if, afterwards, queue contains at least one element (hold or queue)
    def push(self, elementList):
        for element in elementList:
            self.queue.insert(0, element)
        
        return bool(self)

    #before popping, ensure that the held process is added back in to queue
    def pop(self):
        if self.hold:
            self.queue.insert(0, self.hold.pop())
        return self.queue.pop()

    def __bool__(self):
        return bool(self.queue) or bool(self.hold)

    def __str__(self):
        return str(self.queue)