#ifndef    _IO_H
#define    _IO_H     1

#include <stdio.h>
#include "diario.h"

diario *lerDiarioCSV (FILE **f);
int escreverBoletimCSV (FILE **f, diario *d);

#endif
