#include "s21_grep.h"

int main(int argc, char *argv[]) {
  struct Flags flags = {0};

  if (argc == 1) {
    return 0;
  }

  int counter = parser(argc, argv, &flags);

  if (counter == -1) return 1;

  print_file(argv, argc, flags, counter);

  return 0;
}
