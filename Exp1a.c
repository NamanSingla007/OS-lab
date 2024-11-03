#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
};

void calculateTimes(struct Process p[], int n) {
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            p[i].waitingTime = p[i-1].waitingTime + p[i-1].burstTime;
        } else {
            p[i].waitingTime = 0;
        }
        p[i].turnAroundTime = p[i].burstTime + p[i].waitingTime;
        totalWaitingTime += p[i].waitingTime;
        totalTurnAroundTime += p[i].turnAroundTime;
    }

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burstTime, p[i].waitingTime, p[i].turnAroundTime);
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &p[i].burstTime);
    }
    calculateTimes(p, n);
    return 0;
}