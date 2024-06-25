#include "cat.h"

void test_n() {
  system("cat -n test.txt > test1.txt");
  system("./s21_cat -n test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -n: SUCCESS\n");
  } else {
    printf("flag -n: FAIL\n");
  }
  fclose(file);
}

void test_e() {
  system("cat -e test.txt > test1.txt");
  system("./s21_cat -e test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -e: SUCCESS\n");
  } else {
    printf("flag -e: FAIL\n");
  }
  fclose(file);
}

void test_b() {
  system("cat -b test.txt > test1.txt");
  system("./s21_cat -b test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -b: SUCCESS\n");
  } else {
    printf("flag -b: FAIL\n");
  }
  fclose(file);
}

void test_s() {
  system("cat -s test.txt > test1.txt");
  system("./s21_cat -s test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -s: SUCCESS\n");
  } else {
    printf("flag -s: FAIL\n");
  }
  fclose(file);
}

void test_t() {
  system("cat -t test.txt > test1.txt");
  system("./s21_cat -t test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -t: SUCCESS\n");
  } else {
    printf("flag -t: FAIL\n");
  }
  fclose(file);
}

void test_v() {
  system("cat -v test.txt > test1.txt");
  system("./s21_cat -v test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -v: SUCCESS\n");
  } else {
    printf("flag -v: FAIL\n");
  }
  fclose(file);
}

void test_morefiles() {
  system("cat -n test.txt test.txt > test1.txt");
  system("./s21_cat -n test.txt test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("more files: SUCCESS\n");
  } else {
    printf("more files: FAIL\n");
  }
  fclose(file);
}

int main() {
#ifdef FLAG_N
  test_n();
#endif
#ifdef FLAG_E
  test_e();
#endif
#ifdef FLAG_B
  test_b();
#endif
#ifdef FLAG_S
  test_s();
#endif
#ifdef FLAG_T
  test_t();
#endif
#ifdef FLAG_V
  test_v();
#endif
#ifdef MORE_FILES
  test_morefiles();
#endif
  return 0;
}