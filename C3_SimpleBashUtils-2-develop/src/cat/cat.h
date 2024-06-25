#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cat_flag {
  int b;
  int n;
  int e;
  int s;
  int t;
  int T;
  int E;
  int v;
  int fl;
};

void read_file(FILE *file, char *output_str, long file_size);
void parse_flag(struct cat_flag *flag, int argc, char **argv);
int flag_emptylines(struct cat_flag *flag, FILE *file, int count);

#endif  // CAT_H