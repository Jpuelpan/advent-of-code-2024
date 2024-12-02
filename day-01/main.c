#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 2000

typedef struct {
  int left[MAX_SIZE];
  int right[MAX_SIZE];
  int size;
} LocationsList;

typedef struct {
  int key;
  int value;
} LocationFreq;

int ASC(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void calculate_distance(LocationsList *locations) {
  int total_distance = 0;
  for (size_t i = 0; i < locations->size; i++) {
    int distance = abs(locations->left[i] - locations->right[i]);
    /* printf("%d - %d: %d\n", locations->left[i], locations->right[i],
     * distance); */
    total_distance += distance;
  }

  printf("Total distance is: %d\n", total_distance);
}

void calculate_similarity_score(LocationsList *locations) {
  LocationFreq freq[locations->size];
  for (int i = 0; i < locations->size; i++) {
    freq[i].key = locations->left[i];
    freq[i].value = 0;
  }

  for (int i = 0; i < locations->size; i++) {
    for (int j = 0; j < locations->size; j++) {
      if (locations->right[i] == freq[j].key) {
        freq[j].value++;
        break;
      }
    }
  }

  int similarity_score = 0;
  for (int i = 0; i < locations->size; i++) {
    int score = freq[i].key * freq[i].value;
    /* printf("freq: %d: %d -> %d\n", freq[i].key, freq[i].value, score); */
    similarity_score += score;
  }

  printf("Similarity score: %d\n", similarity_score);
}

int main(int argc, char *argv[]) {
  printf("Advent of code 2024 - Day 1\n");

  FILE *fp;
  char ch;
  fp = fopen("./input.csv", "r");

  if (NULL == fp) {
    printf("Failed to open file\n");
    return 1;
  }

  printf("File opened successfully\n");

  char row[100];
  char *token;

  LocationsList locations;
  locations.size = -1;

  while (feof(fp) == 0) {
    fgets(row, sizeof(row), fp);
    token = strtok(row, ",");

    int i = 0;
    locations.size++;
    while (token != NULL) {
      int num;
      if (sscanf(token, "%d", &num) != 1) {
        printf("Failed to convert number\n");
        return 1;
      }

      if (i == 0) {
        locations.left[locations.size] = num;
      } else {
        locations.right[locations.size] = num;
      }

      i++;
      token = strtok(NULL, ",");
    }

    row[0] = '\0';
  };

  qsort(&locations.left, locations.size, sizeof(int), ASC);
  qsort(&locations.right, locations.size, sizeof(int), ASC);

  calculate_distance(&locations);
  calculate_similarity_score(&locations);

  fclose(fp);
  return 0;
}
