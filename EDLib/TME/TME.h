#include "Cell.h"

typedef struct{
  Cell ** head_line;
  Cell ** head_column;
  int lines;
  int columns;
    } TME;

//Cria uma lista de tamanho mxn
TME * TME_create(int m, int n);
//Imprime elementos nao nulos da matriz e sua posicao
void TME_print_sparse(TME *t, void (*print_fn)(data_type));
//Destroi matriz
void TME_destroy(TME* tme);
//Retorna Elemento por posicao. Complexidade O(n), sendo n o maior entre o numero de colunas e o numero de linhas
data_type TME_get(TME *t, Position position);
//Imprime elementos em formato de matriz denso.
void TME_print_dense(TME *t, void (*print_fn)(data_type));
//Soma matrizes. Complexidade 0(n^2), pois no pior caso percorre n linhas, sendo n quantos elementos nao nulos possui.
TME* TME_sum(TME * t, TME * l);
//Funcao auxiliar de insercao in-place. Complexidade O(n).
void  TME_insert(TME** t, data_type value,Position position);
//Funcao para multiplicar por escalar. Complexidade O(n^2), pois no pior caso visita todas as celulas da matriz.
TME * TME_multiply_scalar(TME *t, data_type scalar);
//Permuta coluna por coluna. Complexidade O(n^2).
TME * swap_column(TME*t, int c1, int c2);
//Permuta linha por linha. Complexidade O(n^2)
TME* swap_line(TME*t, int l1, int l2);
//Multiplica matrizes. Complexidade O(n^3), pois cada linha e usada nxn vezes para produzir as somas dos produtos.
TME * TME_multiply(TME *t, TME *l);
// Multiplicacao ponto a ponto. Complexidade O(n^2)
TME * TME_multiply_point(TME*t, TME*l);
//Slicing de matrizes.Complexidade O(n^2).
TME * slicing(TME *t, Position ini, Position end);
//Operaao de convolucao. Complexidade O(n^3)
TME* convolution(TME* input, TME* kernel);
//Transposicao de matrizes. Complexidade O(n^2).
TME * transpose(TME*t);
//Salva em binario
void save_TME_binary(TME *t, char *filename);
//Carrega de binario
TME* load_TME_binary(char* filename);

