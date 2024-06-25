#include "cat.h"

int main(int argc, char **argv) {
  int count = 1;
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      count++;
    }
  }
  int size = 1;
  struct cat_flag flag = {0, 0, 0, 0, 0, 0, 0, 0, 1};
  parse_flag(&flag, argc, argv);
  for (int i = count; i < argc; i++) {
    FILE *file;
    if ((file = fopen(argv[i], "r")) == NULL) {
      printf("file is not opened");
      break;
    }
    size = flag_emptylines(&flag, file, size);
    fclose(file);
  }
  return 0;
}