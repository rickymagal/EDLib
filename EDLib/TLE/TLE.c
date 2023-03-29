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

Lista * lst_insere_ini(Lista *l, int i){
  Lista * novo = (Lista *)malloc(sizeof(Lista));
  novo->info = i;
  novo->prox = l;
  return novo;
}

void lst_imprime(Lista *l){
  if(lst_vazia(l)) return;
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

Lista * lst_retira_elem(Lista * l , int v){
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
  Lista*p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  }free(p);
}

Lista *lst_insere_ordenado(Lista *l, int v){
  Lista* novo = lst_insere_ini(NULL, v);
  Lista* ant = NULL;
  Lista* p = l;
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

void lst_imprime_rec(Lista *l){
  if(lst_vazia(l)) return;
  else{
    printf("info = %d\n", l->info);
    lst_imprime_rec(l->prox);
  }
  printf("----------------------------\n");
}

Lista * lst_retira_elem_rec(Lista *l, int elem){
  if(!l) return l;
  if(l->info == elem){
      Lista *temp = l;
      l = l->prox;
      free(temp);
    }else l->prox = lst_retira_elem_rec(l->prox, elem);
    return l;
}

Lista* lst_insere_fim(Lista* l, int elem){
  if(!l) return lst_insere_ini(l, elem);
  Lista *p = l;
  while(p->prox) p = p->prox;
  p->prox = lst_insere_ini(p->prox, elem);
  return l;
}

Lista* lst_insere_fim_rec(Lista* l, int elem){
  if (!l) return lst_insere_ini(l,elem);
  l->prox = lst_insere_fim_rec(l->prox, elem);
  return l;
}

Lista* lst_busca_rec(Lista* l, int elem){
  if((!l) || (l->info == elem)) return l;
  return lst_busca_rec(l->prox, elem);
}

Lista* lst_retira_pos(Lista* l, int pos){
  Lista * p =l, *ant = NULL;
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

Lista* retira_todas_oc(Lista* l, int elem){
  Lista *p = l;
  Lista * new = lst_cria();
  while(p){
    if(p->info != elem) new = lst_insere_fim(new, p->info);
    p = p->prox;
  }
  free(p);
  return new;
}

Lista* lst_insere_ordenado_rec(Lista* l, int elem){
  if((!l) || (l->info >= elem)) return lst_insere_ini(l,elem);
  l->prox = lst_insere_ordenado_rec(l->prox,elem);
  return l;
}

Lista  *copia (Lista *l){
  Lista* current = l;
  Lista* new = lst_cria();
  while(current != NULL){
    new = lst_insere_fim(new, current->info);
    current = current->prox;
  }
  free(current);
  return new;
  
}

Lista * inverte(Lista* l){
  Lista * new = lst_cria();
  Lista*p = l;
  while(p){
    new = lst_insere_ini(new, p->info);
    p = p->prox;
  }
  free(p);
  return new;
}
void inverte_modifica(Lista** l){
  Lista * current = *l;
  Lista * prev = NULL;
  Lista * next = NULL;
  while(current!=NULL){
    next = current -> prox;
    current->prox = prev;
    prev = current;
    current = next;
  }
  *l = prev;
}

Lista* desloca(Lista *l, int n){
  Lista * first = l;
  Lista * current = l;
  Lista * next = l->prox;
  Lista * new = lst_cria();
  if(n%2==0){
    while(current->prox!=NULL){
      new = lst_insere_fim(new, (current->prox)->info);
      current = current->prox;
    }
    new = lst_insere_fim(new, first->info); 
  }else{
    while(current->prox!=NULL){
      new = lst_insere_fim(new, current->info);
      current = current->prox;
    }
    new = lst_insere_ini(new, current->info);
  }
  lst_libera(l);
  return new;
}

