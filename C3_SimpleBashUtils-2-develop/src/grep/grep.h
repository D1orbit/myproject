#ifndef GREP_H
#define GREP_H

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct grep_flag {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int o;
  int h;
  int f;
  int s;
  int more;
  bool prov;
  char *filename;
};

void parse_flag(struct grep_flag *flag, int argc, char **argv);
void grep_file(FILE *file, regex_t *regex, struct grep_flag *flag);
void grep(int argc, char **argv, struct grep_flag *flag, int count_file);
void grep_Eprint(FILE *file, char **regex, struct grep_flag *flag,
                 int count_regex);
void grep_F(FILE *file, char **regex, struct grep_flag *flag);

#endif  // GREP_H