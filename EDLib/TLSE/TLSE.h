typedef struct tlse TLSE;


TLSE* tlse_cria(void);
TLSE* tlse_insere_ini(TLSE *l, int i);
TLSE* tlse_insere_fim(TLSE* l, int elem);
TLSE* tlse_insere_fim_rec(TLSE* l, int elem);
TLSE* tlse_retira_elem(TLSE  *l, int v);
TLSE* tlse_busca(TLSE *l, int v);
TLSE* tlse_busca_rec(TLSE* l, int elem);
TLSE* tlse_insere_ordenado(TLSE *l, int v);
TLSE* tlse_retira_elem_rec(TLSE * l, int v);
TLSE* tlse_retira_pos(TLSE* l, int pos);
TLSE* retira_todas_oc (TLSE* l, int elem);
TLSE* tlse_insere_ordenado_rec(TLSE* l, int elem);
TLSE* copia (TLSE *l);
TLSE* inverte(TLSE* l);
TLSE* desloca(TLSE *l, int n);

int tlse_vazia(TLSE * l);

void tlse_imprime(TLSE *l);
void tlse_imprime_rec(TLSE *l);
void tlse_libera(TLSE *l);
void inverte_modifica(TLSE** l);
