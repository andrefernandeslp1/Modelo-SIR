#ifndef    _IO_H
#define    _IO_H     1

#include "diario.h"
#include <stdio.h>

diario *lerDiarioCSV (FILE **f);
int escreverBoletimCSV (FILE **f, diario *d);

#endif