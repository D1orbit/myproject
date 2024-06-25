#include "cat.h"

void read_file(FILE *file, char *output_str, long file_size) {
  fread(output_str, file_size, 1, file);
  output_str[file_size] = '\0';
}

void parse_flag(struct cat_flag *flag, int argc, char **argv) {
  const char *short_options = "bnestETv";
  const struct option long_option[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};
  int res = 0;
  int option_index = -1;
  while ((res = getopt_long(argc, argv, short_options, long_option,
                            &option_index)) != -1) {
    if (option_index >= 0) {
      res = long_option[option_index].val;
    }
    option_index = -1;
    switch (res) {
      case 'b':
        flag->b = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'E':
        flag->E = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'T':
        flag->T = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      default:
        printf("flag doesnt exist");
        break;
    }
  }
}

int flag_emptylines(struct cat_flag *flag, FILE *file, int count) {
  int flag_s = 0;
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);
  char *read_str = NULL;
  read_str = (char *)malloc(file_size + 1);
  read_file(file, read_str, file_size);
  int prev = '\n';
  for (long i = 0; i < file_size; i++) {
    while (flag->fl > 1) {
      if (read_str[i] == '\n') {
        flag->fl = 1;
      }
      printf("%c", read_str[i]);
      prev = read_str[i];
      i++;
    }
    if (((prev == '\n' && read_str[i] == '\n') ||
         (i == 0 && read_str[i] == '\n' && read_str[i + 1] == '\n')) &&
        flag->s == 1) {
      flag_s = 1;
      continue;
    }
    if (flag_s == 1) {
      i--;
      flag_s = 0;
    }
    if (((flag->n == 1 && flag->b == 0) ||
         (flag->b == 1 && read_str[i] != '\n')) &&
        (prev == '\n' || i == 0)) {
      printf("%6d\t", count);
      count++;
    }
    if ((flag->E == 1 || flag->e == 1) && read_str[i] == '\n') {
      printf("$");
    }
    if ((flag->T == 1 || flag->t == 1) && read_str[i] == '\t') {
      printf("^I");
      continue;
    }
    if (flag->v && read_str[i] >= 0 && read_str[i] <= 31 &&
        read_str[i] != '\n' && read_str[i] != '\t') {
      printf("^");
      continue;
    }
    printf("%c", read_str[i]);
    prev = read_str[i];
  }
  flag->fl++;
  free(read_str);
  return count;
}