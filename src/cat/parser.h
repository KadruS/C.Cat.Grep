#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "flags_struct.h"

int parser(int argc, char *argv[], struct Flags *flags);

#endif