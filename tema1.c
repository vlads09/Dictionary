/* SIMION GEORGE-VLAD 312CB*/
#include <stdio.h>
#include <string.h>

#include "thash.h"
#include "tlg.h"

TLG citireCuvinte(TLG *lista, char *line) {
  line[strlen(line)] = '\0';
  char *cuvant = strtok(line, " .,\n1234567890");
  while (cuvant != NULL) {
    if (cuvant[strlen(cuvant) - 1] == '\n') {
      cuvant[strlen(cuvant) - 1] = '\0';
    }
    if (strlen(cuvant) >= 3) {
      *lista = GenerareLista(&(*lista), cuvant);
    }
    cuvant = strtok(NULL, " ,.\n1234567890");
  }

  return *lista;
}

int cmpElement(void *e1, void *e2) {
  TElement *el1 = (TElement *)e1;
  TElement *el2 = (TElement *)e2;
  if (el1->length != el2->length) return 0;
  if (el1->length >= el2->length) return 0;
  return 1;
}

TH *GenerareHash(TLG listaCarti) {
  TH *h = NULL;
  TLG p;
  p = listaCarti;
  TElement *element;
  int rez;

  /* calcul dimensiuni maxime pt tabela hash */
  size_t M = ('Z' - 'A' + 1);

  /* initializare tabela hash */
  h = (TH *)InitTH(M, codHash);
  if (h == NULL) return NULL;

  for (; p->info != NULL && p != NULL; p = p->urm) {
    element = (TElement *)malloc(sizeof(TElement));
    if (element == NULL) return h;

    memcpy(element, p->info, sizeof(TElement));
    SortLinkedListFreq(&(element->L));
    SortLinkedListUp(&(element->L));
    rez = InsTH(h, element, cmpElement);
    if (!rez) {
      free(element);
      return h;
    }
  }
  int i;
  for (i = 0; i <= (int)M; i++) {
    SortLinkedListElem(&h->v[i]);
  }
  return h;
}

int main(int argc, char **argv) {
  TH *h = NULL;
  FILE *f;
  char *line = NULL, *copie_linie;
  size_t len = 0;
  f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Nu a deschis fisierul\n");
    return 0;
  }
  TLG lista = malloc(sizeof(TCelulaG));
  lista->info = NULL;
  lista->urm = NULL;
  char *instructiune;
  while (getline(&line, &len, f) != -1) {
    copie_linie = line;
    instructiune =
        strtok_r(line, " ", &line);  // aici imi modific linia sa fie fara primul cuvant si salvez si cuvantul
    if (strcmp(instructiune, "insert") == 0) {
      lista = citireCuvinte(&lista, line);
      if (lista == NULL) {
        printf("Lista nu a putut fi generata\n");
      }
    } else {  // cazul fara insert(print)
      char *instructiune2;
      instructiune2 = strtok(line, " ");
      if (instructiune2 == NULL) {  // cazul cu print simplu
        h = NULL;
        h = GenerareHash(lista);
        AfiTH1(h, afisareElem1);
        continue;
      }
      int lungime, nr_aparitii;
      char c, at;

      int nr = 0;

      char *aux = malloc(strlen(instructiune2) + 1);
      strcpy(aux, instructiune2);
      instructiune2 = strtok(NULL, " ");
      if (instructiune2 == NULL) {  // cazul cu print si frecventa cuvintelor
        nr_aparitii = atoi(aux);
        h = NULL;
        h = GenerareHash(lista);
        AfiTH3(h, afisareElem3, nr_aparitii);
      } else {  // cazul cu print, prima litera a cuvantului si lungimea acestuia
        c = aux[0];
        lungime = atoi(instructiune2);
        if (lungime >= 3) {
          h = NULL;
          h = GenerareHash(lista);
          AfiTH2(h, afisareElem2, lungime, &c);
        }
      }
    }
  }
  DistrTH(&h, free);
  fclose(f);
  return 0;
}