/* SIMION GEORGE-VLAD 312CB*/
/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "tlg.h"

void SortLinkedListFreq(TLG *aL) {
  TLG nod = *aL;
  TLG nod_aux = NULL;
  TWord *aux;     // aux salveaza datele in nod->info
  nod_aux = nod;  // copiez in nod_aux pe nod pentru a putea reusi sortarea
  while (nod != NULL) {
    while (nod_aux->urm != NULL) {
      if (((TWord *)nod->info)->freq <
          ((TWord *)nod_aux->urm->info)->freq)  // compar frecventa intre noduri
      {
        aux = (TWord *)nod->info;  // aux ia informatiile din nod
        nod->info =
            nod_aux->urm
                ->info;  // schimb datele si analog pentru else if-ul de mai jos
        nod_aux->urm->info = aux;
      } else if (strcmp(((TWord *)nod->info)->word,
                        ((TWord *)nod_aux->urm->info)->word) < 0 &&
                 ((TWord *)nod->info)->freq ==
                     ((TWord *)nod_aux->urm->info)->freq) {
        aux = (TWord *)nod->info;
        nod->info = nod_aux->urm->info;
        nod_aux->urm->info = aux;
      }
      nod_aux = nod_aux->urm;  // ma duc la urmatorul nod_aux
    }
    nod = nod->urm;  // ma duc la urmatorul nod_aux
  }
}

void SortLinkedListUp(TLG *aL) {
  TLG nod = *aL;
  TLG nod_aux = NULL;
  TWord *aux;
  while (nod != NULL) {
    nod_aux = nod;
    while (nod_aux->urm != NULL) {
      if ((((TWord *)nod->info)->freq == ((TWord *)nod_aux->urm->info)->freq) &&
          strcmp(((TWord *)nod->info)->word,
                 ((TWord *)nod_aux->urm->info)->word) > 0) {
        aux = (TWord *)nod->info;
        nod->info = nod_aux->urm->info;
        nod_aux->urm->info = aux;
      }
      nod_aux = nod_aux->urm;
    }
    nod = nod->urm;
  }
}

void SortLinkedListElem(TLG *aL) {
  TLG nod = *aL;
  TLG nod_aux = NULL;
  TElement *aux;
  while (nod != NULL) {
    nod_aux = nod;
    while (nod_aux->urm != NULL) {
      if ((((TElement *)nod->info)->length >=
           ((TElement *)nod_aux->urm->info)->length)) {
        aux = (TElement *)nod->info;
        nod->info = nod_aux->urm->info;
        nod_aux->urm->info = aux;
      }
      nod_aux = nod_aux->urm;
    }
    nod = nod->urm;
  }
}

void afisareWord(void *element) {
  TWord *cuvant = (TWord *)element;
  printf("%s/%d", cuvant->word, cuvant->freq);
}

void afisareElem1(void *element) {
  TElement *cuvant = (TElement *)element;
  TLG lcuv = cuvant->L;
  printf("(%d:", cuvant->length);
  int nr = 0;
  for (; lcuv != NULL; lcuv = lcuv->urm) {
    if (nr != 0) {
      printf(", ");
    }
    afisareWord(lcuv->info);
    nr++;
  }
  printf(")");
}

void afisareElem2(void *element) {
  TElement *cuvant = (TElement *)element;
  TLG lcuv = cuvant->L;
  printf("(%d:", cuvant->length);
  int nr = 0;
  for (; lcuv != NULL; lcuv = lcuv->urm) {
    if (nr != 0) {
      printf(", ");
    }
    afisareWord(lcuv->info);
    nr++;
  }
  printf(")");
}

void afisareElem3(void *element, int nr_a) {
  TElement *cuvant = (TElement *)element;
  TLG lcuv = cuvant->L;
  TLG lcuva = cuvant->L;
  TLG lcuvb = cuvant->L;
  for (; lcuva != NULL; lcuva = lcuva->urm) {
    if (((TWord *)(lcuva->info))->freq <= nr_a) {
      printf("(%d: ", cuvant->length);
      break;
    }
  }
  int nr = 0;
  for (; lcuv != NULL; lcuv = lcuv->urm) {
    if (nr != 0 && ((TWord *)(lcuv->info))->freq <= nr_a) {
      printf(", ");
    }
    if (((TWord *)(lcuv->info))->freq <= nr_a) {
      afisareWord(lcuv->info);
      nr++;
    }
  }
  for (; lcuvb != NULL; lcuvb = lcuvb->urm) {
    if (((TWord *)(lcuvb->info))->freq <= nr_a) {
      printf(")");
      break;
    }
  }
}

int Ins_IncLG(TLG *aL, void *ae) {
  TLG aux = malloc(sizeof(TCelulaG));
  if (!aux) return 0;

  aux->info = ae;
  aux->urm = *aL;
  *aL = aux;

  return 1;
}

TWord *alocCuvant(char *cuv) {  // functie care imi returneaza un TWord pentru lista dintr-o celula de tip TElement
  TWord *cuvant = malloc(sizeof(TWord));
  cuvant->word = malloc(strlen(cuv) + 1);
  strcpy(cuvant->word, cuv);
  cuvant->freq = 1;
  return cuvant;
}

TLG GenerareLista(TLG *lista, char *cuv) {
  TLG Laux;  // copie a listei de TElemente
  int cuv_gasit = 0;
  int lung_gasit = 0;
  Laux = *lista;
  TElement *element;
  TLG laux;  // copie a listei dintr-un TElement
  for (; Laux->info != NULL && Laux != NULL; Laux = Laux->urm) {
    element = (TElement *)(Laux->info);
    TLG prim_cuvant = element->L;
    int dif = ((TWord *)(prim_cuvant->info))->word[0] - cuv[0];
    dif =
        abs(dif);  // am calculat pentru a putea insera in acceasi lista cuvintele cu acceasi litera mica sau sub forma de majuscula
    if (element->length == (int)strlen(cuv) && (dif == 32 || dif == 0)) {
      lung_gasit = 1;
      laux = element->L;
      for (; laux != NULL && cuv_gasit == 0; laux = laux->urm) {
        if (strcmp(((TWord *)laux->info)->word, cuv) == 0) {
          ((TWord *)laux->info)->freq++;  // cresc frecventa daca exista deja un TWord egal ca string
          cuv_gasit = 1;
        }
      }

      if (cuv_gasit == 0) {  // aloc un TWord daca nu am gasit deja in TElement
        TWord *ins_cuv = alocCuvant(cuv);
        Ins_IncLG(&(element->L), (void *)ins_cuv);
      }
    }
  }
  if (lung_gasit == 0) {  // aloc un TElement si TWord-ul care a generat conditia
    TWord *ins_cuv = alocCuvant(cuv);
    TElement *ins_el = malloc(sizeof(TElement));
    ins_el->length = strlen(ins_cuv->word);
    Ins_IncLG(&(ins_el->L), (void *)ins_cuv);
    Ins_IncLG(&(*lista), (void *)ins_el);
  }
  return *lista;
}

void DistrugeLG(TLG *aL, TF free_elem) /* distruge lista */
{
  while (*aL != NULL) {
    TLG aux = *aL; /* adresa celulei eliminate */
    if (!aux) return;

    // free_elem(aux->info); /* elib.spatiul ocupat de element*/
    *aL = aux->urm; /* deconecteaza celula din lista */
    // free(aux);            /* elibereaza spatiul ocupat de celula */
  }
}

size_t LungimeLG(TLG *a) /* numarul de elemente din lista */
{
  size_t lg = 0;
  TLG p = *a;

  /* parcurge lista, numarand celulele */
  for (; p != NULL; p = p->urm) lg++;

  return lg;
}

void Afisare(TLG *aL, TF afiEL) {
  if (!*aL) {
    printf("Lista vida\n");
    return;
  }

  printf("[\n");
  for (; *aL && (*aL)->info != NULL; aL = &(*aL)->urm) {
    afiEL((*aL)->info);
  }
  printf("]\n");
}
