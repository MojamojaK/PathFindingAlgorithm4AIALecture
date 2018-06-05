#include <limits.h>

#define HEURISTIC_MULTIPLIER 1

typedef struct Grid {
	int x;
	int y;
	struct Grid* front;
	struct Grid* rear;
	struct Grid* left;
	struct Grid* right;

	struct Grid* next;
	struct Grid* prev;

	struct Grid* origin;
	char* from_direction;
	char* to_direction;

	char in_stack;
	char is_obstacle;
	char conquered;

	int moved_distance;
	double euclidean_distance;
} Grid;

Grid** board;

Grid* null;
Grid* start;

int w, h;
int gx, gy;
int sx, sy;
int size;

void traverse();
void print_grid(Grid*, int);
void print_board();