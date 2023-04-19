typedef struct tlse TLSE;
typedef int data_type;

TLSE* tlse_cria(void);
TLSE* tlse_insere_ini(TLSE *l, data_type i);
TLSE* tlse_insere_fim(TLSE* l, data_type elem);
TLSE* tlse_insere_fim_rec(TLSE* l, data_type elem);
TLSE* tlse_retira_elem(TLSE  *l, data_type v);
TLSE* tlse_busca(TLSE *l, data_type v);
TLSE* tlse_busca_rec(TLSE* l, data_type elem);
TLSE* tlse_insere_ordenado(TLSE *l, data_type v);
TLSE* tlse_retira_elem_rec(TLSE * l, data_type v);
TLSE* tlse_retira_pos(TLSE* l, int pos);
TLSE* retira_todas_oc (TLSE* l, data_type elem);
TLSE* tlse_insere_ordenado_rec(TLSE* l, data_type elem);
TLSE* copia (TLSE *l);
TLSE* inverte(TLSE* l);
TLSE* desloca(TLSE *l, int n);

int tlse_vazia(TLSE * l);

void tlse_imprime(TLSE *l);
void tlse_imprime_rec(TLSE *l);
void tlse_libera(TLSE *l);
void inverte_modifica(TLSE** l);
