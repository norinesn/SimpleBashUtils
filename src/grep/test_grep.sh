TESTFILE=("1.txt 2.txt 3.txt 4.txt 5.txt")
ONETESTFILE=("1.txt" "2.txt" "3.txt" "4.txt" "5.txt")
FLAGS=("-e" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o")
TWOFLAGS=("-el" "-eo" "-iv" "-vi" "-ic" "-ci" "-il" "-li" "-in" "-ni" "-ih" "-hi" "-is" "-si" "-vc" "-cv" "-vl" "-lv" "-vn" "-nv" "-vh" "-hv" "-vs" "-sv" "-cl" "-lc" "-cn" "-nc" "-cs" "-cs" "-co" "-oc" "-ln" "-lh" "-ls" "-lo" "-ol" "-sl" "-hl" "-nl" "-ns" "-sn" "-so" "-os" "-hs" "-sh")
PATTERN=("test" "text")
TEST = 'test'
TEXT = 'text'

red="$(tput setaf 1)"
green="$(tput setaf 2)"
yellow="$(tput setaf 3)"
white="$(tput setaf 7)"
blue="$(tput setaf 4)"


clear
#проверка флагов по одному во всех файлах 
for flags in "${FLAGS[@]}"
do
for patt in "${PATTERN[@]}"
do
  grep $flag $patt $TESTFILE > grep_result
  ./s21_grep $flag $patt $TESTFILE > s21_result
  difference=$(diff grep_result s21_result)
  ((test_case++))

  if [ ! "$difference"  ]; then
      printf "${green}[SUCCESS]: for all files -flag. Test #$test_case for '$flags' for '$patt' '$TESTFILE'\n"
      ((success_cases++))
    else
      printf "${red}[FAIL]: for all files -flag.  Test #$test_case for  ${yellow}'$flags' for '$patt' '$TESTFILE'\n"
     printf "${white}$difference\n"
    fi
done
done


#проверка флагов по одному в одном файле
for flag in "${FLAGS[@]}"
do
for patt in "${PATTERN[@]}"
do
for file in "${ONETESTFILE[@]}"
do
  grep $flag $patt $ONETESTFILE > grep_result
  ./s21_grep $flag $patt $ONETESTFILE > s21_result
  difference=$(diff grep_result s21_result)
  ((test_case++))

  if [ ! "$difference"  ]; then
      printf "${green}[SUCCESS]: for one files -flag. Test #$test_case for '$flag' for '$patt''$file'\n"
      ((success_cases++))
    else
      printf "${red}[FAIL]: for one files -flag.  Test #$test_case for  ${yellow}'$flag' for '$patt''$file'\n"
     printf "${white}$difference\n"
    fi
done
done
done


#проверка флагов по два во всех файлах
for twoFlags in "${TWOFLAGS[@]}"
do
for patt in "${PATTERN[@]}"
do
  grep $twoFlags $patt $TESTFILE > grep_result
  ./s21_grep $twoFlags $patt $TESTFILE > s21_result
  difference=$(diff grep_result s21_result)
  ((test_case++))

  if [ ! "$difference"  ]; then
      printf "${green}[SUCCESS]: for all files -twoFlags. Test #$test_case for '$twoFlags' for '$patt' '$TESTFILE'\n"
      ((success_cases++))
    else
      printf "${red}[FAIL]: for all files -twoFlags.  Test #$test_case for  ${yellow}'$twoFlags' for '$patt' '$TESTFILE'\n"
     printf "${white}$difference\n"
    fi
done
done


#проверка флагов по два в одном файле

for twoflags in "${TWOFLAGS[@]}"
do
for patt in "${PATTERN[@]}"
do
for file in "${ONETESTFILE[@]}"
do
  grep $twoflags $patt $ONETESTFILE > grep_result
  ./s21_grep $twoflags $patt $ONETESTFILE > s21_result
  difference=$(diff grep_result s21_result)
  ((test_case++))

  if [ ! "$difference"  ]; then
      printf "${green}[SUCCESS]: for one files -twoFlags. Test #$test_case for '$twoFlags' for '$patt' '$file'\n"
      ((success_cases++))
    else
      printf "${red}[FAIL]: for one files -twoFlags.  Test #$test_case for  ${yellow}'$twoFlags' for '$patt' '$file'\n"
     printf "${white}$difference\n"
    fi
done
done
done


#проверка -е шаблон -е шаблон 1.txt
for file in "${ONETESTFILE[@]}"
do
grep -e $TEST -e $TEXT $ONETESTFILE  > grep_result
./s21_grep -e $TEST -e $TEXT $ONETESTFILE  > s21_result
difference=$(diff grep_result s21_result)
((test_case++))

if [ ! "$difference"  ]; then
    printf "${green}[SUCCESS]:for -e pattern -e pattern one files. Test #$test_case for '-e' 'test' '-e' 'text'\n"
    ((success_cases++))
   else
    printf "${red}[FAIL]:for -e pattern -e pattern all one. ${red}Test #$test_case for ${yellow}'-e' 'test' '-e' 'text'\n"
    printf "${white}$difference\n"
fi
done


#проверка -е шаблон -е шаблон все_файлы

grep -e $TEST -e $TEXT $TESTFILE  > grep_result
./s21_grep -e $TEST -e $TEXT $TESTFILE  > s21_result
difference=$(diff grep_result s21_result)
((test_case++))

if [ ! "$difference"  ]; then
    printf "${green}[SUCCESS]:for -e pattern -e pattern all files. Test #$test_case for '-e' 'test' '-e' 'text'\n"
    ((success_cases++))
   else
    printf "${red}[FAIL]:for -e pattern -e pattern all files. ${red}Test #$test_case for ${yellow}'-e' 'test' '-e' 'text'\n"
    printf "${white}$difference\n"
    fi


# проверка -f 1 файл
for file in "${ONETESTFILE[@]}"
do
grep -f ffile.txt $file  > grep_result
./s21_grep -f ffile.txt  $file  > s21_result
difference=$(diff grep_result s21_result)
((test_case++))

if [ ! "$difference"  ]; then
     printf "${green}[SUCCESS]: -f flag for one file. Test #$test_case for '-f' 'ffile.txt' '$file'\n"
    ((success_cases++))
   else
     printf "${red}[FAIL]: -f flag for one file. Test #$test_case for ${yellow}'-f' 'ffile.txt' '$file'\n"
     printf "${white}$difference\n"
fi
done

# проверка -f во всех файлах
grep -f ffile.txt $TESTFILE> grep_result
./s21_grep -f ffile.txt  1.txt 2.txt 3.txt  > s21_result
difference=$(diff grep_result s21_result)
((test_case++))

if [ ! "$difference"  ]; then
     printf "${green}[SUCCESS]: -f flag for all file. Test #$test_case for '-f' 'ffile.txt' '$TESTFILE'\n "
    ((success_cases++))
   else
     printf "${red}[FAIL]: -f flag for all file. Test #$test_case for ${yellow}'-f' 'ffile.txt' '$TESTFILE'\n "
     printf "${white}$difference\n"
fi


# без флагов в нескольких файлах
for patt in "${PATTERN[@]}"
do
grep $patt $TESTFILE  > grep_result
./s21_grep $patt  $TESTFILE  > s21_result
difference=$(diff grep_result s21_result)
((test_case++))

if [ ! "$difference"  ]; then
     printf "${green}[SUCCESS]: for all file no flag. Test #$test_case for 'no flag' '$TESTFILE'\n"
    ((success_cases++))
   else
     printf "${red}[FAIL]: for all file no flag. Test #$test_case for ${yellow}'no flag' '$TESTFILE'\n"
     printf "${white}$difference\n"
fi
done

printf "${blue}Total amount of test cases = $test_case. Success cases = $success_cases\n"