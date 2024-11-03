#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;

    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }

    return pos;
}

int main() {
    int frames, pages, count = 0, time[10], flag1, flag2, pos, page_faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frame[frames];
    for (int i = 0; i < frames; ++i)
        frame[i] = -1;

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int page[pages];
    printf("Enter the page references: ");
    for (int i = 0; i < pages; ++i)
        scanf("%d", &page[i]);

    for (int i = 0; i < pages; ++i) {
        flag1 = flag2 = 0;

        for (int j = 0; j < frames; ++j) {
            if (frame[j] == page[i]) {
                count++;
                time[j] = count;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (int j = 0; j < frames; ++j) {
                if (frame[j] == -1) {
                    count++;
                    page_faults++;
                    frame[j] = page[i];
                    time[j] = count;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = findLRU(time, frames);
            count++;
            page_faults++;
            frame[pos] = page[i];
            time[pos] = count;
        }

        printf("\nFrames after inserting page %d: ", page[i]);
        for (int j = 0; j < frames; ++j)
            printf("%d ", frame[j]);
    }

    printf("\n\nTotal Page Faults: %d\n", page_faults);

    return 0;
}