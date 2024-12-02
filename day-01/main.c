#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LocationsList {
  int left[1000];
  int right[1000];
  int cur;
};

int ASC(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

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

  struct LocationsList locations;
  locations.cur = -1;

  while (feof(fp) == 0) {
    fgets(row, sizeof(row), fp);
    token = strtok(row, ",");

    int i = 0;
    locations.cur++;
    while (token != NULL) {
      int num;
      if (sscanf(token, "%d", &num) != 1) {
        printf("Failed to convert number\n");
        return 1;
      }

      if (i == 0) {
        locations.left[locations.cur] = num;
      } else {
        locations.right[locations.cur] = num;
      }

      i++;
      token = strtok(NULL, ",");
    }

    row[0] = '\0';
  };

  qsort(&locations.left, locations.cur, sizeof(int), ASC);
  qsort(&locations.right, locations.cur, sizeof(int), ASC);

  int total_distance = 0;
  for (size_t i = 0; i < locations.cur; i++) {
    int distance = abs(locations.left[i] - locations.right[i]);
    printf("%d - %d: %d\n", locations.left[i], locations.right[i], distance);
    total_distance += distance;
  }

  printf("Total distance is: %d\n", total_distance);

  fclose(fp);
  return 0;
}
