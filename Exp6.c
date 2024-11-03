#include <stdio.h>
#include <stdbool.h>

int resources, processes;
int max[10][10], allocation[10][10], need[10][10], available[10];
bool finish[10];

void input() {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the Max Matrix for each process:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation Matrix for each process:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
            // Calculate the Need Matrix
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter the Available Resources:\n");
    for (int j = 0; j < resources; j++) {
        scanf("%d", &available[j]);
    }
}

bool isSafe() {
    int work[resources];
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[p][j] > work[j])
                        break;
                }

                if (j == resources) {
                    for (int k = 0; k < resources; k++)
                        work[k] += allocation[p][k];

                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            return false;  // System is in an unsafe state
        }
    }

    return true;  // System is in a safe state
}

void requestResources() {
    int process;
    int request[resources];

    printf("\nEnter the process number requesting resources: ");
    scanf("%d", &process);

    printf("Enter the request for resources: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &request[i]);

        if (request[i] > need[process][i]) {
            printf("Error: Request exceeds the need of process %d\n", process);
            return;
        }

        if (request[i] > available[i]) {
            printf("Error: Resources not available for process %d\n", process);
            return;
        }
    }

    // Tentatively allocate resources
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the new state is safe
    if (isSafe()) {
        printf("Resources have been allocated safely to process %d.\n", process);
    } else {
        printf("System is in an unsafe state! Request cannot be granted.\n");
        // Rollback allocation
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

int main() {
    input();

    if (isSafe()) {
        printf("\nThe system is in a safe state.\n");
    } else {
        printf("\nThe system is in an unsafe state.\n");
        return 0;
    }

    requestResources();

    return 0;
}