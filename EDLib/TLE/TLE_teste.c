#include <stdio.h>
#include "TLE.h"

int main(){
  Lista *l;
  l = lst_cria();
  l = lst_insere(l,23);
  l = lst_insere(l, 45);
  l = lst_insere(l, 56);
  l = lst_insere(l, 78);
  lst_imprime(l);
  l = lst_retira(l, 78);
  lst_imprime(l);
  l = lst_retira(l, 45);
  lst_imprime(l);
  lst_libera(l);
  l = lst_retira_rec(l, 56);
  lst_imprime_rec(l);
  lst_libera_rec(l);
  l = lst_cria();
  l = lst_insere_ordenado(l,23);
  l = lst_insere_ordenado(l,56);
  l = lst_insere_ordenado(l, 45);
  l = lst_insere_ordenado(l, 56);
  l = lst_insere_ordenado(l, 78);
  lst_imprime(l);
  return 0;
}
