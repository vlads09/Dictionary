/* SIMION GEORGE-VLAD 312CB*/
/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void *info;          /* adresa informatie */
  struct celulag *urm; /* adresa urmatoarei celule */
} TCelulaG, *TLG;      /* tipurile Celula, Lista  */

typedef struct
{
    char* word; // cuvantul
    int freq; // frecventa
} TWord;

typedef struct
{
  TLG L; // lista de TWord-uri
  int length; // lungimea asimilata unui TWord din lista
} TElement;

typedef int (*TFElem)(void *);        /* functie prelucrare element */
typedef int (*TFCmp)(void *, void *); /* functie de comparare doua elemente */
typedef void (*TF)(void *);           /* functie afisare/eliberare un element */

/* functii lista generica */
int Ins_IncLG(TLG *, void *);    /*- inserare la inceput reusita sau nu (1/0) -*/
void DistrugeLG(TLG *aL, TF fe); /* distruge lista */
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(TLG *, TF);
TLG GenerareLista(TLG *, char *);
void afisareElem1(void *);
void afisareElem2(void *);
void afisareElem3(void *, int);
void afisareWord(void *);
void SortLinkedListFreq(TLG *);
void SortLinkedListUp(TLG *);
void SortLinkedListElem(TLG *);

#endif
