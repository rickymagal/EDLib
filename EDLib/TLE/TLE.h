typedef struct lista Lista;

Lista* lst_cria(void);
Lista* lst_insere_ini(Lista *l, int i);
Lista* lst_insere_fim(Lista* l, int elem);
Lista* lst_insere_fim_rec(Lista* l, int elem);
Lista* lst_retira_elem(Lista  *l, int v);
Lista* lst_busca(Lista *l, int v);
Lista* lst_busca_rec(Lista* l, int elem);
Lista* lst_insere_ordenado(Lista *l, int v);
Lista* lst_retira_elem_rec(Lista * l, int v);
Lista* lst_retira_pos(Lista* l, int pos);
Lista* retira_todas_oc (Lista* l, int elem);
Lista* lst_insere_ordenado_rec(Lista* l, int elem);
Lista* copia (Lista *l);
Lista* inverte(Lista* l);
Lista* desloca(Lista *l, int n);

int lst_vazia(Lista * l);

void lst_imprime(Lista *l);
void lst_imprime_rec(Lista *l);
void lst_libera(Lista *l);
void inverte_modifica(Lista** l);
