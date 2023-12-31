#include "print_file.h"

int print_file(char *argv[], int argc, int counter, struct Flags flags) {
  char *table[256] = {
      "^@",   "^A",   "^B",   "^C",    "^D",   "^E",   "^F",   "^G",   "^H",
      "\t",   "\n",   "^K",   "^L",    "^M",   "^N",   "^O",   "^P",   "^Q",
      "^R",   "^S",   "^T",   "^U",    "^V",   "^W",   "^X",   "^Y",   "^Z",
      "^[",   "^\\",  "^]",   "^^",    "^_",   " ",    "!",    "\"",   "#",
      "$",    "%",    "&",    "'",     "(",    ")",    "*",    "+",    ",",
      "-",    ".",    "/",    "0",     "1",    "2",    "3",    "4",    "5",
      "6",    "7",    "8",    "9",     ":",    ";",    "<",    "=",    ">",
      "?",    "@",    "A",    "B",     "C",    "D",    "E",    "F",    "G",
      "H",    "I",    "J",    "K",     "L",    "M",    "N",    "O",    "P",
      "Q",    "R",    "S",    "T",     "U",    "V",    "W",    "X",    "Y",
      "Z",    "[",    "\\",   "]",     "^",    "_",    "`",    "a",    "b",
      "c",    "d",    "e",    "f",     "g",    "h",    "i",    "j",    "k",
      "l",    "m",    "n",    "o",     "p",    "q",    "r",    "s",    "t",
      "u",    "v",    "w",    "x",     "y",    "z",    "{",    "|",    "}",
      "~",    "^?",   "M-^@", "M-^A",  "M-^B", "M-^C", "M-^D", "M-^E", "M-^F",
      "M-^G", "M-^H", "M-^I", "M-^J",  "M-^K", "M-^L", "M-^M", "M-^N", "M-^O",
      "M-^P", "M-^Q", "M-^R", "M-^S",  "M-^T", "M-^U", "M-^V", "M-^W", "M-^X",
      "M-^Y", "M-^Z", "M-^[", "M-^\\", "M-^]", "M-^^", "M-^_", "M- ",  "M-!",
      "M-\"", "M-#",  "M-$",  "M-%",   "M-&",  "M-'",  "M-(",  "M-)",  "M-*",
      "M-+",  "M-,",  "M--",  "M-.",   "M-/",  "M-0",  "M-1",  "M-2",  "M-3",
      "M-4",  "M-5",  "M-6",  "M-7",   "M-8",  "M-9",  "M-:",  "M-;",  "M-<",
      "M-=",  "M->",  "M-?",  "M-@",   "M-A",  "M-B",  "M-C",  "M-D",  "M-E",
      "M-F",  "M-G",  "M-H",  "M-I",   "M-J",  "M-K",  "M-L",  "M-M",  "M-N",
      "M-O",  "M-P",  "M-Q",  "M-R",   "M-S",  "M-T",  "M-U",  "M-V",  "M-W",
      "M-X",  "M-Y",  "M-Z",  "M-[",   "M-\\", "M-]",  "M-^",  "M-_",  "M-`",
      "M-a",  "M-b",  "M-c",  "M-d",   "M-e",  "M-f",  "M-g",  "M-h",  "M-i",
      "M-j",  "M-k",  "M-l",  "M-m",   "M-n",  "M-o",  "M-p",  "M-q",  "M-r",
      "M-s",  "M-t",  "M-u",  "M-v",   "M-w",  "M-x",  "M-y",  "M-z",  "M-{",
      "M-|",  "M-}",  "M-~",  "M-^?"};

  int prev = '\n';
  int prevPrev = 0;
  int line_counter = 1;

  for (int i = counter; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");

    if (file != NULL) {
      int c = 0;

      while ((c = fgetc(file)) != EOF) {
        if (flags.s && prev == '\n' && c == '\n' && prevPrev == '\n') {
          continue;
        }
        if ((flags.n && prev == '\n') ||
            (flags.b && prev == '\n' && c != '\n')) {
          printf("%6d\t", line_counter++);
        }
        if (flags.e && c == '\n') {
          printf("$");
        }

        prevPrev = prev;
        prev = c;

        if (flags.v) {
          if (flags.t && c == '\t') {
            printf("^I");
          } else {
            printf("%s", table[c]);
          }
          continue;
        }

        if (flags.t && c == '\t') {
          printf("^I");
          continue;
        }

        putc(c, stdout);
      }

      fclose(file);
    } else {
      printf("./s21_cat: %s: No such file or directory\n", argv[i]);
    }
  }
  return 0;
}
