#include "TME.h"
#include <stdlib.h>
#include <stdio.h>

TME * TME_create(int m, int n){
  TME* new = (TME*)malloc(sizeof(TME));
  new->head_line = (Cell**)malloc(sizeof(Cell*)*m);
  new->head_column = (Cell**)malloc(sizeof(Cell*)*n);
  new->lines = m;
  new->columns = n;
  for(int i=0; i<n; i++) *(new->head_column + i) = NULL;
  for(int i=0; i<m; i++) *(new->head_line + i) = NULL;
  return new;
}

data_type  TME_get(TME *t, Position position){
  if(t->columns<t->lines){
    Cell *l = *(t->head_line+(position.line-1));
    if(!l) return 0;
    while(l){
      if(l->position.column == position.column){
	return l->value;
      }l=l->next_line;
     }
    return 0;
  }else{
    Cell *l = *(t->head_column+(position.column-1));
    if(!l) return 0;
    while(l){
      if(l->position.line == position.line){
	return l->value;
      }l=l->next_column;
    }return 0;
  }
}

void TME_destroy(TME* tme) {
    for (int i = 0; i < tme->lines; i++) {
      Cell* current_line = tme->head_line[i];
      while (current_line != NULL) {
        Cell* next_cell = current_line->next_line;
        free(current_line);
        current_line = next_cell;
      }
    }
    free(tme->head_line);
    free(tme->head_column);
    free(tme);
}

void TME_print_sparse(TME *t, void (*print_fn)(data_type)){
  Cell *p;
  for(int i=0;i<t->lines;i++){
    for(p=*(t->head_line+i); p!=NULL;p=p->next_line){
      (*print_fn)(p->value);
      printf("(%d,%d)\n", (p->position).line, (p->position).column);
    }
  }
}


void TME_print_dense( TME *t, void (*print_fn)(data_type)){
  float zero = 0;
  for(int i =0; i<t->lines;i++){
    printf("| ");
    Cell *p = *(t->head_line+i);
    if(!p){
      for(int j=0; j<t->columns; j++) printf("%.6f ", zero);
      printf("|\n");
      continue;
    }else{
      int zeroes_before = 0;
      int ant=0;
      while(p){
	zeroes_before = p->position.column - ant - 1;
	for(int k=0; k<zeroes_before;k++) printf("%.6f ", zero);
	ant = p->position.column;
	(*print_fn)(p->value);
	printf(" ");
	p = p->next_line;
      }
      if(ant< t->columns){
	for(int n=0; n<t->columns - ant; n++) printf("%.6f ", zero);
      }
    }printf("|\n");
  }
}

void change(TME **t, data_type value, Position position){
  Cell *p = *((*t)->head_line + position.line-1);
  while(p->position.column < position.column){
    p = p->next_line;
  }
  p->value = value;
}

void TME_insert(TME** t, data_type value,Position position){
  if (TME_get(*t, position)){
    change(t, value, position);
    return;
  }
  Cell * new = cell_create(value, position, NULL, NULL);
  if (position.line > (*t)->lines || position.column > (*t)->columns || position.line <1 || position.column <1) return;
  Cell ** line = ((*t)->head_line + position.line-1);
  Cell ** column =((*t)->head_column + position.column-1);
  if(!(*line)){
      new->next_line = *line;
      *line = new;
  }else{
    Cell * temp = *line;
    Cell * ant = temp;
    if(position.column< temp->position.column){
      new->next_line = *line;
      *line = new;
      
    }else{
     while(temp && position.column > (temp)->position.column){
        ant = temp;
       temp = (temp)->next_line;
     } new->next_line=temp;
    ant->next_line = new;
    }
  }
   if(!(*column)){
      new->next_column = *column;
      *column = new;
  }else{
    Cell * temp = *column;
    Cell * ant = temp;
    if(position.line< temp->position.line){
      new->next_column = *column;
      *column = new;
      
    }else{
     while(temp && position.line > (temp)->position.line){
        ant = temp;
       temp = (temp)->next_column;
     } new->next_column=temp;
    ant->next_column = new;
    }
   }

}

TME* TME_copy(TME *t){
  TME* new = TME_create(t->lines, t->columns);
  for(int i=0; i<t->lines; i++){
    Cell *temp = *(t->head_line +i);
    while(temp){
      TME_insert(&new, temp->value, temp->position);
      temp = temp->next_line;
    }
  }return new;
}

TME* TME_sum(TME * t, TME * l){
  if(t->columns != l->columns || t->lines != l->lines) return t;
  Cell *T, *L;
  TME *new = TME_copy(t);
    for(int i=0; i<t->lines; i++){
      T = *(t->head_line+i);
      L = *(l->head_line+i);
      while(T){
	 while(L->position.column<= T->position.column){
	   if(L->position.column == T->position.column) TME_insert(&new, L->value + T->value, T->position);
	   else  TME_insert(&new, L->value, L->position);
	   L = L->next_line;
	   if(!L) break;
	 }
	 T = T->next_line;
      }
    }return new;
}

TME * slicing(TME *t, Position ini, Position end){
  TME *new = TME_create(end.line -ini.line+1, end.column - ini.column+1);
  int endLine, endColumn;
  if(end.line > t->lines) endLine = t->lines;
  else endLine = end.line;
  if(end.column>t->columns) endColumn = t->columns;
  else endColumn = end.column;
  for(int i = ini.line; i<=endLine; i++){
    Cell*l = *(t->head_line +i-1);
    while(l->position.column <= endColumn){
      Position position;
      position.line = i-ini.line +1;
      position.column =l->position.column - ini.column+1;
      TME_insert(&new, l->value, position);
      l = l->next_line;
      if(!l) break;
    }
  }return new;
}

TME *swap_column(TME *t, int c1, int c2){
  TME * new = TME_create(t->lines, t->columns);
    for(int i=0; i<t->lines;i++){
      Cell *l = *(t->head_line +i);
      while(l){
	Position position;
	position.line = l->position.line;
	if(l->position.column == c1){
	  position.column = c2;
	}else if(l->position.column ==c2){
	  position.column = c1;
	}else{
	  position.column = l->position.column;
	}
	TME_insert(&new, l->value, position);
	l = l->next_line;
      }
    }return new;
}

TME* swap_line(TME*t, int l1, int l2){
    TME * new = TME_create(t->lines, t->columns);
    for(int i=0; i<t->columns;i++){
      Cell *c = *(t->head_column +i);
      while(c){
	Position position;
	position.column = c->position.column;
	if(c->position.line == l1){
	  position.line = l2;
	}else if(c->position.line ==l2){
	  position.line = l1;
	}else{
	  position.line = c->position.line;
	}
	TME_insert(&new, c->value, position);
	c = c->next_column;
      }
    }return new;
  
}

TME * transpose(TME*t){
  if(t->lines != t->columns) return t;
  TME *new = TME_create(t->lines, t->columns);
  for(int i =0; i<t->lines; i++){
    Cell *l = *(t->head_line +i);
    while(l){
      Position position;
      position.line = l->position.column;
      position.column = l->position.line;
      TME_insert(&new, l->value, position);
      l = l->next_line;
    }free(l);
  }return new;
}

TME * TME_multiply_scalar(TME *t, data_type scalar){
  TME *new  = TME_create(t->lines, t->columns);
  for(int i=0; i<t->lines; i++){
    Cell *p = *(t->head_line+i);
    while(p){
      TME_insert(&new, (p->value)*scalar, p->position);
      p = p->next_line;
    }
  }return new;
}


TME * TME_multiply(TME *t, TME *l){
  if(t->columns != l->lines) return t;
  int sum;
  TME * new = TME_create(t->lines, l->columns);
  for(int i = 0;i<t->lines; i++){
    for(int j=0; j<l->columns; j++){
      Cell * T = *(t->head_line +i);
      Cell *L = *(l->head_column +j);
      sum = 0;
      while(L){
	if(T){
         while(T->position.column<= L->position.line){
	   if(T->position.column == L->position.line) sum+= L->value*T->value;
	   T = T->next_line;
	   if(!T) break;
	 }
	}L = L->next_column;
      }
      Position position;
      position.line = i+1;
      position.column  = j+1;
      if(sum!=0) TME_insert(&new, sum, position);
    }
  }return new;
}

TME * TME_multiply_point(TME*t, TME*l){
  if(t->columns != l->columns || t->lines != l->lines) return t;
  Cell *T, *L;
  TME *new = TME_copy(t);
    for(int i=0; i<t->lines; i++){
      T = *(t->head_line+i);
      L = *(l->head_line+i);
      while(T){
	 while(L->position.column<= T->position.column){
	   if(L->position.column == T->position.column) TME_insert(&new, L->value * T->value, T->position);
	   L = L->next_line;
	   if(!L) break;
	 }
	 T = T->next_line;
      }
    }
    free(T);
    free(L);
    return new;
}

TME* convolution(TME* input, TME* kernel)
{
    int input_lines = input->lines;
    int input_columns = input->columns;
    int kernel_lines = kernel->lines;
    int kernel_columns = kernel->columns;
    
    TME* output = TME_create(input_lines, input_columns);
    
    for (int i = 0; i < input_lines; i++) {
        for (int j = 0; j < input_columns; j++) {
                       int start_line = i - kernel_lines / 2;
            int start_column = j - kernel_columns / 2;
            int end_line = start_line + kernel_lines - 1;
            int end_column = start_column + kernel_columns - 1;
        
            data_type sum = 0;
            
            for (int k = 0; k < kernel_lines; k++) {
                for (int l = 0; l < kernel_columns; l++) {
                    int current_line = start_line + k;
                    int current_column = start_column + l;
                    
                    if (current_line >= 0 && current_line < input_lines &&
                        current_column >= 0 && current_column < input_columns) {
		      Position current;
		      Position kernel;
		      current.line = current_line+1;
		      current.column = current_column+1;
		      kernel.line = k+1;
			kernel.column = l+1;
                       
                        data_type input_value = TME_get(input, current);
                      
                        data_type kernel_value = TME_get(input, kernel);
                        
                        sum += input_value * kernel_value;
                    }
                }
            }
            
            Position position;
            position.line = i + 1;
            position.column = j + 1;
            TME_insert(&output, sum, position);
        }
    }
    
    return output;
}

void save_TME_binary(TME *t, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&(t->lines), sizeof(int), 1, file);
    fwrite(&(t->columns), sizeof(int), 1, file);
    for (int i = 0; i < t->lines; i++) {
        for (int j = 0; j < t->columns; j++) {
             Position position;
            position.line = i + 1;
            position.column = j + 1;
            data_type value = TME_get(t, position);
            if(value) fwrite(&value, sizeof(data_type), 1, file);
        }
    }

    fclose(file);
}


TME* load_TME_binary(char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return NULL;
    }

    int rows, columns;
    fread(&rows, sizeof(int), 1, file);
    fread(&columns, sizeof(int), 1, file);

    TME* t = TME_create(rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            data_type value;
            fread(&value, sizeof(data_type), 1, file);
            Position position;
            position.line = i + 1;
            position.column = j + 1;
            TME_insert(&t, value, position);
        }
    }

    fclose(file);
    return t;
}
