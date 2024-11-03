#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, head, direction, total_distance = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int request[n + 2];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    int max_cylinder;
    printf("Enter the maximum cylinder value: ");
    scanf("%d", &max_cylinder);

    request[n] = head;
    request[n + 1] = (direction == 1) ? max_cylinder : 0;

    qsort(request, n + 2, sizeof(int), compare);

    int index = 0;
    while (request[index] != head)
        index++;

    if (direction == 1) {
        for (int i = index; i < n + 2; i++) {
            total_distance += abs(request[i] - head);
            head = request[i];
        }
        for (int i = index - 1; i >= 0; i--) {
            total_distance += abs(request[i] - head);
            head = request[i];
        }
    } else {
        for (int i = index; i >= 0; i--) {
            total_distance += abs(request[i] - head);
            head = request[i];
        }
        for (int i = index + 1; i < n + 2; i++) {
            total_distance += abs(request[i] - head);
            head = request[i];
        }
    }

    printf("Total distance: %d\n", total_distance);
    return 0;
}