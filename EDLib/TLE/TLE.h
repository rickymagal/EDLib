typedef struct lista Lista;

Lista * lst_cria(void);
Lista * lst_insere(Lista *l, int i);
Lista * lst_retira(Lista  *l, int v);
Lista * lst_busca(Lista *l, int v);
Lista * lst_insere_ordenado(Lista *l, int v);
Lista * lst_retira_rec(Lista * l, int v);


int lst_vazia(Lista * l);

void lst_imprime(Lista *l);
void lst_imprime_rec(Lista *l);
void lst_libera(Lista *l);
void lst_libera_rec(Lista *l);
