#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Flags flags = GrepReadFlags(argc, argv);
  if (flags.pattern) {
    GrepRegexflag(argc, argv, flags);
  } else {
    Grep(argc, argv, flags);
  }
  return 0;
}

Flags GrepReadFlags(int argc, char *argv[]) {
  Flags flags = {false, 0,     false, false, false,
                 false, false, false, false, false};
  for (int currentFlag = getopt(argc, argv, "eivclnhsfo"); currentFlag != -1;
       currentFlag = getopt(argc, argv, "eivclnhsfo")) {
    switch (currentFlag) {
      case 'e':
        flags.pattern = true;
        break;
      case 'i':
        flags.noregistr |= REG_ICASE;  // передаем в regexec
        break;
      case 'v':
        flags.invert = true;
        break;
      case 'c':
        flags.count = true;
        break;
      case 'l':
        flags.filesMatch = true;
        break;
      case 'n':
        flags.numberLine = true;
        break;
      case 'h':
        flags.noFilename = true;
        break;
      case 'o':
        flags.printMayched = true;
        break;
      case 's':
        flags.noPrintErr = true;
        break;
      case 'f':
        flags.fFile = true;
        break;
    }
  }
  return flags;
}

void GrepRegexflag(int argc, char *argv[], Flags flags) {
  char filename[256][256] = {""};
  char patternsE[256][256] = {""};
  int count_P = 0, count_f = 0;
  for (int i = 0; i < argc; i++) {  // создаем массив с паттернами Е
    if (strcmp(argv[i], "-e") == 0) {
      strcpy(patternsE[count_P], argv[i] + 3);
      count_P++;
    }
  }
  for (int i = 1; i < argc; i++) {  // находим имена и количество файлов
    if (strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "-v") != 0 &&
        strcmp(argv[i], "-ev") != 0 && strcmp(argv[i], "-ve") != 0) {
      int check = 0;
      for (int j = 0; j < count_P; j++) {
        if (strcmp(argv[i], patternsE[j]) == 0) check = 1;
      }
      if (check == 0) {
        strcpy(filename[count_f], argv[i]);
        count_f++;
      }
    }
  }
  for (int f = 0; f < count_f; f++) {
    for (int p = 0; p < count_P; p++) {
      FILE *file;
      file = fopen(filename[f], "r");
      if (file != NULL) {
        regex_t preg;
        regcomp(&preg, patternsE[p], flags.noregistr);
        GrepFile(file, filename[f], flags, &preg, count_f);
        regfree(&preg);
        fclose(file);
      } else {
        if (!flags.noPrintErr)
          printf("grep: %s: No such file or directory\n", *filename);
      }
    }
  }
}

void GrepFile(FILE *file, char *filename, Flags myFlag, regex_t *preg,
              int count_f) {
  char line[1024] = "";
  while (fgets(line, 1024, file)) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    if (myFlag.invert) {
      if (count_f == 1) {
        if (regexec(preg, line, 0, NULL, 0)) printf("%s\n", line);
      } else {
        if (regexec(preg, line, 0, NULL, 0)) printf("%s:%s\n", filename, line);
      }
    } else {
      if (count_f == 1) {
        if (!regexec(preg, line, 0, NULL, 0)) printf("%s\n", line);
      } else {
        if (!regexec(preg, line, 0, NULL, 0)) printf("%s:%s\n", filename, line);
      }
    }
  }
}

void GrepFlag_c(FILE *file, char *filename, int count_f, Flags flags,
                regex_t *preg) {  // флаг с - вывод количества совпадающих строк
  char line[1024] = "";
  int count = 0;
  while (fgets(line, 1024, file)) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    if (!flags.invert) {
      if (!regexec(preg, line, 0, NULL, 0)) count++;
    } else {
      if (regexec(preg, line, 0, NULL, 0)) count++;
    }
  }
  if (count_f > 1)
    printf("%s:%d\n", filename, count);
  else
    printf("%d\n", count);
}

void GrepFlag_l(FILE *file, Flags flags, char *filename,
                regex_t *preg) {  // l - выводить только соответствующие файлы
  char line[1024] = "";  //записываем читаемую строку
  int count = 0;         // счетчик файлов
  regmatch_t match;  //структурный тип где хранится начало и конец части строки
                     //где было совпадение
  while (fgets(line, 1024, file)) {
    if (line[strlen(line) - 1] == '\n')  //меняем перенос строки на конец строки
      line[strlen(line) - 1] = '\0';
    if (flags.invert) {  // флаг v
      if (regexec(preg, line, 1, &match,
                  0)) {  //скомпилированный шаблон, куда, кол-во шаблонов,
                         //массив смещений, eflags
        if (count < 1) {  //печатаем 1 раз
          printf("%s\n", filename);
          count++;
        }
      }
    } else {  //без флага v
      if (!regexec(preg, line, 1, &match, 0)) {
        if (count < 1) {
          printf("%s\n", filename);
          count++;
        }
      }
    }
  }
}

void GrepFlag_n(
    FILE *file, char *filename, Flags flags, regex_t *preg,
    int count_f) {  // n - перед каждой совпадающей строкой укажите номер строки
  char line[1024] = "";
  int countLine = 0;  // счетчик строк
  regmatch_t match;
  while (fgets(line, 1024, file)) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    countLine++;
    if (flags.invert) {
      if (regexec(preg, line, 1, &match, 0)) {
        if (count_f ==
            1)  // eсли 1 файл, то не печаем имя файла, если больше, то печатаем
          printf("%d:%s\n", countLine, line);
        else
          printf("%s:%d:%s\n", filename, countLine, line);
      }
    } else {
      if (!regexec(preg, line, 1, &match, 0)) {
        if (count_f == 1)
          printf("%d:%s\n", countLine, line);
        else
          printf("%s:%d:%s\n", filename, countLine, line);
      }
    }
  }
}

void GrepFlag_h(FILE *file, Flags flags,
                regex_t *preg) {  // h - не начинать вывод с имени файла
  char line[1024] = "";
  regmatch_t match;
  while (fgets(line, 1024, file)) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    if (flags.invert) {
      if (regexec(preg, line, 1, &match, 0)) printf("%s\n", line);
    } else {
      if (!regexec(preg, line, 1, &match, 0)) printf("%s\n", line);
    }
  }
}

void GrepFlag_o(
    FILE *file, char *filename, Flags flags, regex_t *preg, int count_f,
    char *pattern) {  // o - выведите совпавшие части совпадающей строки
  char line[1024] = "";
  regmatch_t match;
  while (fgets(line, 1024, file)) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    if (flags.invert) {
      if (regexec(preg, line, 0, NULL, 0)) {
        if (count_f == 1) {
          printf("%s\n", pattern);
        } else {
          printf("%s:%s\n", filename, pattern);
        }
      }
    } else {
      if (!regexec(preg, line, 1, &match, 0)) {
        if (count_f ==
            1) {  // если 1 файл то только шаблон, если больше то +имя файла
          printf("%s\n", pattern);
        } else {
          printf("%s:%s\n", filename, pattern);
        }
      }
    }
  }
}

void GrepReadPatternFromFileF(int argc, FILE *f, char *filename, char *argv[],
                              Flags flags,
                              int count_f) {  //чтение флага из файла
  char filenameF[100] = {" "};
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0) strcpy(filenameF, argv[i + 1]);
  }
  FILE *filePattern;
  filePattern = fopen(filenameF, "r");
  if (filePattern != NULL) {
    char patternFromFile[1024] = "";
    char patternsF[1024][1024] = {""};
    int countPatF = 0;
    while (fgets(patternFromFile, 1024, filePattern)) {
      if (patternFromFile[strlen(patternFromFile) - 1] == '\n')
        patternFromFile[strlen(patternFromFile) - 1] = '\0';
      strcpy(patternsF[countPatF], patternFromFile);
      countPatF++;
    }
    fclose(filePattern);
    char line[1024] = "";
    while (fgets(line, 1024, f)) {
      int check = 0;
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
      for (int i = 0; i < countPatF && check == false; i++) {
        regex_t regex;
        if (!regcomp(&regex, patternsF[i], flags.noregistr)) {
          if (flags.invert ? regexec(&regex, line, 0, NULL, 0)
                           : !regexec(&regex, line, 0, NULL, 0)) {
            check = 1;
            count_f == 1 ? printf("%s\n", line)
                         : printf("%s:%s\n", filename, line);
          }
          regfree(&regex);
        }
      }
    }
  } else {
    if (flags.noPrintErr)
      printf("grep: %s: No such file or directory\n", filenameF);
  }
}

void Grep(int argc, char *argv[], Flags flags) {
  char **pattern = &argv[1];
  char **end = &argv[argc];
  regex_t preg;
  int count_f = 0;
  for (; pattern != end && pattern[0][0] == '-'; ++pattern)
    ;

  if (pattern == end) {
    if (!flags.noPrintErr) printf("no pattrn\n");
  } else {
    if (regcomp(&preg, *pattern, flags.noregistr)) {
      if (!flags.noPrintErr) printf("failed to cimpile regex\n");
    } else {
      for (char **filename = pattern + 1; filename != end; ++filename) {
        count_f++;
      }
      for (char **filename = pattern + 1; filename != end; ++filename) {
        if (**filename != '-' && !flags.pattern) {
          FILE *f = fopen(*filename, "r");
          if (f == NULL) {
            if (!flags.noPrintErr) {
              printf("grep: %s: No such file or directory\n", *filename);
            }
          } else {
            if (flags.fFile) {
              GrepReadPatternFromFileF(argc, f, *filename, argv, flags,
                                       count_f);
            } else if (flags.filesMatch) {
              GrepFlag_l(f, flags, *filename, &preg);
            } else if (flags.count)
              GrepFlag_c(f, *filename, count_f, flags, &preg);
            else if (flags.noFilename) {
              GrepFlag_h(f, flags, &preg);
            } else if (flags.printMayched) {
              GrepFlag_o(f, *filename, flags, &preg, count_f, *pattern);
            } else if (flags.numberLine) {
              GrepFlag_n(f, *filename, flags, &preg, count_f);
            } else
              GrepFile(f, *filename, flags, &preg, count_f);
            fclose(f);
          }
        }
      }
    }
    regfree(&preg);
  }
}