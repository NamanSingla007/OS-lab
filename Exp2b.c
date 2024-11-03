#include <stdio.h>

#define MAX 100

typedef struct {
    int id;          // Process ID
    int arrival;     // Arrival Time
    int burst;       // Burst Time
    int priority;    // Priority
    int remaining;   // Remaining Time (for preemption)
    int completion;  // Completion Time
    int waiting;     // Waiting Time
    int turnaround;  // Turnaround Time
    int is_completed; // Status flag for process completion
} Process;

void findWaitingTime(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

void findTurnaroundTime(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
    }
}

int main() {
    int n, time = 0, completed = 0, prev = -1;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[MAX];

    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time, burst time, and priority for process %d: ", i + 1);
        p[i].id = i + 1;
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].remaining = p[i].burst;
        p[i].is_completed = 0;
    }

    while (completed != n) {
        int idx = -1;
        int highest_priority = 100000;

        // Find the process with the highest priority at current time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].is_completed == 0) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                }
                if (p[i].priority == highest_priority) {
                    if (p[i].arrival < p[idx].arrival) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            if (p[idx].remaining == p[idx].burst) {
                p[idx].completion = time + p[idx].burst;
            }

            p[idx].remaining--;
            time++;

            if (p[idx].remaining == 0) {
                p[idx].is_completed = 1;
                completed++;
                p[idx].completion = time;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
            }
        } else {
            time++;
        }
    }

    // Output results
    printf("\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", 
            p[i].id, p[i].arrival, p[i].burst, p[i].priority, p[i].completion, p[i].turnaround, p[i].waiting);
    }

    return 0;
}