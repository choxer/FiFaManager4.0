#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#include "datastruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortTeams(void);
void Fifasort(int (*)(TPlayer* , TPlayer*));
void Tausch( int , TPlayer * , TPlayer * );

#endif



