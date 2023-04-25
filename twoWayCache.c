#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 32
#define SETS 16
#define ASSOCIATIVITY 2

typedef struct Cache Cache;

struct Cache{
    int isValid[ASSOCIATIVITY];
    int key[ASSOCIATIVITY];
};

int main() {
    // Variables to track total hits and accesses
    int hits = 0, accesses = 0;	
    // File pointer to read from traces.txt
    FILE* fp = fopen("traces.txt", "r");
    // Array of chars for input
    char line[256];

    Cache cache[SETS][ASSOCIATIVITY];

    // Initialize cache
    for (int i = 0; i < SETS; i++) {
        for (int j = 0; j < ASSOCIATIVITY; j++) {
            cache[i][j].isValid[j] = 0;
            cache[i][j].key[j] = 0;
        }
    }
	// Scan in key
    while (fgets(line, sizeof(line), fp)) {
	// Convert string to int
        int addr = atoi(line);

        // Calculate cache set and tag
        int set = addr % SETS;
        int key = addr / SETS;

        // Check if cache line has the same key
	// Flag variable
	// 1 if valid key
        int hit = 0;
	// Cache hits
        for (int i = 0; i < ASSOCIATIVITY; i++) {
            if (cache[set][i].isValid[i] && cache[set][i].key[i] == key){
		// Increment total number of hits
                hits++;
                hit = 1;
                break;
            }
        }

        // Cache missed
        if (!hit) {
            int idx;
            if (cache[set][0].isValid[0] && cache[set][1].isValid[1]) {
                // If both lines are valid
                idx = cache[set][0].isValid[0] > cache[set][1].isValid[1] ? 1 : 0;
            } else {
                // else choose other
                idx = cache[set][0].isValid[0] ? 1 : 0;
            }
            cache[set][idx].isValid[idx] = 1;
            cache[set][idx].key[idx] = key;
        }

        accesses++;
    }
    fclose(fp);

    // Print results
    printf("Hits: %d\n", hits);
    printf("Accesses: %d\n", accesses);
    printf("Hit rate: %.2f%%\n", ((float)hits / accesses) * 100);

    return 0;
}

