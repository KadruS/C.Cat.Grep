#include "parser.h"

int parser(int argc, char *argv[], struct Flags *flags) {
  int option = 0;
  int counter = 1;

  flags->regex_flag |= REG_NEWLINE;

  while ((option = getopt(argc, argv, "ivclnhsf:oe:")) != -1) {
    switch (option) {
      case 'e':
        FlagFnE(flags);
        break;
      case 'i':
        flags->i = 1;
        flags->regex_flag |= REG_ICASE;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        FlagFnF(flags);
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        counter = -1;
    }
    if (counter == -1) return counter;
  }
  counter = optind;

  if (flags->combined != NULL && strlen(flags->combined) > 0) {
    flags->combined[strlen(flags->combined) - 1] = '\0';
  }

  return counter;
}

int FlagFnE(struct Flags *flags) {
  flags->e = 1;
  flags->regex_flag |= REG_EXTENDED;

  strcat(flags->combined, optarg);
  strcat(flags->combined, "|");
  strcat(flags->combined, "\0");
  return 0;
}

int FlagFnF(struct Flags *flags) {
  FILE *file = fopen(optarg, "r");
  if (errno) {
    fprintf(stderr, "%s: ", "./s21_grep");
    perror(optarg);
    exit(1);
  }

  char *line = 0;
  size_t length = 0;

  while (getline(&line, &length, file) > 0) {
    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';
    }

    if (strlen(line) > 1) {
      strcat(flags->combined, line);
      strcat(flags->combined, "|");
    }
  }
  free(line);
  strcat(flags->combined, "\0");

  flags->f = 1;
  flags->regex_flag |= REG_EXTENDED;

  fclose(file);
  return 0;
}