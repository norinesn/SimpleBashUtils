СС = gcc
ССflagM= -lm -Wextra -Werror -Wall
ССflag= -Wextra -Werror -Wall -std=c11
MuchFlag=-D_GNU_SOURCE -Wextra -Werror -Wall -std=c11
all:clean main


main: s21_grep

s21_grep:
	$(СС) $(ССflag) s21_grep.c -o s21_grep

test: rebuild
	rm -rf ffile.txt 1.txt 2.txt 3.txt 4.txt 5.txt
	touch ffile.txt 1.txt 2.txt 3.txt 4.txt 5.txt
	echo "name\nfirst\n123\nuyt" >>ffile.txt
	echo "text.\n.\ntest\n\n.\text%T\n\ncdcvdtestfvf\nname\n\nhyfirst\nfirst" >>1.txt 
	echo "Text123.\nTesthy\n56Text\n.Test\nNamevfv\nName\nfvfFirst\n\n\nFirst" >>2.txt 
	echo "frfTEXT.\nTEST\n\nvfu vfv\nTEST\n\ntfTEXT\nNAME\nfvfNAME\nFIRST\nfbf\nvgvFIRST" >>3.txt
	echo " " >>4.txt  
	echo "\n\n\n" >>5.txt
	chmod +x test_grep.sh
	bash ./test_grep.sh

clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

cpp:
	cppcheck *.c

valgrind:
	
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -e test 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -i text 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -v test 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -c text 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -l test 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -n text 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -s test 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -h text 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -o test 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -f ffile.txt 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -fv ffile.txt 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -vl text 1.txt 2.txt 3.txt 4.txt 5.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -on cdc 3.txt

clear_terminal:
	clear
clean:
	rm -rf *.a -f
	rm -rf *.o -f
	rm -rf s21_grep
	rm -rf ffile.txt 1.txt 2.txt 3.txt 4.txt 5.txt

rebuild:clean all