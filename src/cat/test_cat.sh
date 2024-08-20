TESTFILE=("1.txt 2.txt 3.txt ")
ONETESTFILE=("3.txt" "1.txt" "2.txt")
FLAGS=("-b" "-e" "-n" "-s" "-t" "-v" "-E" "-T" "--number-nonblank" "--number" "--squeeze-blank" )

red="$(tput setaf 1)"
green="$(tput setaf 2)"
yellow="$(tput setaf 3)"
white="$(tput setaf 7)"
blue="$(tput setaf 4)"


clear

for flag in "${FLAGS[@]}"
do
  cat $flag $TESTFILE > cat_result
  ./s21_cat $flag $TESTFILE > s21_result
  difference=$(diff cat_result s21_result)
  ((test_case++))

  if [ ! "$difference"  ]; then
      printf "${green}[SUCCESS]: for all files -flag. Test #$test_case for '$flag'\n"
      ((success_cases++))
    else
      printf "${red}[FAIL]: for all files -flag.  Test #$test_case for  ${yellow}'$flag'\n"
     printf "${white}$difference\n"
    fi
done


for flag in "${FLAGS[@]}"
do
for file in "${ONETESTFILE[@]}"
do
  cat $flag $ONETESTFILE > cat_result
  ./s21_cat $flag $ONETESTFILE > s21_result
  difference=$(diff cat_result s21_result)
  ((test_case++))

  if [ ! "$difference"  ]; then
      printf "${green}[SUCCESS]: for one files -flag. Test #$test_case for '$flag'\n"
      ((success_cases++))
    else
      printf "${red}[FAIL]: for one files -flag.  Test #$test_case for  ${yellow}'$flag'\n"
     printf "${white}$difference\n"
    fi
done
done

printf "${blue}Total amount of test cases = $test_case. Success cases = $success_cases\n"



 
