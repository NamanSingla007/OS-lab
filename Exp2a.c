#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateTimes(struct Process proc[], int n, int quantum) {
    int time = 0;  // Current time
    int done;  // Flag to check if all processes are done

    while (1) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                done = 0;  // There is at least one process remaining
                if (proc[i].remainingTime > quantum) {
                    time += quantum;
                    proc[i].remainingTime -= quantum;
                } else {
                    time += proc[i].remainingTime;
                    proc[i].waitingTime = time - proc[i].burstTime;
                    proc[i].remainingTime = 0;
                }
            }
        }
        if (done) {
            break;
        }
    }

    // Calculate turnaround times
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime;
    }
}

void displayProcessInfo(struct Process proc[], int n) {
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }
}

int main() {
    int n, quantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for process %d: ", proc[i].id);
        scanf("%d", &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].waitingTime = 0;
        proc[i].turnaroundTime = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    calculateTimes(proc, n, quantum);
    displayProcessInfo(proc, n);

    return 0;
}