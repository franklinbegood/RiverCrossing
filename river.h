#ifndef RIVER_H
#define RIVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
typedef struct pole {
	int val;
	int w;
} Pole;

Pole **loadFile(char *filename, int *n, int *m);
void crossRiver(Pole** p, int r, int c, int n, int m);
int fewestRotations(char *filename);

#endif
