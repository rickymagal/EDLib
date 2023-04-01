#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vector.h"

Vector *vector_construct(){

    Vector* v= (Vector*)calloc(1, sizeof(Vector));

    v->size = 0;
    v->allocated = 10;

    v->data= (data_type*)calloc(v->allocated, sizeof(data_type));
    return v;
}

void vector_push_back(Vector *v, data_type val){
  
    if (v->size == v->allocated)
    {
        v->allocated *= 2;
        v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
    }
    v->data[v->size] = val;
    v->size++;   
}

data_type vector_get(Vector *v, int i){
    if((i<0) || (i>v->size)){
        printf("Error\n");
        exit(0);
    }
    return v->data[i];
}

void vector_set(Vector *v, int i, data_type val){
    if((i<0) || (i>v->size)){
        printf("Error");
        exit(0);
    }
    v->data[i]= val;
}

int vector_size(Vector *v){
    return v->size;
}

int vector_find(Vector *v, data_type val){
    for(int i=0; i<v->size; i++){
        if(v->data[i]==val){
            return i;
        }
    }
    return -1;
}
void vector_destroy(Vector *v){
    free(v->data);
    free(v);
}
    
data_type  vector_remove(Vector *v, int i){
  data_type removido = v->data[i];
  for(int j = i; j<v->size-1; j++) v->data[j] = v->data[j+1];
  v->size = v->size-1;
  return removido;
}

data_type vector_pop_front(Vector *v){
  return vector_remove(v, 0);
}
data_type vector_pop_back(Vector *v){
  return vector_remove(v, v->size-1);
}

void vector_insert(Vector *v, int i, data_type val){
  if(v->size == v->allocated){
    v->allocated *= 2;
    v->data = (data_type*)realloc(v->data, v->allocated * sizeof(data_type));
  }
  v->size++;
  for(int j = v->size-1; j>i;j--) v->data[j] = v->data[j-1];
  v->data[i] = val;
}

void vector_swap(Vector *v, int i, int j){
  data_type temp = v->data[i];
  v->data[i] = v->data[j];
  v->data[j] = temp;
}

int vector_binary_search(Vector *v, data_type val){
  int low = 0, high = v->size -1;
  int mid;
  while(high-low>1){
    mid = (high + low)/2;
    if(v->data[mid]<val) low = mid + 1;
    else high = mid;
  }
  if(v->data[low] == val)  return low;
  else if(v->data[high] == val) return high;
  else return -1;
}

void vector_sort(Vector *v){
  data_type temp;
  for(int x = 0; x < v->size - 1; x++){       
        for(int y = 0; y < v->size - x - 1; y++){          
            if(v->data[y] > v->data[y + 1]){               
                temp = v->data[y];
                v->data[y] = v->data[y + 1];
                v->data[y + 1] = temp;
            }
        }
    }
}

void vector_reverse(Vector *v){
  for(int i =0, j = v->size-1;i<v->size/2; i++, j--) vector_swap(v, i, j);
}

Vector *vector_copy(Vector *v){
  Vector * new = vector_construct();
  new->size = v->size;
  new->allocated = v->allocated;
  new->data = (data_type*) memcpy(new->data, v->data, sizeof(data_type)*v->allocated);
  return new;
}

void vector_clear(Vector *v){
  v->size = 0;
  v->allocated = 10;
  free(v->data);
  v->data = (data_type*)calloc(v->allocated, sizeof(data_type));
}

Vector * vector_find_all(Vector * v, data_type val){
  Vector * new = vector_construct();
  for(int i=0; i<v->size;i++) if(v->data[i] == val) vector_push_back(new, i);
  return new;
}
