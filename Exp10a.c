#include <stdio.h>
#include <stdlib.h>  

int main() {
    int n, head, total_distance = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for (int i = 0; i < n; i++) {
        total_distance += abs(request[i] - head);
        head = request[i];
    }

    printf("Total distance: %d\n", total_distance);
    return 0;
}