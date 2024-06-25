NAME = s21_string
CC = gcc
CC_FLAGS = -std=c11 -Wall -Wextra -Werror -g
GCOVFLAGS = -L. -ls21_string --coverage
TEST_FLAGS = -std=c11 -g

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck
endif

TEST_COMPILE = $(CC) $(TEST_FLAGS) *.c libs21_string.a $(CHECK_FLAGS) -L. -ls21_string

all: clean s21_string.a

test: s21_string.a
	$(TEST_COMPILE)
	./a.out

s21_string.a: s21_string.o
	ar rcs libs21_string.a *.o
	rm -rf *.o
	ranlib libs21_string.a
	cp libs21_string.a s21_string.a
	cp libs21_string.a ls21_string.a

s21_string.o:
	$(CC) $(CC_FLAGS) -c s21*.c

gcov_report: s21_string.a test
	rm -f *.g*
	$(CC) $(TEST_FLAGS) s21_m*.c s21_s*.c test.c s21_t*.c s21_i*.c libs21_string.a $(CHECK_FLAGS) $(GCOVFLAGS)
	rm -rf a-test.gcda a-test.gcno
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	rm -rf *.gcda *.gcno s21_tests s21_tests.info

clean:
	rm -rf *.o *.g* *.info *.out report *.a

rebuild: clean all