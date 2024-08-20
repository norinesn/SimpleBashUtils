#ifndef S21_GREP_H
#define S21_GREP_H

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool pattern;  // e - шаблон
  int noregistr;  // i - игнор прописные и строчные буквы
  bool invert;  // v - инвертировать совпадения
  bool count;  // c - вывод количества совпадающих строк
  bool filesMatch;  // l - выводить только соответствующие файлы
  bool numberLine;  // n - перед каждой совпадающей строкой укажите номер строки
  bool noFilename;  // h - не начинать вывод с имени файла
  bool noPrintErr;  // s - не показывать сообщения об ошибках
  bool fFile;         // f - брать шаблон из файла
  bool printMayched;  // o - выведите совпавшие части совпадающей строки
} Flags;

Flags GrepReadFlags(int argc, char *argv[]);
void GrepFile(FILE *file, char *filename, Flags flags, regex_t *preg,
              int count_f);
void GrepRegexflag(int argc, char *argv[], Flags flags);
void GrepFlag_c(FILE *file, char *filename, int count_f, Flags flags,
                regex_t *preg);
void GrepFlag_l(FILE *file, Flags flags, char *filename, regex_t *preg);
void GrepFlag_n(FILE *file, char *filename, Flags flags, regex_t *preg,
                int count_f);
void GrepFlag_h(FILE *file, Flags flags, regex_t *preg);
void GrepFlag_o(FILE *file, char *filename, Flags flags, regex_t *preg,
                int count_f, char *pattern);
void GrepReadPatternFromFileF(int argc, FILE *f, char *filename, char *argv[],
                              Flags flags, int count_f);
void Grep(int argc, char *argv[], Flags flags);
#endif