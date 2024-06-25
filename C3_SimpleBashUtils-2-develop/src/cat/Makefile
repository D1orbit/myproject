all: s21_cat test

test: cat.o
	gcc -Wall -Wextra -Werror cat.o cat_test.c -DFLAG_N -DFLAG_E -DFLAG_B -DFLAG_S -DFLAG_T -DMORE_FILES -DFLAG_V -o test

s21_cat: cat.o
	gcc -Wall -Wextra -Werror cat.o s21_cat.c -o s21_cat

cat.o: cat.c
	gcc -Wall -Wextra -Werror -c cat.c

clean:
	rm -rf *.o s21_cat test1.txt test test2.txt result.txt

rebuild: clean all