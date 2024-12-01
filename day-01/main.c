#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Running list distance calculator\n");

  FILE *file_ptr;
  char ch;
  file_ptr = fopen("./input.csv", "r");

  if (NULL == file_ptr) {
    printf("Failed to open file\n");
    return 1;
  }

  printf("File opened successfully");

  while ((ch = fgetc(file_ptr)) != EOF) {
    printf("%c", ch);
  }

  fclose(file_ptr);
  return 0;
}
