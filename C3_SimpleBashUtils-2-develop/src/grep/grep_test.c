#include "grep.h"

void test_e() {
  system("grep -e test -e 23 test.txt > test1.txt");
  system("./s21_grep -e test -e 23 test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -e: SUCCESS\n");
  } else {
    printf("flag -e: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

void test_i() {
  system("grep -i test test.txt > test1.txt");
  system("./s21_grep -i test test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -i: SUCCESS\n");
  } else {
    printf("flag -i: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

void test_v() {
  system("grep -v test test.txt > test1.txt");
  system("./s21_grep -v test test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -v: SUCCESS\n");
  } else {
    printf("flag -v: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

void test_c() {
  system("grep -c test test.txt > test1.txt");
  system("./s21_grep -c test test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -c: SUCCESS\n");
  } else {
    printf("flag -c: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

void test_l() {
  system("grep -l 23 *.txt > file1.txt");
  system("./s21_grep -l 23 *.txt > file2.txt");
  system("cmp file1.txt file2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -l: SUCCESS\n");
  } else {
    printf("flag -l: FAIL\n");
  }
  system("rm -f file2.txt file1.txt result.txt");
  fclose(file);
}

void test_n() {
  system("grep -n test test.txt > test1.txt");
  system("./s21_grep -n test test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -n: SUCCESS\n");
  } else {
    printf("flag -n: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

void test_h() {
  system("grep -h test test.txt > test1.txt");
  system("./s21_grep -h test test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -h: SUCCESS\n");
  } else {
    printf("flag -h: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

void test_s() {
  system("grep -s test test.txt > test1.txt");
  system("./s21_grep -s test test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -s: SUCCESS\n");
  } else {
    printf("flag -s: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

void test_f() {
  system("grep -f pattern.txt test.txt > test1.txt");
  system("./s21_grep -f pattern.txt test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -f: SUCCESS\n");
  } else {
    printf("flag -f: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

void test_o() {
  system("grep -o test test.txt > test1.txt");
  system("./s21_grep -o test test.txt > test2.txt");
  system("cmp test1.txt test2.txt > result.txt");
  FILE *file;
  file = fopen("result.txt", "r");
  if (fgetc(file) == EOF) {
    printf("flag -o: SUCCESS\n");
  } else {
    printf("flag -o: FAIL\n");
  }
  system("rm -f test1.txt test2.txt result.txt");
  fclose(file);
}

int main() {
#ifdef FLAG_E
  test_e();
#endif
#ifdef FLAG_I
  test_i();
#endif
#ifdef FLAG_V
  test_v();
#endif
#ifdef FLAG_C
  test_c();
#endif
#ifdef FLAG_L
  test_l();
#endif
#ifdef FLAG_N
  test_n();
#endif
#ifdef FLAG_H
  test_h();
#endif
#ifdef FLAG_S
  test_s();
#endif
#ifdef FLAG_F
  test_f();
#endif
#ifdef FLAG_O
  test_o();
#endif
  return 0;
}