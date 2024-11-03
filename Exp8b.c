#include <stdio.h>

int predict(int pages[], int frames[], int pages_len, int index, int frames_count) {
    int pos = -1, farthest = index;
    for (int i = 0; i < frames_count; i++) {
        int j;
        for (j = index; j < pages_len; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == pages_len) return i;
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int frames, pages;
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

    int page_faults = 0;
    for (int i = 0; i < pages; ++i) {
        int flag = 0;

        for (int j = 0; j < frames; ++j) {
            if (frame[j] == page[i]) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            int pos;
            if (i < frames)
                pos = i;
            else
                pos = predict(page, frame, pages, i + 1, frames);
            
            frame[pos] = page[i];
            page_faults++;
        }

        printf("\nFrames after inserting page %d: ", page[i]);
        for (int j = 0; j < frames; ++j)
            printf("%d ", frame[j]);
    }

    printf("\n\nTotal Page Faults: %d\n", page_faults);

    return 0;
}