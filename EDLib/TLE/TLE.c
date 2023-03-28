#include <stdlib.h>
#include <stdio.h>
#include "TLE.h"


struct lista {
  int info;
  struct lista* prox;
};

typedef struct lista Lista;

Lista *  lst_cria(void){
  return NULL;
}

Lista * lst_insere(Lista *l, int i){
  Lista * novo = (Lista *)malloc(sizeof(Lista));
  novo->info = i;
  novo->prox = l;
  return novo;
}

void lst_imprime(Lista *l){
  Lista * p;
  for(p=l;p!=NULL;p=p->prox)
    printf("info = %d\n", p->info);
    printf("----------------------------\n");
}

int lst_vazia(Lista *l){
  return(l==NULL);
}

Lista * lst_busca (Lista * l, int v){
  Lista* p;
  for(p=l;p!=NULL;p=p->prox)
    if(p->info == v) return p;
  return NULL;
}

Lista * lst_retira(Lista * l , int v){
  Lista *ant = NULL;
  Lista * p = l;
  while(p!=NULL && p->info != v){
    ant = p;
    p = p->prox;
  }
  if (p==NULL) return l;
  if(ant == NULL) l = p->prox;
  else ant->prox = p->prox;
  free(p);
  return l;
}

void lst_libera(Lista * l){
  Lista *p = l;
  while(p!=NULL){
    Lista * t = p->prox;
    free(p);
    p = t;
  }
}

Lista *lst_insere_ordenado(Lista *l, int v){
  Lista *novo;
  Lista *ant = NULL;
  Lista *p = l;
  while(p!=NULL && p->info<v){
    ant = p;
    p = p->prox;
  }
  novo =  (Lista*)malloc(sizeof(Lista));
  novo->info = v;
  if(ant==NULL){
    novo->prox = l;
    l = novo;
  }else{
    novo->prox = ant->prox;
    ant->prox = novo;
  }
  return l;
}

void lst_imprime_rec(Lista *l){
  if(lst_vazia(l)) return;
  else{
    printf("info = %d\n", l->info);
    lst_imprime_rec(l->prox);
  }
  printf("----------------------------\n");
}

Lista * lst_retira_rec(Lista *l, int v){
  if(!lst_vazia(l)){
    if(l->info == v){
      Lista *t = l;
      l = l->prox;
      free(t);
    }else l = lst_retira_rec(l->prox, v);
  }
  return l;
}

void lst_libera_rec(Lista *l){
  if(!lst_vazia(l)){
    lst_libera_rec(l->prox);
    free(l);
  }
}

