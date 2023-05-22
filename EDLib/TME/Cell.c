#include "Cell.h"
#include <stdlib.h>


Cell* cell_create(data_type value, Position position, Cell* next_line, Cell* next_column) {
    Cell* new_cell = (Cell*)malloc(sizeof(Cell));
    if (new_cell == NULL) {
        return NULL;
    }
    new_cell->value = value;
    new_cell->position = position;
    new_cell->next_line = next_line;
    new_cell->next_column = next_column;
    return new_cell;
}

void cell_destroy(Cell * c){
  free(c);
}
