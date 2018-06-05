#include <stdio.h>
#include "types.h"

void print_grid(Grid* entry, int indent) {
	for (int i = 0; i < indent; i++) {
		printf("\t");
	}
	if (entry != null) {
		printf("Grid[%02d][%02d]=%02d| %lf", entry->y, entry->x, entry->moved_distance, entry->moved_distance + entry->euclidean_distance * HEURISTIC_MULTIPLIER);
		if (entry->origin == null) {
			printf("<-null");
		} else {
			//printf("<-[%d][%d]", entry->origin->x, entry->origin->y);
		}
		printf("\n");
	} else {
		printf("NULL\n");
	}
}

void print_board() {
	int i, j;
	printf("    \\ ");
	for (i = 0; i < w; i++) {
		printf(" %2d   ", i);
	}
	printf("\n");
	for (j = 0; j < h; j++) {
		printf("   %2d ", j);
		for (i = 0; i < w; i++) {
			Grid* grid = *(board + i + j * w);
			if (grid->is_obstacle) {
				printf(" \033[35m++++\033[00m ");
			}  else if (grid->moved_distance == INT_MAX) {
				printf("   *  ");
			} else {
				if (grid->conquered) {
					if (grid->to_direction[0] == ' ' && grid->to_direction[1] == ' ') {
						printf("\033[033m");
					} else {
						printf("\033[031m");
					}
				} else if (grid->x == gx && grid->y == gy) {
					printf("\033[034m");
				} else {
					printf("\033[036m");
				}
				printf("%3d%s ", grid->moved_distance, grid->to_direction);
				printf("\033[00m");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void traverse() {
	//printf("traverse\n");
	Grid* node = *(board + gx + h * gy);
	while (node->origin != null) {
		//printf("[%d][%d]%s\n", node->origin->x, node->origin->y, node->from_direction);
		node->origin->to_direction = node->from_direction;
		node = node->origin;
	}
}