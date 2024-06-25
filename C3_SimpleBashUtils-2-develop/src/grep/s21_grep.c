#include "grep.h"

int main(int argc, char **argv) {
  struct grep_flag flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false};
  char *filename[argc - 1];
  char *regex[argc - 1];
  int count_file = 0;
  int count_regex = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      i++;
      regex[count_regex] = argv[i];
      count_regex++;
    } else {
      filename[count_file] = argv[i];
      count_file++;
    }
  }
  parse_flag(&flag, argc, argv);
  argv += optind;
  argc -= optind;
  if (argc == 0) {
    fprintf(stderr, "no pattern\n");
    if (flag.e == 1) {
      free(flag.filename);
    }
    exit(1);
  }
  argv -= optind;
  argc += optind;
  if (flag.e == 1) {
    for (int i = 0; i < count_file; i++) {
      FILE *file;
      flag.more = count_file;
      flag.filename = filename[i];
      if ((file = fopen(filename[i], "r")) == NULL) {
        if (errno) {
          if (flag.s == 0) {
            perror(*filename);
          }
        }
        continue;
      }
      grep_Eprint(file, regex, &flag, count_regex);
      fclose(file);
    }
  } else if (flag.f == 1) {
    for (int i = 0; i < count_file; i++) {
      FILE *file;
      flag.more = count_file;
      flag.filename = filename[i];
      file = fopen(filename[i], "rb");
      if (file == NULL) {
        if (errno) {
          if (flag.s == 0) {
            perror(*filename);
          }
        }
        continue;
      }
      grep_F(file, regex, &flag);
      fclose(file);
    }
  } else {
    grep(argc, argv, &flag, count_file);
  }
  return 0;
}