// fcfs scheduling algorithm

#include<stdio.h>

typedef struct node{
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int responseTime;
} Process;

void fcfs(Process[],int);

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
        processes[i].processId = i + 1;
        printf("\n");
    }
    // Sort processes based on arrival time (if needed)
       for (int i = 0; i < n - 1; i++)
       {
           for (int j = 0; j < n - i - 1; j++) 
           {
               if (processes[j].arrivalTime > processes[j + 1].arrivalTime) 
               {
                   Process temp = processes[j];
                   processes[j] = processes[j + 1];
                   processes[j + 1] = temp;
               }
           }
       } // sorting over
     
 
    fcfs(processes,n);

   return 0;
}

void fcfs(Process processes[], int n)
{
   int elapsedTime = 0;
   float avgWaitingTime = 0;
   float avgTurnAroundTime = 0;
   float avgResponseTime = 0;
   int totalWaitingTime = 0;
   int totalTurnAroundTime = 0;
   int totalResponseTime = 0;
      
    printf("\nGantt chart\n");  
    for(int i = 0; i<n; i++)
    {
        if(processes[i].arrivalTime > elapsedTime) // to take care of the idle time
          elapsedTime = elapsedTime + (processes[i].arrivalTime - elapsedTime);
        
        int temp = elapsedTime; 
        processes[i].responseTime = elapsedTime - processes[i].arrivalTime;  
        elapsedTime+=processes[i].burstTime;
        processes[i].completionTime = elapsedTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
        printf("|(%d)  P%d  (%d)",temp,processes[i].processId,elapsedTime);
    }
    
    printf("|\n");
    printf("Observation Table\nPID \tAT \t BT \tCT \tTT \tWT \tRT \n");
     
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].processId, processes[i].arrivalTime,
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
