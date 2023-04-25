#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 32
#define BLOCK_SIZE 4
#define SETS (32/4)

// Structure defintion
typedef struct Cache Cache;
// Cache structure
struct Cache{
    unsigned int key;
    int lruCount;
};

struct Cache cache[SETS];
// Function prototypes
void initializeCache();
int accessCache(unsigned int addr);

/* Driver Function */
int main() {
        // Variable to keep track of total hits and accesses
    int hits = 0, accesses = 0;
        // Unsigned int for address
    unsigned int addr;
        // initialize the cache
    initializeCache();

    // File pointer to read input from traces
    FILE* fp = fopen("traces.txt", "r");
    while (fscanf(fp, "%x", &addr) != EOF) {
        accesses++;
        hits += accessCache(addr);
    }
    fclose(fp);

    double hit_rate = (double) hits / accesses;
        printf("Hits: %d \n", hits);
        printf("Accesses: %d \n", accesses);
        printf("Hit rate: %f\n", hit_rate);

    return 0;
}
/* Helper Function to intialize cache */	
void initializeCache() {
    // Loop over sets 
    for (int i = 0; i < SETS; i++) {
        cache[i].key = 0;
        cache[i].lruCount = 0;
    }
}

int accessCache(unsigned int addr) {
	// Variabel to keep track of cache index
    int idx = (addr/BLOCK_SIZE) % SETS;
    unsigned int key = addr/(SETS * BLOCK_SIZE);
	// Cache hits
    if (cache[idx].key == key) {
        // Increment LRU counter and return 1
        cache[idx].lruCount++;
        return 1;
	// Cache missed
    } else {
        // Set old key to new
        cache[idx].key = key;
	// reset LRU count
        cache[idx].lruCount = 0;
        return 0;
    }
}

