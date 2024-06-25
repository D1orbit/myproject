#include "grep.h"

void parse_flag(struct grep_flag *flag, int argc, char **argv) {
  const char *short_options = "eivclnohfs";
  const struct option long_option[] = {{NULL, 0, NULL, 0}};
  int res = 0;
  int option_index = -1;
  while ((res = getopt_long(argc, argv, short_options, long_option,
                            &option_index)) != -1) {
    if (option_index >= 0) {
      res = long_option[option_index].val;
    }
    option_index = -1;
    switch (res) {
      case 'e':
        flag->e = 1;
        flag->prov = true;
        break;
      case 'i':
        flag->i = 1;
        flag->prov = true;
        break;
      case 'v':
        flag->v = 1;
        flag->prov = true;
        break;
      case 'c':
        flag->c = 1;
        flag->prov = true;
        break;
      case 'l':
        flag->l = 1;
        flag->prov = true;
        break;
      case 'n':
        flag->n = 1;
        flag->prov = true;
        break;
      case 'o':
        flag->o = 1;
        flag->prov = true;
        break;
      case 'h':
        flag->h = 1;
        flag->prov = true;
        break;
      case 'f':
        flag->f = 1;
        flag->prov = true;
        break;
      case 's':
        flag->s = 1;
        flag->prov = true;
        break;
      default:
        printf("flag doesnt exist\n");
        break;
    }
  }
}

void grep_Eprint(FILE *file, char **regex, struct grep_flag *flag,
                 int count_regex) {
  int status;
  regex_t preg;
  regex_t *re = &preg;
  char *line = 0;
  size_t length = 0;
  while (getline(&line, &length, file) > 0) {
    for (int i = 0; i < count_regex; i++) {
      if ((status = regcomp(re, regex[i], REG_EXTENDED)) != 0) {
        printf("error");
        continue;
      }
      status = regexec(re, line, 0, NULL, 0);
      if (flag->e == 1 && status == 0 && flag->more > 1) {
        printf("%s:%s", flag->filename, line);
        regfree(re);
        break;
      } else if (flag->e == 1 && status == 0) {
        printf("%s", line);
        regfree(re);
        break;
      }
      regfree(re);
    }
  }
  free(line);
  regfree(re);
}

void grep_F(FILE *file, char **regex, struct grep_flag *flag) {
  int status;
  regex_t preg;
  regex_t *re = &preg;
  char *line = 0;
  size_t length = 0;
  char *line_f = 0;
  size_t length_f = 0;
  while (getline(&line, &length, file) > 0) {
    FILE *file_f;
    if ((file_f = fopen(regex[0], "r")) == NULL) {
      printf("file is not opened");
      break;
    }
    while (getline(&line_f, &length_f, file_f) > 0) {
      if ((status = regcomp(re, line_f, REG_EXTENDED)) != 0) {
        regfree(re);
        printf("error");
        continue;
      }
      status = regexec(re, line, 0, NULL, 0);
      if (flag->f == 1 && status == 0) {
        printf("%s", line);
        regfree(re);
        break;
      }
      regfree(re);
    }
    fclose(file_f);
  }
  free(line_f);
  free(line);
}

void grep_file(FILE *file, regex_t *regex, struct grep_flag *flag) {
  char *line = 0;
  size_t length = 0;
  int count_reg = 0;
  regmatch_t match;
  int str_count = 0;
  bool file_flag = false;
  while (getline(&line, &length, file) > 0) {
    str_count++;
    if (flag->v == 1) {
      if (regexec(regex, line, 1, &match, 0)) {
        if (flag->more == 1) {
          printf("%s:", flag->filename);
        } else if (flag->n == 1) {
          printf("%d:", str_count);
        }
        printf("%s", line);
      }
    } else {
      if (!regexec(regex, line, 1, &match, 0)) {
        count_reg++;
        file_flag = true;
        if (flag->o == 1) {
          int k = match.rm_eo - match.rm_so;
          if (flag->more > 1) {
            printf("%s:", flag->filename);
          }
          printf("%.*s\n", k, line + match.rm_so);
        }
        if (flag->n == 1) {
          if (flag->more > 1) {
            printf("%s:", flag->filename);
          }
          printf("%d:%s", str_count, line);
        }
        if (flag->h == 1 || !flag->prov || flag->s == 1 || flag->i == 1) {
          printf("%s", line);
        }
      }
    }
  }
  if (flag->c == 1) {
    if (flag->more > 1) {
      printf("%s:", flag->filename);
    }
    printf("%d\n", count_reg);
  }
  if (file_flag && flag->l == 1) {
    printf("%s\n", flag->filename);
  }
  free(line);
}

void grep(int argc, char **argv, struct grep_flag *flag, int count_file) {
  regex_t preg;
  regex_t *re = &preg;
  if (argc == 1) {
    printf("no flags or not patterns\n");
  }
  if (flag->f != 1) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
        continue;
      }
      if (flag->i == 1) {
        if (regcomp(re, argv[i], REG_ICASE)) {
          if (errno) {
            if (flag->s == 0) {
              perror("regcomp");
            }
          }
          continue;
        }
      } else {
        if (regcomp(re, argv[i], 0)) {
          printf("failed compile regex");
        }
      }
      for (int j = i + 1; j < argc; j++) {
        if (argv[j][0] == '-') {
          continue;
        }
        if (argc - (i + 1) > 1) {
          flag->more = 1;
        }
        flag->filename = argv[j];
        FILE *file;
        if ((file = fopen(argv[j], "r")) == NULL) {
          if (errno) {
            if (flag->s == 0) {
              perror(argv[j]);
            }
          }
          continue;
        }
        grep_file(file, re, flag);
        fclose(file);
      }
      break;
    }
  }
  regfree(re);
}