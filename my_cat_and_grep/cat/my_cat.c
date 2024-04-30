#include "my_cat.h"

int main(int argc, char **argv) {
  int result = 1;
  struct flags flag = {
      .b = 0,
      .e = 0,
      .n = 0,
      .s = 0,
      .t = 0,
      .v = 0,
  };
  result = parser(argc, argv, &flag);
  if (flag.b == 1) {
    flag.n = 0;
  }
  while (optind < argc) {
    result = print_file(argv, &flag);
    optind++;
  }
  return result;
}

int parser(int argc, char *argv[], struct flags *flag) {
  int a;
  int res = 0;
  int i = 0;

  static struct option opt[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };

  while ((a = getopt_long(argc, argv, "bEnsTvet", opt, &i)) != -1) {
    switch (a) {
      case 'b':
        flag->b = 1;
        break;

      case 'E':
        flag->e = 1;
        break;

      case 'n':
        flag->n = 1;
        break;

      case 's':
        flag->s = 1;
        break;

      case 'T':
        flag->t = 1;
        break;

      case 'v':
        flag->v = 1;
        break;

      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;

      case 't':
        flag->t = 1;
        flag->v = 1;
        break;

      case '?':
        res = -1;
        break;
    }
  }
  return res;
}

int print_file(char *argv[], struct flags *flag) {
  int res = 0;
  FILE *f = fopen(argv[optind], "rt");

  if (f != NULL) {
    int count = 1;
    int empty_count = 0;
    int last_symbol = '\n';

    while (1) {
      int c = fgetc(f);
      if (c == EOF) {
        break;
      }
      if (flag->s && c == '\n' && last_symbol == '\n') {
        empty_count++;
        if (empty_count > 1) {
          continue;
        }
      } else {
        empty_count = 0;
      }
      if (last_symbol == '\n' && ((flag->b && c != '\n') || flag->n)) {
        printf("%6d\t", count++);
      }
      if (flag->t && c == '\t') {
        printf("^");
        c = 'I';
      }
      if (flag->e && c == '\n') {
        printf("$");
      }
      if (flag->v) {
        if ((c < 32 && c != '\n' && c != '\t') || c == 127) printf("^");
        if (c > 127 && c < 160) printf("M-^");
        if ((c < 32 || (c > 126 && c < 160)) && c != '\n' && c != '\t')
          c = c > 126 ? c - 128 + 64 : c + 64;
      }
      printf("%c", c);
      last_symbol = c;
    }
    fclose(f);
  } else {
    res = -1;
  }
  return res;
}