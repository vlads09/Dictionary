/* SIMION GEORGE-VLAD 312CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(void*);

typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

/* functii tabela hash */
TH* InitTH(size_t M, TFHash fh);
void DistrTH(TH**aa, TF fe);
void AfiTH1(TH*a, TF afiEl);
void AfiTH2(TH*a, TF afiEl, int, char*);
void AfiTH3(TH*a, void(*afi_elem)(void*,int), int);
int InsTH(TH*a, void*ae, TFCmp f);
int codHash(void*);

#endif