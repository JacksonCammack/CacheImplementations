#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 32
#define SET 4

// Structure definition
typedef struct Cache Cache;
// Structure
struct Cache{
    int isValid[SET];
    int key[SET];
    int LRUcount;
};

int main() {
    // Variables to track total hits/accesses
    int hits = 0, accesses = 0;
    // File pointer to take input from traces.txt
    FILE * fp = fopen("traces.txt","r");
    // Array of chars for input
    char line[256];
    // Create cache
    Cache cache[32/4];
    
    // Initialize cache
    for (int i = 0; i < CACHE_SIZE / SET; i++) {
        for (int j = 0; j < SET; j++) {
            cache[i].isValid[j] = 0;
            cache[i].key[j] = 0;
        }
        cache[i].LRUcount = 0;
    }
    // Scan input from file
    while (fgets(line, sizeof(line), fp)) {
	// turn string into int
        int addr = atoi(line);

        // Calculate cache set and tag
        int set = (addr / CACHE_SIZE) % (CACHE_SIZE / SET);
        int key = addr / (CACHE_SIZE / SET);
	
        // Turn hit flag to 1 if hit
        int hit = 0;
        for (int i = 0; i < SET; i++) {
            if (cache[set].isValid[i] && cache[set].key[i] == key){
                hit = 1;
                cache[set].LRUcount = i;
                break;
            }
        }
	// Cache hits
        if (hit) {
            hits++;
	// Cache missed
        } else {
            // Replace least recently used cache line
            int LRU = cache[set].LRUcount;
            cache[set].isValid[LRU] = 1;
            cache[set].key[LRU] = key;
            cache[set].LRUcount = (LRU + 1) % SET;
        }
        accesses++;
    }
    fclose(fp);

    // Print results
    printf("Accesses: %d\n", accesses);
    printf("Hits: %d\n", hits);
    printf("Hit rate: %.2f%%\n", ((float)hits / accesses) * 100);

    return 0;
}

