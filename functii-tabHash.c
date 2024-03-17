/* SIMION GEORGE-VLAD 312CB*/
/*  functii-tabHash.c - functii tabela hash */

#include "thash.h"

int codHash(void* element) {
  TElement* el = (TElement*)element;
  char litera = ((TWord*)(el->L->info))->word[0];
  if ((litera >= 'A') && (litera <= 'Z')) {
    return litera - 'A';
  } else {
    return litera - 'a';
  }
}

TH* InitTH(size_t M, TFHash fh) {
  TH* h = (TH*)calloc(sizeof(TH), 1);
  if (!h) {
    printf("eroare alocare hash\n");
    return NULL;
  }

  h->v = (TLG*)calloc(M, sizeof(TLG));
  if (!h->v) {
    printf("eroare alocare vector de pointeri TLG in hash\n");
    // free(h);
    return NULL;
  }

  h->M = M;
  h->fh = fh;
  return h;
}

void DistrTH(TH** ah, TF elib_elem) {
  TLG *p, el, aux;

  /* parcurgere cu pointeri */
  for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
    /* daca exista elemente corespunzatoare acestui hash
     * eliberam info din celula si apoi eliberam celula */
    for (el = *p; el != NULL;) {
      aux = el;
      el = el->urm;
      elib_elem(aux->info);
      // free(aux);
    }
  }
  // free((*ah)->v);
  // free(*ah);
  *ah = NULL;
}

void AfiTH1(TH* ah, TF afi_elem) {
  TLG p, el;
  int i;
  for (i = 0; i < (int)ah->M; i++) {
    p = ah->v[i];
    if (p) {
      printf("pos %d: ", i);
      for (el = p; el != NULL; el = el->urm) afi_elem(el->info);
      printf("\n");
    }
  }
}

void AfiTH2(TH* ah, TF afi_elem, int lungime, char* c) {
  TLG p, el;
  int i;
  int cod;
  if (*c >= 'A' && *c <= 'Z') {
    cod = *c - 'A';
  } else {
    cod = *c - 'a';
  }
  p = ah->v[cod];
  if (p) {
    // printf("pos %d: ", i);
    for (el = p; el != NULL && ((TElement*)(el->info))->length < lungime;
         el = el->urm)
      ;
    afi_elem(el->info);
    printf("\n");
  }
}

void AfiTH3(TH* ah, void (*afi_elem)(void*, int), int nr_a) {
  TLG p, el;
  int i;
  for (i = 0; i < (int)ah->M; i++) {
    p = ah->v[i];
    if (p) {
      printf("pos%d: ", i);
      for (el = p; el != NULL; el = el->urm) afi_elem(el->info, nr_a);
      printf("\n");
    }
  }
}

/* daca elementul exista functia intoarce 0
 *altfel se incearca inserarea elementului si se intoarce rezultatul inserarii
 */
int InsTH(TH* a, void* ae, TFCmp fcmp) {
  int cod = a->fh(ae), rez;
  TLG el;

  for (el = a->v[cod]; el != NULL; el = el->urm) {
    if (fcmp(el->info, ae) == 1) return 1;
  }
  rez = Ins_IncLG(a->v + cod, ae); /* reminder: a->v+cod <=> &a->v[cod] */
  return rez;
}
