all: s21_grep test

test: grep.o
	gcc -Wall -Wextra -Werror grep.o grep_test.c -DFLAG_E -DFLAG_I -DFLAG_V -DFLAG_C -DFLAG_L -DFLAG_N -DFLAG_H -DFLAG_S -DFLAG_F -DFLAG_O -o test

s21_grep: grep.o
	gcc -Wall -Wextra -Werror grep.o s21_grep.c -o s21_grep

grep.o: grep.c
	gcc -c grep.c

clean:
	rm -rf *.o s21_grep test test1.txt test2.txt

rebuild: clean all