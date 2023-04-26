#include <stdlib.h>
#include <stdio.h>
#include "TLSE.h"

struct tlse {
  data_type info;
  struct tlse* prox;
};


typedef struct tlse TLSE;

TLSE *  tlse_cria(void){
  return NULL;
}

TLSE * tlse_insere_ini(TLSE *l, data_type i){
  TLSE * novo = (TLSE *)malloc(sizeof(TLSE));
  novo->info = i;
  novo->prox = l;
  return novo;
}

void tlse_imprime(TLSE *l, void (*print_fn)(data_type)){
  if(tlse_vazia(l)) return;
  TLSE * p;
  for(p=l;p!=NULL;p=p->prox) (*print_fn)(p->info);
  printf("----------------------------\n");
}

int tlse_vazia(TLSE *l){
  return(l==NULL);
}

TLSE * tlse_busca (TLSE * l, data_type v){
  TLSE* p;
  for(p=l;p!=NULL;p=p->prox)
    if(p->info == v) return p;
  return NULL;
}

TLSE * tlse_retira_elem(TLSE * l , data_type v){
  TLSE *ant = NULL;
  TLSE * p = l;
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

void tlse_libera(TLSE * l){
  TLSE*p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  }free(p);
}

TLSE *tlse_insere_ordenado(TLSE *l, data_type v){
  TLSE* novo = tlse_insere_ini(NULL, v);
  TLSE* ant = NULL;
  TLSE* p = l;
  if(!l) return novo;
  while(p!=NULL && p->info <v){
    ant = p;
    p = p->prox;
  }
  if(ant==NULL){
    novo->prox = l;
    return novo;
  }
  novo->prox = p;
  ant->prox = novo;
  return l;
}

void tlse_imprime_rec(TLSE *l, void (*print_fn)(data_type)){
  if(tlse_vazia(l)) return;
  else{
    (*print_fn)(l->info);
    tlse_imprime_rec(l->prox, *print_fn);
  }
  printf("----------------------------\n");
}

TLSE * tlse_retira_elem_rec(TLSE *l, data_type elem){
  if(!l) return l;
  if(l->info == elem){
      TLSE *temp = l;
      l = l->prox;
      free(temp);
    }else l->prox = tlse_retira_elem_rec(l->prox, elem);
    return l;
}

TLSE* tlse_insere_fim(TLSE* l, data_type elem){
  if(!l) return tlse_insere_ini(l, elem);
  TLSE *p = l;
  while(p->prox) p = p->prox;
  p->prox = tlse_insere_ini(p->prox, elem);
  return l;
}

TLSE* tlse_insere_fim_rec(TLSE* l, data_type elem){
  if (!l) return tlse_insere_ini(l,elem);
  l->prox = tlse_insere_fim_rec(l->prox, elem);
  return l;
}

TLSE* tlse_busca_rec(TLSE* l, data_type elem){
  if((!l) || (l->info == elem)) return l;
  return tlse_busca_rec(l->prox, elem);
}

TLSE* tlse_retira_pos(TLSE* l, int pos){
  TLSE * p =l, *ant = NULL;
  int i = 1;
  while((p) && i<pos){
    ant = p;
    p = p->prox;
    i++;
  }
  if(!p) return l;
  if(!ant) l = l->prox;
  else ant->prox = p->prox;
  free(p);
  return l;
}

TLSE* retira_todas_oc(TLSE* l, data_type elem){
  TLSE *p = l;
  TLSE * new = tlse_cria();
  while(p){
    if(p->info != elem) new = tlse_insere_fim(new, p->info);
    p = p->prox;
  }
  free(p);
  return new;
}

TLSE* tlse_insere_ordenado_rec(TLSE* l, data_type elem){
  if((!l) || (l->info >= elem)) return tlse_insere_ini(l,elem);
  l->prox = tlse_insere_ordenado_rec(l->prox,elem);
  return l;
}

TLSE  *copia (TLSE *l){
  TLSE* current = l;
  TLSE* new = tlse_cria();
  while(current != NULL){
    new = tlse_insere_fim(new, current->info);
    current = current->prox;
  }
  free(current);
  return new;
  
}

TLSE * inverte(TLSE* l){
  TLSE * new = tlse_cria();
  TLSE*p = l;
  while(p){
    new = tlse_insere_ini(new, p->info);
    p = p->prox;
  }
  free(p);
  return new;
}
void inverte_modifica(TLSE** l){
  TLSE * current = *l;
  TLSE * prev = NULL;
  TLSE * next = NULL;
  while(current!=NULL){
    next = current -> prox;
    current->prox = prev;
    prev = current;
    current = next;
  }
  *l = prev;
}

TLSE* desloca(TLSE *l, int n){
  TLSE * first = l;
  TLSE * current = l;
  TLSE * next = l->prox;
  TLSE * new = tlse_cria();
  if(n%2==0){
    while(current->prox!=NULL){
      new = tlse_insere_fim(new, (current->prox)->info);
      current = current->prox;
    }
    new = tlse_insere_fim(new, first->info); 
  }else{
    while(current->prox!=NULL){
      new = tlse_insere_fim(new, current->info);
      current = current->prox;
    }
    new = tlse_insere_ini(new, current->info);
  }
  tlse_libera(l);
  return new;
}

void retira_todas_oc_modifica(TLSE **l, data_type val){
  TLSE *ant = NULL;
  TLSE * p = *l;
  while(p){
    if(p->info == val){
      if(ant==NULL){
	TLSE* aux = p;
	*l = p->prox;
	p=p->prox;
	free(aux);
      }else{
	TLSE* aux = p;
	ant->prox = p->prox;
	p =  p->prox;
	free(aux);
      }
    }else{
      ant = p;
      p = p->prox;
    }
  }
}

void tlse_concatena(TLSE **l, TLSE *m){
  TLSE* p = *l;
  TLSE* ant = NULL;
  while(p){
    ant = p;
    p = p->prox;
  }ant->prox = m;
}

data_type tlse_busca_pos(TLSE *l, int i){
  TLSE* p;
  int j;
    for(p=l, j = 0;j< i;p=p->prox, j++){}
    return p->info;
}
