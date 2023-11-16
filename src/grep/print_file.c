#include "print_file.h"

int print_file(char *argv[], int argc, struct Flags flags, int counter) {
  char **end = &argv[argc];
  char *pattern = argv[counter];
  int file_counter = argc - counter - 1;

  if (flags.e || flags.f) {
    pattern = flags.combined;
    file_counter = argc - counter--;
  }

  regex_t regex;

  if (regcomp(&regex, pattern, flags.regex_flag)) {
    perror("regex failed!");
    exit(1);
  }

  for (char **filename = &argv[++counter]; filename != end; filename++) {
    FILE *file = fopen(*filename, "r");
    if (errno) {
      if (!flags.s) {
        fprintf(stderr, "%s: ", argv[0]);
        perror(*filename);
      }
      errno = 0;
      continue;
    }
    if (flags.l) {
      GrepFlagL(file, flags, &regex, filename);
    } else if (flags.c) {
      GrepFlagC(file, flags, &regex, filename, file_counter);
    } else if (flags.o) {
      GrepFlagO(file, flags, &regex, filename, file_counter);
    } else {
      grep_from_file(file, flags, &regex, filename, file_counter);
    }
    fclose(file);
  }

  regfree(&regex);
  return 0;
}

int grep_from_file(FILE *file, struct Flags flags, regex_t *regex,
                   char **filename, int file_counter) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  int line_number = 1;

  while (getline(&line, &length, file) > 0) {
    if (!flags.v) {
      if (!regexec(regex, line, 1, &match, 0)) {
        if (file_counter > 1 && !flags.h) {
          printf("%s:", *filename);
          if (flags.n) {
            printf("%d:", line_number);
          }
          printf("%s", line);
        } else {
          if (flags.n) {
            printf("%d:", line_number);
          }
          printf("%s", line);
        }
      }
    } else {
      if (regexec(regex, line, 1, &match, 0)) {
        if (file_counter > 1 && !flags.h) {
          printf("%s:", *filename);
          if (flags.n) {
            printf("%d:", line_number);
          }
          printf("%s", line);
        } else {
          if (flags.n) {
            printf("%d:", line_number);
          }
          printf("%s", line);
        }
      }
    }
    line_number++;
  }

  free(line);
  return 0;
}

int GrepFlagC(FILE *file, struct Flags flags, regex_t *regex, char **filename,
              int file_counter) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;

  int line_counter = 0;

  while (getline(&line, &length, file) > 0) {
    if (!flags.v) {
      if (!regexec(regex, line, 1, &match, 0)) {
        line_counter++;
      }
    } else {
      if (regexec(regex, line, 1, &match, 0)) {
        line_counter++;
      }
    }
  }

  if (file_counter > 1 && !flags.h) {
    printf("%s:%d\n", *filename, line_counter);
  } else {
    printf("%d\n", line_counter);
  }

  free(line);
  return 0;
}

int GrepFlagL(FILE *file, struct Flags flags, regex_t *regex, char **filename) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;

  int is_matched = 0;

  while (getline(&line, &length, file) > 0) {
    if (!flags.v) {
      if (!regexec(regex, line, 1, &match, 0)) {
        is_matched = 1;
      }
    } else {
      if (regexec(regex, line, 1, &match, 0)) {
        is_matched = 1;
      }
    }
  }

  if (is_matched) {
    printf("%s\n", *filename);
  }

  free(line);
  return 0;
}

int GrepFlagO(FILE *file, struct Flags flags, regex_t *regex, char **filename,
              int file_counter) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  int line_number = 1;

  while (getline(&line, &length, file) > 0) {
    int offset = 0;

    if (!flags.v) {
      while (!regexec(regex, line + offset, 1, &match, 0)) {
        if (file_counter > 1 && !flags.h) {
          printf("%s:", *filename);
          if (flags.n) {
            printf("%d:", line_number);
          }
          PrintO(&offset, match, line);
        } else {
          if (flags.n) {
            printf("%d:", line_number);
          }
          PrintO(&offset, match, line);
        }
      }
    }
    line_number++;
  }

  free(line);
  return 0;
}

int PrintO(int *offset, regmatch_t match, char *line) {
  int start = match.rm_so + *offset;
  int end = match.rm_eo + *offset;

  for (int j = start; j < end; j++) {
    printf("%c", line[j]);
  }
  printf("\n");
  *offset = end;
  return 0;
}