#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 10
#define MAX_BLOCKS 100

// Structures for file allocation methods

// For sequential file allocation
struct SequentialFile {
    char name[20];
    int startBlock;
    int length;
};

// For indexed file allocation
struct IndexedFile {
    char name[20];
    int indexBlock;
    int blocks[MAX_BLOCKS];
    int blockCount;
};

// Function prototypes
void allocateSequentialFile(struct SequentialFile files[], int *fileCount, int *blockMap);
void allocateIndexedFile(struct IndexedFile files[], int *fileCount, int *blockMap);
void displaySequentialFiles(struct SequentialFile files[], int fileCount);
void displayIndexedFiles(struct IndexedFile files[], int fileCount);

int main() {
    struct SequentialFile sequentialFiles[MAX_FILES];
    struct IndexedFile indexedFiles[MAX_FILES];
    int sequentialFileCount = 0, indexedFileCount = 0;
    int blockMap[MAX_BLOCKS] = {0}; // 0: free, 1: allocated

    int choice;
    while (1) {
        printf("\nFile Allocation Menu:\n");
        printf("1. Allocate Sequential File\n");
        printf("2. Allocate Indexed File\n");
        printf("3. Display Sequential Files\n");
        printf("4. Display Indexed Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                allocateSequentialFile(sequentialFiles, &sequentialFileCount, blockMap);
                break;
            case 2:
                allocateIndexedFile(indexedFiles, &indexedFileCount, blockMap);
                break;
            case 3:
                displaySequentialFiles(sequentialFiles, sequentialFileCount);
                break;
            case 4:
                displayIndexedFiles(indexedFiles, indexedFileCount);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

// Function to allocate a sequential file
void allocateSequentialFile(struct SequentialFile files[], int *fileCount, int *blockMap) {
    struct SequentialFile file;
    printf("Enter file name: ");
    scanf("%s", file.name);
    printf("Enter start block: ");
    scanf("%d", &file.startBlock);
    printf("Enter file length: ");
    scanf("%d", &file.length);

    // Check if blocks are available
    for (int i = file.startBlock; i < file.startBlock + file.length; i++) {
        if (blockMap[i] == 1) {
            printf("Block %d is already allocated.\n", i);
            return;
        }
    }

    // Allocate blocks
    for (int i = file.startBlock; i < file.startBlock + file.length; i++) {
        blockMap[i] = 1;
    }

    files[*fileCount] = file;
    (*fileCount)++;
    printf("File allocated successfully.\n");
}

// Function to allocate an indexed file
void allocateIndexedFile(struct IndexedFile files[], int *fileCount, int *blockMap) {
    struct IndexedFile file;
    printf("Enter file name: ");
    scanf("%s", file.name);
    printf("Enter index block: ");
    scanf("%d", &file.indexBlock);

    // Check if index block is available
    if (blockMap[file.indexBlock] == 1) {
        printf("Index block %d is already allocated.\n", file.indexBlock);
        return;
    }

    printf("Enter number of blocks: ");
    scanf("%d", &file.blockCount);

    printf("Enter block numbers: ");
    for (int i = 0; i < file.blockCount; i++) {
        scanf("%d", &file.blocks[i]);
        if (blockMap[file.blocks[i]] == 1) {
            printf("Block %d is already allocated.\n", file.blocks[i]);
            return;
        }
    }

    // Allocate index block and file blocks
    blockMap[file.indexBlock] = 1;
    for (int i = 0; i < file.blockCount; i++) {
        blockMap[file.blocks[i]] = 1;
    }

    files[*fileCount] = file;
    (*fileCount)++;
    printf("Indexed file allocated successfully.\n");
}

// Function to display sequential files
void displaySequentialFiles(struct SequentialFile files[], int fileCount) {
    printf("\nSequential Files:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("File: %s, Start Block: %d, Length: %d\n", files[i].name, files[i].startBlock, files[i].length);
    }
}

// Function to display indexed files
void displayIndexedFiles(struct IndexedFile files[], int fileCount) {
    printf("\nIndexed Files:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("File: %s, Index Block: %d, Blocks: ", files[i].name, files[i].indexBlock);
        for (int j = 0; j < files[i].blockCount; j++) {
            printf("%d ", files[i].blocks[j]);
        }
        printf("\n");
    }
}