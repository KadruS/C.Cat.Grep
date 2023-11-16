#include "parser.h"

int parser(int argc, char *argv[], struct Flags *flags) {
  int option = 0;
  int counter = 1;
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {NULL, 0, NULL, 0}};

  while ((option = getopt_long(argc, argv, "+benstvET", long_options, NULL)) !=
         -1) {
    switch (option) {
      case 'b':
        flags->b = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'E':
        flags->e = 1;
        break;
      case 'T':
        flags->t = 1;
        break;
      // not sure if needed, error if wrong flag
      default:
        counter = -1;
    }
    // here again error if wrong flag
    if (counter == -1) break;
    counter = optind;
  }

  return counter;
}