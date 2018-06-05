#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gen.h"

void create_null() {
	null = (Grid*)malloc(sizeof(Grid));
	null->x = -1;
	null->y = -1;
	null->front = null;
	null->rear = null;
	null->left = null;
	null->right = null;
	null->next = null;
	null->prev = null;
	null->moved_distance = INT_MAX;
	null->to_direction = "  ";
	null->from_direction = "  ";
	null->origin = null;
}

Grid* generate_board(int width, int height, int start_x, int start_y, int goal_x, int goal_y) {
	create_null();
	// fprintf(stderr, "COMPLETED NULL CREATION\n");
	int i, j;
	h = height;
	w = width;
	gx = goal_x;
	gy = goal_y;
	sx = start_x;
	sy = start_y;
	size = width * height;
	board = (Grid**)malloc(sizeof(Grid*) * height * width);
	Grid* grid;
	if (board == NULL) {
		fprintf(stderr, "BOARD MALLOC ERROR\n");
		exit(1);
	}
	// fprintf(stderr, "COMPLETED BOARD MALLOC\n");
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			grid = (Grid*)malloc(sizeof(Grid));
			if (grid == NULL) {
				fprintf(stderr, "GRID MALLOC ERROR\n");
				exit(1);
			}
			grid->x = i;
			grid->y = j;
			grid->next = null;
			grid->prev = null;
			grid->in_stack = 0;
			int t1 = i - goal_x, t2 = j - goal_y;
			grid->moved_distance = INT_MAX;
			grid->euclidean_distance = sqrt((double)(t1*t1) + (double)(t2*t2));
			grid->conquered = 0;
			grid->is_obstacle = 0;
			// grid->to_direction = (char*)malloc(sizeof(char) * 3);
			grid->to_direction = "  ";
			// grid->from_direction = (char*)malloc(sizeof(char) * 3);
			grid->from_direction = "  ";
			grid->origin = null;
			*(board + i + j * width) = grid;
			//printf("%lf\n", grid->euclidean_distance);
		}
	}
	// fprintf(stderr, "COMPLETED ALL GRID MALLOCS\n");
	for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
			grid = *(board + i + j * width);
			if (i < 1) { // no left
				grid->left = null;
			} else {
				grid->left = *(board + (i - 1) + j * width);
			}
			if (i > width - 2) { // no right
				grid->right = null;
			} else {
				grid->right = *(board + (i + 1) + j * width);
			}
			if (j < 1) { // no front
				grid->front = null;
			} else {
				grid->front = *(board + i + (j - 1) * width);
			}
			if (j > height - 2) { // no rear
				grid->rear = null;
			} else {
				grid->rear = *(board + i + (j + 1) * width);
			}
		}
	}
	// fprintf(stderr, "ASSIGNED ALL MOVES\n");
	start = *(board + start_x + start_y * width);
	return start;
}

void set_obstacle(int x, int y) {
	if ((x == gx && y == gy) || (x == sx && y == sy)) {
		fprintf(stderr, "invalid obstacle location\n");
		exit(1);
	}
	Grid* grid = *(board + x + y * w);
	grid->is_obstacle = 1;
}

void clear_board() {
	int i;
	for (i = 0; i < size; i++) {
		//free((*(board + i))->to_direction);
		//free((*(board + i))->from_direction);
		free(*(board + i));
	}
	free(board);
	free(null);
}