#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define MAX_WORD_SIZE 50

// Structure to hold key-value pairs
typedef struct {
    char word[MAX_WORD_SIZE];
    int count;
} KeyValuePair;

// Function prototypes
void map(FILE *file, KeyValuePair **pairs, int *num_pairs);
void reduce(KeyValuePair **pairs, int num_pairs);
void count_words_loop(FILE *file, KeyValuePair **pairs, int *num_pairs);

int main() {
    FILE *file;
    char *filename = "F:/ds2024/Prac_4_bonus/large_text.txt";
    KeyValuePair *pairs_mapreduce = NULL;
    KeyValuePair *pairs_loop = NULL;
    int num_pairs_mapreduce = 0;
    int num_pairs_loop = 0;
    clock_t start, end;
    double cpu_time_used_mapreduce, cpu_time_used_loop;

    // MapReduce implementation
    start = clock();
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    map(file, &pairs_mapreduce, &num_pairs_mapreduce);
    fclose(file);
    reduce(&pairs_mapreduce, num_pairs_mapreduce);
    end = clock();
    cpu_time_used_mapreduce = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Loop implementation
    start = clock();
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    count_words_loop(file, &pairs_loop, &num_pairs_loop);
    fclose(file);
    end = clock();
    cpu_time_used_loop = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Printing results
    printf("MapReduce Implementation:\n");
    for (int i = 0; i < num_pairs_mapreduce; i++) {
        printf("%s: %d\n", pairs_mapreduce[i].word, pairs_mapreduce[i].count);
    }
    printf("Time taken for MapReduce implementation: %lf seconds\n", cpu_time_used_mapreduce);

    printf("\nLoop Implementation:\n");
    for (int i = 0; i < num_pairs_loop; i++) {
        printf("%s: %d\n", pairs_loop[i].word, pairs_loop[i].count);
    }
    printf("Time taken for Loop implementation: %lf seconds\n", cpu_time_used_loop);

    // Free memory
    free(pairs_mapreduce);
    free(pairs_loop);

    return 0;
}

// Function to map words to key-value pairs
void map(FILE *file, KeyValuePair **pairs, int *num_pairs) {
    char buffer[BUFFER_SIZE];
    *num_pairs = 0;
    *pairs = malloc(sizeof(KeyValuePair));
    if (*pairs == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    while (fscanf(file, "%s", buffer) == 1) {
        int found = 0;
        // Convert word to lowercase
        for (int i = 0; buffer[i]; i++) {
            buffer[i] = tolower(buffer[i]);
        }
        // Check if word already exists in pairs, if yes, increment count
        for (int i = 0; i < *num_pairs; i++) {
            if (strcmp((*pairs)[i].word, buffer) == 0) {
                (*pairs)[i].count++;
                found = 1;
                break;
            }
        }
        // If word is not found, add it to pairs
        if (!found) {
            (*pairs)[*num_pairs].count = 1;
            strcpy((*pairs)[*num_pairs].word, buffer);
            (*num_pairs)++;
            *pairs = realloc(*pairs, (*num_pairs + 1) * sizeof(KeyValuePair));
            if (*pairs == NULL) {
                fprintf(stderr, "Memory reallocation failed.\n");
                exit(1);
            }
        }
    }
}

// Function to reduce key-value pairs
void reduce(KeyValuePair **pairs, int num_pairs) {
    // No need to reduce in this case
    // Could be implemented for more complex tasks
}

// Function to count words using a simple loop
void count_words_loop(FILE *file, KeyValuePair **pairs, int *num_pairs) {
    char buffer[BUFFER_SIZE];
    *num_pairs = 0;
    *pairs = malloc(sizeof(KeyValuePair));
    if (*pairs == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    while (fscanf(file, "%s", buffer) == 1) {
        int found = 0;
        // Convert word to lowercase
        for (int i = 0; buffer[i]; i++) {
            buffer[i] = tolower(buffer[i]);
        }
        // Check if word already exists in pairs, if yes, increment count
        for (int i = 0; i < *num_pairs; i++) {
            if (strcmp((*pairs)[i].word, buffer) == 0) {
                (*pairs)[i].count++;
                found = 1;
                break;
            }
        }
        // If word is not found, add it to pairs
        if (!found) {
            (*pairs)[*num_pairs].count = 1;
            strcpy((*pairs)[*num_pairs].word, buffer);
            (*num_pairs)++;
            *pairs = realloc(*pairs, (*num_pairs + 1) * sizeof(KeyValuePair));
            if (*pairs == NULL) {
                fprintf(stderr, "Memory reallocation failed.\n");
                exit(1);
            }
        }
    }
}
