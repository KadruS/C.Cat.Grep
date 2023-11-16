#ifndef PRINT_FIL_H
#define PRINT_FIL_H

#define _GNU_SOURCE
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flags_struct.h"

int grep_from_file(FILE *file, struct Flags flags, regex_t *regex,
                   char **filename, int file_counter);
int print_file(char *argv[], int argc, struct Flags flags, int counter);
int GrepFlagC(FILE *file, struct Flags flags, regex_t *regex, char **filename,
              int file_counter);
int GrepFlagL(FILE *file, struct Flags flags, regex_t *regex, char **filename);
int GrepFlagO(FILE *file, struct Flags flags, regex_t *regex, char **filename,
              int file_counter);
int PrintO(int *offset, regmatch_t match, char *line);

#endif