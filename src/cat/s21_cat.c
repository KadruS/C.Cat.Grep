#include "s21_cat.h"

int main(int argc, char *argv[]) {
  struct Flags flags = {0};

  int counter = parser(argc, argv, &flags);

  if (counter == -1) return 1;

  if (flags.n && flags.b) flags.n = 0;

  print_file(argv, argc, counter, flags);
  return 0;
}
