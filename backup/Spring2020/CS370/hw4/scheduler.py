import sys
import csv
import time
from typing import Dict, List

#opens and reads CSV file and stores the data in the global variable csv_table
#csv_table number values are stored as ints rather than strings
def openCSV():
    global csv_table

    #open csv file and store contents in csv_reader
    file_handle = open(sys.argv[1], 'r', encoding = "utf8")
    csv_reader = csv.DictReader(file_handle)

    #change values to integer type instead of string type
    table: List[Dict[str, int]] = []
    for row in csv_reader:
        int_row: Dict[str, int] = {}
        for col in row:
            int_row[col] = int(row[col])
        table.append(int_row)

    #store resulting table in global value csv_table to be referenced by other functions
    csv_table = table
    file_handle.close()

#returns the row with processID id
#ex: rowWithID(1) returns the row in the csv_table with processID 1
def rowWithID(id):
    for line in csv_table:
        if line['ProcessID'] == id:
            return line
    return None

'''
Scheduling Algorithms
'''

#runs FCFS scheduling algorithm on csv_table and returns a 2 dimensional array representing the resulting gantt chart
def FCFS():
    finishedProcesses = []#array of processes that have completed (1-4)
    gantt = []#return value
    time = 0#arrivalTime
    idleSum = 0#time spent idling

    #run while there still exists processes that have not completed
    while len(finishedProcesses) < len(csv_table):

        #for every processin the csv table
        for id in range(1, len(csv_table)+1):
            line = rowWithID(id)#line represents the information associated with a generic process
            #if process has arrived and isn't complete
            if line['Arrival Time'] <= time and not(id in finishedProcesses):
                #if we just finished idling, append idle to gantt chart and reset idleSum
                if idleSum > 0:
                    gantt.append([time-idleSum, -1, time])
                    idleSum = 0
                #run process for burst time ammount of time
                time += line['Burst Time']
                #process is now complete and added to gantt chart
                gantt.append([time, id, time+line['Burst Time']])
                finishedProcesses.append(id)
            else:
                #if none of the processes have arrived, begin idling
                if id == len(csv_table):
                    idleSum+=1
                    time += 1
    return gantt

#runs SJFP scheduling algorithm on csv_table and returns a 2 dimensional array representing the resulting gantt chart
def SJFP():
    global csv_table#I need this because I change the contents of csv_table
    finishedProcesses = []#array of processes that have completed (1-4)
    gantt = []#return value
    time = 0#arrivalTime
    idleSum = 0#time spent idling
    prevProcess = None#starts at None to signify that prevProcess has not been assigned yet
    #run while there still exists processes that have not completed
    while len(finishedProcesses) < len(csv_table):
        #add processes to ready Queue
        readyQueue = []
        for id in range(1, len(csv_table)+1):
            line = rowWithID(id)#line represents the information associated with a generic process
            #if process has arrived and isn't complete
            if line['Arrival Time'] <= time and not(rowWithID(id) in finishedProcesses):
                readyQueue.append(line)
        
        #If there exists at least 1 process in ready Queue
        if len(readyQueue) > 0:
            #if IDLE is greater than 0, push IDLE to Gantt chart and reset IDLE to 0
            if idleSum > 0:
                gantt.append([time-idleSum, -1, time])
                idleSum = 0
            
            #Determine shortest process of processes in ready Queue
            shortestProcess = readyQueue[0]
            for line in readyQueue:
                if line['Burst Time'] < shortestProcess['Burst Time']:
                    shortestProcess = line
            
            #set process's arrival time to be passed to gantt chart
            if shortestProcess != prevProcess:
                shortestProcess['Arrival Time'] = time

            #if shortest process is not the same as previous Process (and previous process is not equal to None), push previous Process to Gantt Chart
            if prevProcess != None and prevProcess not in finishedProcesses and shortestProcess != prevProcess:
                gantt.append([prevProcess['Arrival Time'], prevProcess['ProcessID'], time])
            prevProcess = shortestProcess
            
            #run shortest process for 1 second
            shortestProcess['Burst Time'] -= 1
            
            #if doing so completes this process, add process to finished process and print to Gantt Chart
            if shortestProcess['Burst Time'] <= 0:
                finishedProcesses.append(shortestProcess)
                gantt.append([shortestProcess['Arrival Time'], shortestProcess['ProcessID'], time+1])
        else:
            #run IDLE for 1 second
            idleSum += 1

        time += 1
    openCSV()#return csv_table to it's original state
    return gantt

#runs Round Robin scheduling algorithm on csv_table and returns a 2 dimensional array representing the resulting gantt chart
def roundRobin():
    global csv_table#I need this because I change the contents of csv_table in this function
    
    #if time a time quotient wasn't given to us, we can't run this function
    if len(sys.argv) > 2:
        tq = int(sys.argv[2])#time quotient
        finishedProcesses = []#array of processes that have completed (1-4)
        gantt = []#return value
        time = 0#arrivalTime
        idleSum = 0#time spent idling
        readyQueue = []
        save = None#if a process needs to return to readyQueue, I set save equal to that process
        
        #run until all processes are finished
        while len(finishedProcesses) < len(csv_table):
            #add processes with arrival times greater than or equal to time
            for id in range(1, len(csv_table)+1):
                line = rowWithID(id)
                if line['Arrival Time'] <= time and line not in readyQueue and line not in finishedProcesses and line != save:
                    readyQueue.append(line)
            
            #add save to ready queue
            if save != None:
                readyQueue.append(save)
                save = None

            #run next process in ready queue
            if len(readyQueue) > 0:
                #if we have just finished idling, add that time to gantt chart
                if idleSum > 0:
                    gantt.append([time-idleSum, -1, time])
                    idleSum = 0
                process = readyQueue.pop(0)#remove first process from readyQueue and store it in process
                arrival = time#save value for gantt chart

                #run process depending on whether time left is less than tq or not
                if process['Burst Time'] <= tq:
                    #run process until process is complete
                    time += process['Burst Time']
                    finishedProcesses.append(process)
                else:
                    #run process for tq seconds. Save process to be put back into readyQueue later
                    time += tq
                    process['Burst Time'] -= tq
                    save = process
                #push results to gantt chart
                cur = time
                gantt.append([arrival, process['ProcessID'], cur])
            else:
                #run idle while readyQueue is empty
                idleSum += 1
                time += 1
        
        openCSV()#restores csv_table to its original values
        return gantt

#returns the turnaround time for given id and gantt chart
def findTaround(id, gantt):
    for i in range(len(gantt)-1, -1, -1):
        if gantt[i][1] == id:
            completionTime = gantt[i][2]
            break
    #print("id: "+str(id)+" Completion: "+str(completionTime)+" arrival time: "+str(rowWithID(id)['Arrival Time']))
    return completionTime-rowWithID(id)['Arrival Time']

#returns the waiting time for given id and gantt chart
def findWait(id, gantt):
    return findTaround(id, gantt) - rowWithID(id)['Burst Time']

#returns an array of turn around times where 0th index holds processID 1
def fillTaround(gantt):
    taround = []
    for i in range(1, len(csv_table)+1):
        taround.append(findTaround(i, gantt))
    return taround

#returns an array of waiting times where 0th index holds processID 1
def fillWait(gantt):
    wait = []
    for i in range(1, len(csv_table)+1):
        wait.append(findWait(i, gantt))
    return wait

#returns throughput given gantt chart
def throughput(gantt):
    time = gantt[len(gantt)-1][2]
    processNum = len(csv_table)
    return processNum/time

#takes in wait, and turnaround arrays and prints out waiting time and turnaround chart
def printChart(wait, taround):
    print("%s | %s | %s" %("Process ID", "Waiting Time", "Turnaround Time"))
    for i in range(len(wait)):
        print("    %-7s|      %-8s|        %s" %(i+1, wait[i], taround[i]))
    print()

#prints the gantt chart in proper format
#gantt is a 2-dimensional array where each array inside it represents a single entry in the gantt chart
#[n]-nth line in gantt chart. [n][0]-left value on nth line. [n][1]-middle value on nth line. [n][2]-right value on nth line
def printGantt(gantt):
    print("Gantt chart is:")
    for row in gantt:
       print("[%s]" %(str(row[0]).center(5)), end = "")
       if row[1] == -1:
           print("--%s" %(" IDLE "), end = "")
       else:
           print("--%s" %(str(row[1]).center(6)), end = "")
       print("--[%s]" %(str(row[2]).center(5)))
    print()

#given an array of values, returns the avg of the values
def avg(arr):
    sum = 0
    for val in arr:
        sum += val
    return sum/len(arr)

#given the gantt chart created by one of the three scheduling algorithms, prints out the information in proper format
def printAlg(gantt):
    wait = fillWait(gantt)
    taround = fillTaround(gantt)
    printChart(wait, taround)
    printGantt(gantt)
    print("Average Waiting Time:  " + str(avg(wait)))
    print("Average Turnaround Time:  " + str(avg(taround)))
    print("Throughput:  " + str(throughput(gantt)))
    print()

#runs the 3 scheduling algorithms and prints out results in proper format
def runAlgorithms():
    print(17*"-"+" FCFS " + 17*"-")
    gantt = FCFS()
    printAlg(gantt)
    
    print(17*"-"+" SJFP " + 17*"-")
    gantt = SJFP()
    printAlg(gantt)

    print(17*"-"+" Round Robin " + 17*"-")
    gantt = roundRobin()
    printAlg(gantt)

def main():
    openCSV()
    runAlgorithms()
       
if __name__ == "__main__":
    main()