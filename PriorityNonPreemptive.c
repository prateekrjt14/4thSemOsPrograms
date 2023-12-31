// priority non-preemptive scheduling algorithm

#include <stdio.h>

typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    int finished;
    int responseTime;
} Process;

void priorityNP(Process[], int);

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Enter Priority: ");
        scanf("%d", &processes[i].priority);
        printf("\n");
        processes[i].processId = i + 1;
        processes[i].finished = 0;
    }
    
    priorityNP(processes, n);
    
    return 0;
}

void priorityNP(Process processes[], int n)
{
    int exec;
    float avgTurnAroundTime = 0;
    float avgWaitingTime = 0;
    float avgResponseTime = 0;
    int totalTurnAroundTime = 0;
    int totalWaitingTime = 0;
    int totalResponseTime = 0;
    int elapsedTime = 0;
    int finishedProcesses = n; // till all the processes are over
    
    printf("\nGantt chart\n");
    
    while (finishedProcesses) {
        // Find the highest priority process that has arrived and not finished
        exec = -1;
        int lowestPriority = 9999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= elapsedTime && !processes[i].finished) // process has arrived, but has not been executed
            {
                if (processes[i].priority < lowestPriority) // this process has more priority than the 'exec' assigned priority, so we'll update the 'exec' 
                {
                    exec = i;
                    lowestPriority = processes[i].priority;
                }
            }
        }
        
        if (exec == -1)
        {
            // No process available to execute, increment the elapsed time
            printf("|(%d)***(%d)",elapsedTime,elapsedTime+1);
            elapsedTime++;
        } 
        
        else 
        {
            // Execute the selected process
            int temp = elapsedTime;
            processes[exec].responseTime = elapsedTime - processes[exec].arrivalTime;
            elapsedTime += processes[exec].burstTime;
            processes[exec].completionTime = elapsedTime;
            processes[exec].finished = 1;
            processes[exec].turnAroundTime = processes[exec].completionTime - processes[exec].arrivalTime;
            processes[exec].waitingTime = processes[exec].turnAroundTime - processes[exec].burstTime;
            finishedProcesses--;
            printf("|(%d) P%d (%d)",temp,processes[exec].processId,elapsedTime);
        }
    }
    printf("|\n\n");
    
    
   printf("Observation Table\nPr \tPID \tAT \t BT \tCT \tTT \tWT \tRT \n");
   
   for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].priority, processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime,processes[i].completionTime,processes[i].turnAroundTime, processes[i].waitingTime, processes[i].responseTime);
                         
        totalTurnAroundTime+= processes[i].turnAroundTime;
        totalWaitingTime+= processes[i].waitingTime;
        totalResponseTime+=processes[i].responseTime;       
    }
   
    avgTurnAroundTime = (float)totalTurnAroundTime/n;
    avgWaitingTime    = (float)totalWaitingTime/n;
    avgResponseTime   = (float)totalResponseTime/n;
    
    printf("\nAverage Waiting Time: %.2lf\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnAroundTime);
    printf("Average Response Time: %.2lf\n", avgResponseTime);
}
