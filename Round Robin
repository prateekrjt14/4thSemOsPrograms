// round robin scheduling algorithm 
#include<stdio.h>

typedef struct process{
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int finished;
    int responseTime;
    int alreadyEnqueued;
} Process;

int timeProgress[100]; int j = -1; int processTrack[100]; int k = -1;

void roundRobin(Process[], int, int);

int main()
{
    int n, timeQuantum;

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
        printf("\n");
        processes[i].processId = i + 1;
        processes[i].completionTime = 0;
        processes[i].waitingTime = 0;
        processes[i].turnAroundTime = 0;
        processes[i].finished = 0;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].alreadyEnqueued = 0;
    }
    
    printf("\nEnter the time quantum: ");
    scanf("%d",&timeQuantum);
    
    //Sorting the processes on the basis of their arival Time for round robin(if needed)
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(processes[j].arrivalTime > processes[j+1].arrivalTime)
            {
                Process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }// sorting over
    
    roundRobin(processes, n, timeQuantum);
    return 0;
}

void roundRobin(Process processes[], int n, int timeQuantum)
{
    int current = 0, rear = 0, front = 0;
    int queue[n+1];
    
    for(int i = 0; i<n+1; i++) // initializing all the elements of queue to '-1'
       queue[i] = -1;
    
    queue[current] = current;
    processes[current].alreadyEnqueued = 1;
    
    float avgWaitingTime = 0;
    float avgTurnAroundTime = 0;
    float avgResponseTime = 0;
    
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalResponseTime = 0;
    
    int elapsedTime = 0;
    timeProgress[++j] = 0;
    
    int finishedProcesses = n;
    
    printf("\nRound Robin Started...\nStatuses of ready queue and currently running processes\n");
    
    while(finishedProcesses)
    {
        if(processes[current].finished)// process(being pointed by 'current') has already finished execution
        {
           current = (current+1)%n;
           continue;
        }   
        
        if(processes[current].arrivalTime > elapsedTime)// to take care of the idle time
        {   elapsedTime = elapsedTime + (processes[current].arrivalTime - elapsedTime);
             timeProgress[++j]=elapsedTime;
             processTrack[++k] = 0;
        }  
        if(processes[current].remainingTime == processes[current].burstTime)// first cpu allocation to the process(being pointed by 'current')
           processes[current].responseTime = elapsedTime - processes[current].arrivalTime;
           
        processes[current].remainingTime-= timeQuantum;
        elapsedTime+=timeQuantum;
        
        if(processes[current].remainingTime < 0) // for the case, when the remaining time is lesser than the timeQuantum
        {
           elapsedTime+=processes[current].remainingTime;
           processes[current].remainingTime = 0;
        }  
        timeProgress[++j] = elapsedTime;
        processTrack[++k] = processes[current].processId;
        printf("\nProcess %d executed, now remaining time is %d, elapsed time = %d\n",processes[current].processId, processes[current].remainingTime, elapsedTime);
        
        if(processes[current].remainingTime == 0) // process(being pointed by 'current') has finished it's execution
        {
           processes[current].completionTime = elapsedTime;
           processes[current].turnAroundTime = processes[current].completionTime - processes[current].arrivalTime;
           processes[current].waitingTime = processes[current].turnAroundTime - processes[current].burstTime;
           processes[current].finished = 1;
           finishedProcesses--;
           
           printf("\n\nProcess %d finished, completion time is %d\n\n",processes[current].processId, elapsedTime);
        }
        // managing the queue

        for(int i = 0; i<n; i++)
        {
            if(processes[i].remainingTime == processes[i].burstTime && processes[i].arrivalTime <= elapsedTime && !processes[i].alreadyEnqueued)
            {
               rear = (rear+1)%(n+1);
               queue[rear] = i;
               printf("\nprocess %d enqueued\n\n", processes[queue[rear]].processId);
               processes[i].alreadyEnqueued = 1;
            }
        }
        
        if(processes[current].remainingTime!=0)
        {
            rear = (rear + 1)%(n+1);
            queue[rear] = current;
            printf("\nprocess %d enqueued\n\n", processes[current].processId);
        }
        
        queue[front] = -1;
        front = (front + 1)%(n+1);
        current = queue[front];
        
        // if curent equals '-1', the queue is empty and the cpu is in idle state
        if (current == -1) {
            int idleTime = elapsedTime;
            int nextProcess = -1;

            // Find the next process that has not finished and has the earliest arrival time
            for (int i = 0; i < n; i++) {
                if (!processes[i].finished && processes[i].arrivalTime > elapsedTime) {
                    if (nextProcess == -1 || processes[i].arrivalTime < processes[nextProcess].arrivalTime) {
                        nextProcess = i;
                    }
                }
            }

            if (nextProcess != -1) {
                elapsedTime = processes[nextProcess].arrivalTime;
                processTrack[++k] = 0;
                timeProgress[++j] = elapsedTime;
                printf("\nCPU idle from %d to %d\n", idleTime, elapsedTime);
                rear = front = 0;
                queue[front] = nextProcess;
                printf("\nProcess %d enqueued\n\n", processes[queue[rear]].processId);
                current = queue[front];
            }
        }
    }
    
    for(int i = 0; i<n;  i++)
    {
        for(int j = 0; j<n-i-1;  j++)
        {
            if(processes[j].processId > processes[j+1].processId)
            {
                Process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
    
    printf("\nObservation Table\nPID \tAT \t BT \tCT \tTT \tWT \tRT \n");
     
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime,processes[i].completionTime,processes[i].turnAroundTime, processes[i].waitingTime, processes[i].responseTime);
               
        totalTurnAroundTime+= processes[i].turnAroundTime;
        totalWaitingTime+= processes[i].waitingTime;
        totalResponseTime+=processes[i].responseTime;       
    }
    
    printf("\n\nGantt Chart\nP0-->Idle time\n");
    
    for(int i = 0; i<=k; i++)
        printf("| P%d\t",processTrack[i]);
        
    printf("|\n");
    
    for(int i = 0; i<=j; i++)
        printf("%d\t",timeProgress[i]);
        
    printf("\n");    
    
       
    avgTurnAroundTime = (float)totalTurnAroundTime/n;
    avgWaitingTime    = (float)totalWaitingTime/n;
    avgResponseTime   = (float)totalResponseTime/n;
    
    printf("\nAverage Waiting Time: %.2lf\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnAroundTime);
    printf("Average Response Time: %.2lf\n", avgResponseTime);
}
