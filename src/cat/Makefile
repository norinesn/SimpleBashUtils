СС = gcc
ССflag = -Wextra -Werror -Wall -std=c11

all:clean main

main: s21_cat

s21_cat: s21_cat.c
	$(СС) $(ССflag) s21_cat.c -o s21_cat 

test: rebuild
	rm -rf 1.txt 2.txt 3.txt
	touch  1.txt 2.txt 3.txt
	echo "tp.\n\n\ntbtbtbg\n\n\n34gabgj\n" >>1.txt
	echo "	It was an ordinary grey autumn day in 1993.\n You came home from work at Hewlett-Packard, feeling a little tired.\n You lived in a small two-bedroom apartment on the outskirts of N town.\n" >>3.txt
	chmod +x test_cat.sh
	bash test_cat.sh

clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

cpp:
	cppcheck *.c

valgrind:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -b 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -e 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -n 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -s 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -t 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -v 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -E 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -T 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --number-nonblank 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --number 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --squeeze-blank 1.txt 2.txt 3.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -b 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -e 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -n 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -s 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -t 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -v 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -E 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -T 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --number-nonblank 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --number 1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --squeeze-blank 1.txt
	
clean:
	rm -rf s21_cat
	rm -rf ffile.txt 1.txt 2.txt 3.txt

rebuild:clean all
