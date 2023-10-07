CC = gcc -Wall -Werror -Wextra -std=c++17 -g
L = -lstdc++ -lgtest -lgtest_main
GCOVF = -fprofile-arcs -ftest-coverage
LF = -lrt -lm -lsubunit -lpthread

OS := $(shell uname)
ifeq ($(OS), Linux)
	UL = $(L) $(LF)
else
	UL = $(L)
endif



all: build

install: unistall
	mkdir build
	cd calculator && qmake && make && make clean && rm -rf Makefile .qmake.stash && mv calculator.app ../build

dvi:
	open dvi.html

test:
	$(CC) tests/*.cc calculator/model/*.cc -o res_test $(UL) -I calculator/model/
	./res_test

leaks: 
	$(CC) tests/*.cc calculator/model/*.cc -o res_test $(UL) -I calculator/model/
	leaks -atExit -- ./res_test

clang_format: clang-format

clang-format: 
	cp ../materials/linters/.clang-format ../src
	clang-format -n calculator/*.cc
	clang-format -n calculator/view/*.h
	clang-format -n calculator/view/*.cc
	clang-format -n calculator/model/*.h
	clang-format -n calculator/model/*.cc
	clang-format -n calculator/controller/*.h
	clang-format -n calculator/controller/*.cc
	clang-format -i calculator/*.cc
	clang-format -i calculator/view/*.h
	clang-format -i calculator/view/*.cc
	clang-format -i calculator/model/*.h
	clang-format -i calculator/model/*.cc
	clang-format -i calculator/controller/*.h
	clang-format -i calculator/controller/*.cc


valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./res_test

docker_check: 
	docker build -t "valgrind:1.0" .
	docker run --rm -v $(PWD):/tmp -w /tmp valgrind:1.0

gcov_report:
	$(GCC) $(GCOVF) tests/*.cc -o res_test $(LIB) -I.
	./res_test
	gcov *.cc
	lcov --capture --directory . --output-file test.info #--ignore-errors mismatch
	genhtml test.info --output-directory report
	open report/index.html

clang_format:
	cp ../materials/linters/.clang-format ../src
	clang-format -n headers/*.h patterns/*.tpp tests/*.cc
	clang-format -i headers/*.h patterns/*.tpp tests/*.cc
	rm -rf .clang-format

build: install

unistall: clean

rebuild: clean build

clear: clean

clean:
	rm -rf *.dSYM *.o *.out
	rm -rf res_test
	rm -rf build*
