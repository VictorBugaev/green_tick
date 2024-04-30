all: gcov_report
clean:
	rm -rf test test_sharp test_sscanf test_sprintf *.o *.a *.gcno *.html *.gcda
	rm -rf lcov_report lcov_report.info
clang_test:
	clang-format -n -style=Google *.c *.h */*.c

my_string.o:
	gcc -c -Wall -Wextra -Werror -std=c11 my_string/*.c my_sprintf/my_sprintf.c my_sscanf/my_sscanf.c

my_string.a: my_string.o
	ar rc my_string.a *.o
	ranlib my_string.a

test:
	gcc -Wall -Wextra -Werror -o test my_string_test.c my_string/*.c --coverage -lcheck -lm -lpthread -lsubunit 
	 ./test

test_sharp: 
	gcc -Wall -Wextra -Werror -o test_sharp my_sharp_tests.c my_string/*.c --coverage -lcheck -lm -lpthread -lsubunit 
	./test_sharp
test_sprintf:
	gcc -Wall -Wextra -Werror -o test_sprintf my_sprintf/my_sprintf_test.c my_sprintf/my_sprintf.c my_string/*.c --coverage -lcheck -lm -lpthread -lsubunit 
	 ./test_sprintf

test_sscanf:
	gcc -Wall -Wextra -Werror my_sscanf/my_sscanf_test.c my_sscanf/my_sscanf.c my_string/*.c -o test_sscanf --coverage -lcheck -lm -lpthread -lsubunit
	./test_sscanf 

gcov_report: test test_sharp test_sscanf test_sprintf
	gcovr --html >> report.html

lcov_report:test test_sharp test_sprintf test_sscanf 
	lcov -t "lcov_report" -o lcov_report.info -c -d . 
	genhtml -o lcov_report lcov_report.info
