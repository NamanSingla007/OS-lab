#include <stdio.h>

int findLFU(int freq[], int frames) {
    int min = freq[0], pos = 0;

    for (int i = 1; i < frames; ++i) {
        if (freq[i] < min) {
            min = freq[i];
            pos = i;
        }
    }

    return pos;
}

int main() {
    int frames, pages, page_faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frame[frames], freq[frames];
    for (int i = 0; i < frames; ++i) {
        frame[i] = -1;
        freq[i] = 0;
    }

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int page[pages];
    printf("Enter the page references: ");
    for (int i = 0; i < pages; ++i)
        scanf("%d", &page[i]);

    for (int i = 0; i < pages; ++i) {
        int flag = 0;

        for (int j = 0; j < frames; ++j) {
            if (frame[j] == page[i]) {
                flag = 1;
                freq[j]++;
                break;
            }
        }

        if (!flag) {
            int pos = findLFU(freq, frames);
            frame[pos] = page[i];
            freq[pos] = 1;
            page_faults++;
        }

        printf("\nFrames after inserting page %d: ", page[i]);
        for (int j = 0; j < frames; ++j)
            printf("%d ", frame[j]);
    }

    printf("\n\nTotal Page Faults: %d\n", page_faults);

    return 0;
}