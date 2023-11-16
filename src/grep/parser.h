#ifndef PARSER_H
#define PARSER_H

#define _GNU_SOURCE
#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flags_struct.h"

int parser(int argc, char *argv[], struct Flags *flags);
int FlagFnE(struct Flags *flags);
int FlagFnF(struct Flags *flags);

#endif