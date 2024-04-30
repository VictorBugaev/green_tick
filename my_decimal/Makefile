all: gcov_report
clean:
	rm -rf test test_sharp test_sscanf test_sprintf *.o *.a *.gcno *.html *.gcda
	rm -rf lcov_report lcov_report.info
clang_test:
	clang-format -n -style=Google *.c *.h */*.c

my_decimal.o:
	gcc -c -Wall -Wextra -Werror -std=c11 *.c

my_decimal.a: my_decimal.o
	ar rc my_decimal.a *.o
	ranlib my_decimal.a

test:
	gcc -Wall -Wextra -Werror -o test *.c tests/*.c --coverage -lcheck -lm -lpthread -lsubunit 
	 ./test

gcov_report: test
	gcovr --html >> report.html
	xdg-open report.html

lcov_report:test
	lcov -t "lcov_report" -o lcov_report.info -c -d . 
	genhtml -o lcov_report lcov_report.info