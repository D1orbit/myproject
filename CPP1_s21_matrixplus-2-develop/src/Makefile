CC=g++
FLAGS = -std=c++17 -Wall -Wextra -Werror
FUNC = *.cpp
FUNC_O = *.o

all: test

s21_matrix_oop.a:
	gcc $(FLAGS) -c $(FUNC)
	ar rc s21_matrix_oop.a $(FUNC_O)
	ranlib s21_matrix_oop.a 

test: clean s21_matrix_oop.a
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(TEST) s21_matrix_oop.a -lgtest -o test
	./test

check:
	cppcheck --enable=all --suppress=missingIncludeSystem .

linters: 
	# cp ../materials/linters/clang-format .
	clang-format -i *.cpp *.h
	#rm clang-format

linters_check:
	clang-format -n *.cpp *.h

clean:
	rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda test matrix_oop 