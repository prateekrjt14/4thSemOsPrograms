// Priority preemptive scheduling algorithm

#include<stdio.h>

typedef struct process {
    int processId;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int responseTime;
} Process;

void priorityPreemptive(Process[], int);
int timeProgress[100], processTrack[100], j = -1, k = -1;

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Accept process details from the user
    for (int i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Enter Priority: ");
        scanf("%d", &processes[i].priority);
        printf("\n");
        processes[i].processId = i + 1;
        processes[i].remainingTime = processes[i].burstTime; // creating copy of burstTime
    }

    priorityPreemptive(processes, n);

    return 0;
}

void priorityPreemptive(Process processes[], int n)
{
    float avgWaitingTime = 0;
    float avgTurnAroundTime = 0;
    float avgResponseTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalResponseTime = 0;
    int elapsedTime = 0;
    int remainingProcesses = n;
    timeProgress[++j] = 0;

    while (remainingProcesses)
    {
        int exec = -1;
        int lowestPriorityValue = 9999;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= elapsedTime && processes[i].remainingTime > 0)
            {
                if (processes[i].priority < lowestPriorityValue)
                {
                    lowestPriorityValue = processes[i].priority;
                    exec = i;
                }
            }
        }

        if (exec == -1)
        {
            processTrack[++k] = 0;
            elapsedTime++;
            timeProgress[++j] = elapsedTime;
            continue;
        }

        if (processes[exec].remainingTime == processes[exec].burstTime) // first cpu allocation
        {
            processes[exec].responseTime = elapsedTime - processes[exec].arrivalTime;
        }

        processes[exec].remainingTime--;
        elapsedTime++;
        
        processTrack[++k] = processes[exec].processId;
        timeProgress[++j] = elapsedTime;

        if (processes[exec].remainingTime == 0) // process has been executed
        {
            processes[exec].completionTime = elapsedTime;
            processes[exec].turnAroundTime = processes[exec].completionTime - processes[exec].arrivalTime;
            processes[exec].waitingTime = processes[exec].turnAroundTime - processes[exec].burstTime;
            totalTurnAroundTime += processes[exec].turnAroundTime;
            totalWaitingTime += processes[exec].waitingTime;
            totalResponseTime += processes[exec].responseTime;
            remainingProcesses--;
        }
    }

    avgTurnAroundTime = (float)totalTurnAroundTime / n;
    avgWaitingTime = (float)totalWaitingTime / n;
    avgResponseTime = (float)totalResponseTime / n;

    printf("\nObservation Table\nPr\tPID \tAT \t BT \tCT \tTT \tWT \tRT \n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].priority,processes[i].processId, processes[i].arrivalTime,
            processes[i].burstTime, processes[i].completionTime, processes[i].turnAroundTime, processes[i].waitingTime, processes[i].responseTime);

    }
    
    printf("\nGantt Chart\n(P0-->idle time)\n");
    for(int i = 0; i<=k; i++)
        printf("| P%d\t",processTrack[i]);
        
    printf("|\n");
    
    for(int i = 0; i<=j; i++)
        printf("%d\t",timeProgress[i]);
        
    printf("\n");

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
}
