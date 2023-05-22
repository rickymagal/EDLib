typedef float data_type;

typedef struct {
  int line;
  int column;
} Position;

typedef struct Cell{
  Position position;
  data_type value;
  struct Cell * next_line;
  struct Cell *next_column;

}Cell;

Cell * cell_create(data_type value, Position position, Cell *next_line, Cell *next_column);
void cell_destroy(Cell * c);
