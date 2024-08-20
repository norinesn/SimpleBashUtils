#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {  // typedef чтобы при обращению к элементу структуры не писатьs
                  // truct, перед main чтобы все ф-ции могли к ней обращаться
  bool numberNonBlank;  // b - перечислять только те строки, которые содержат
                        // символы
  bool end;  // e - помечать конец каждой строки $
  bool number;  // n - перечислять все строки, начиная с 1
  bool squeeze;  // s - сжимать несколько последовательных пустых строк в одну
                 // пустую строку.
  bool tab;      // t - отображать символы табуляции
  bool nonPrinting;  // v - преобразует непечатаемые символы в их обозначение
                     // каретки
} Flags;             // имя структуры

Flags CatReadFlags(int argc, char *argv[]);  //считывает флаги cat
void CatSetTable(char *table[256]);          // создали таблицу
void CatFile(FILE *file, Flags flags, char *table[256], int *count);
void catSetNonPrinting(char *table[256]);
void CatSetEnd(char *table[256]);  // для флага е
void CatSetTab(char *table[256]);  // для флага t
void Cat(int argc, char *argv[], Flags flags, char *table[256], int *count);

#endif