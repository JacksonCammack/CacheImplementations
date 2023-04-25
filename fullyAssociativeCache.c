#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 32

// structure definition
typedef struct Cache Cache;
// structure
struct Cache{
    int isValid;
    int key;
};

int main() {
    // Variables to track total hits/accesses
    int hits = 0, accesses = 0;
    // File pointer to read input from traces.txt
    FILE* fp = fopen("traces.txt", "r");

    // Line to take input from file
    char line[256];

    struct Cache cache[CACHE_SIZE];

    // Initialize cache
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].isValid = 0;
        cache[i].key = 0;
    }
    // Scan input into line
    while (fgets(line, sizeof(line), fp)) {
	// turn string into int
        int addr = atoi(line);

        // flag to determine hit
        int hit = 0;
        for (int i = 0; i < CACHE_SIZE; i++) {
            if (cache[i].isValid && cache[i].key == addr) {
                hit = 1;
		// Increment number of hits
                hits++;
                break;
            }
        }

        // Cache miss
        if (!hit) {
            int idx = -1;
            for (int i = 0; i < CACHE_SIZE; i++) {
                if (!cache[i].isValid) {
                    idx = i;
                    break;
                }
            }

            // remove LRU if no empty space
            if (idx == -1) {
                int lruIdx = 0;
                int lruTime = cache[0].key;
                for (int i = 1; i < CACHE_SIZE; i++) {
                    if (cache[i].key < lruTime) {
                        lruIdx = i;
                        lruTime = cache[i].key;
                    }
                }
                idx = lruIdx;
            }

            // Add address
            cache[idx].isValid = 1;
            cache[idx].key = addr;
        }
	// Increment total accesses
        accesses++;
    }
    fclose(fp);

    // Print results
    printf("Accesses: %d\n", accesses);
    printf("Hits: %d\n", hits);
    printf("Hit rate: %.2f%%\n", ((float)hits / accesses) * 100);

    return 0;
}

