####### suzymarg`s variables
TARGET = SmartCalc
FLAGS = -Wall -Wextra -Werror -std=c11
CC = gcc
LFLAGS = -fprofile-arcs -ftest-coverage
SRC := $(wildcard SmartCalc/calculate_func/*.c)
OBJ := $(patsubst SmartCalc/calculate_func/*.c, %.o, $(SRC))
VALGRIND_FLAGS=--leak-check=full
VALGRIND_FLAGS_v2 = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
LINUX_FLAGS=-lcheck -lsubunit -lm -lrt -lpthread
MAC_FLAGS=-lcheck -lm
OS := $(shell uname -s)
########
all: clean s21_smartcalc.a test gcov_report

gcov: gcov_report

test: s21_smartcalc.a
ifeq ($(OS),Linux)
	$(CC) $(FLAGS) $(OBJ) $(LFLAGS)  -o test $(LINUX_FLAGS)
	./test
endif
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(OBJ) $(LFLAGS)  -o test $(MAC_FLAGS)
	./test
endif

gcov_report: test
	gcov check.c
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage-html
	rm -rf *.gcda *.gcno
ifeq ($(OS),Linux)
	xdg-open coverage-html/index.html

else
	open coverage-html/index.html
endif
s21_smartcalc.a: 
	gcc -Wall -Wextra -Werror SmartCalc/calculate_func/*.c -c
	ar rc libs21_smartcalc.a *.o
	ranlib libs21_smartcalc.a
	cp libs21_smartcalc.a ./s21_smartcalc.a
	rm *.o
clean:
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.gcda
	rm -rf *.a
	rm -rf *.info
	rm -rf *.a_check
	rm -rf gcov
	rm -rf coverage
	rm -rf coverage-html
	rm -rf test
	rm -rf memory_test
	rm -rf valgrind.txt
	rm -rf coverage-html obj *.dSYM **/*.dSYM report coverage.info controller_tests_vg.log

stylemake:
	clang-format -style=Google -i SmartCalc/*.c SmartCalc/*.h SmartCalc/*.cpp SmartCalc/calculate_func/*.c 



stylecheck:
	clang-format -style=Google -n SmartCalc/*.c SmartCalc/*.h SmartCalc/*.cpp SmartCalc/calculate_func/*.c


install:
	@echo "Start installation"
	@mkdir -p ../build
	@cd SmartCalc && qmake && make && make clean && rm -rf Makefile && mv SmartCalc ../../build/$(TARGET)
	@cp -R ../build/$(TARGET) ~/Desktop/$(TARGET)
	@echo "Install completed successfully"

uninstall:
	@rm -rf ~/Desktop/SmartCalc ../build
	@echo "Uninstall completed successfully"

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET) ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v1.0.tgz *
	@cd ../dist && rm -rf $(TARGET) README.md README_RUS.md
	@echo "The build was successfully archived"

valgrind: test
	valgrind $(VALGRIND_FLAGS_v2) ./test
	grep -n "ERROR SUMMARY" valgrind.txt