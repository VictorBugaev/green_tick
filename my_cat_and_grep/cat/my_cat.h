#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

int parser(int argc, char *argv[], struct flags *flag);
int print_file(char *argv[], struct flags *flag);
