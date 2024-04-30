Flags 			= -Werror -Wall -Wextra -std=c11
gcc 			= gcc $(Flags)

all: my_math.o my_math.a
clean:
	rm -rf test test_sharp test_sscanf test_sprintf *.o *.a *.gcno *.html *.gcda
	rm -rf lcov_report lcov_report.info
clang_test:
	clang-format -n -style=Google *.c *.h */*.c

my_math.o:
	$(gcc) -c -I ./ Functions/*.c

my_math.a: my_math.o
	ar rc my_math.a *.o
	ranlib my_math.a

test:
	$(gcc) -o test my_math_test.c -I ./ Functions/*.c --coverage -lcheck -lm -lpthread -lsubunit 
	 ./test

gcov_report: test
	gcovr --html >> report.html

lcov_report:test
	lcov -t "lcov_report" -o lcov_report.info -c -d . 
	genhtml -o lcov_report lcov_report.info