#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

char* UP		= "↑";
char* DOWN 		= "↓";
char* LEFT 		= "←";
char* RIGHT 	= "→";
char* NONE		= "  ";
char* START		= "+ ";

void push_stack(Grid*);
void pop_stack(Grid*);
void move_surround(Grid*);
void move(Grid*, Grid*, char[]);
void print_stack();

Grid* stack_head;

#ifndef GREEDY
#define ASTAR
char* mode = "A*";
#else
char* mode = "Greedy";
#endif

double heuristic (Grid* entry) {
#ifdef GREEDY
	return abs(entry->x - gx) + abs(entry->y - gy);
#elif defined ASTAR
	return entry->euclidean_distance;
#endif
	//return 0;
}

double score (Grid* entry) {

	return heuristic(entry)
#ifdef ASTAR
	+ entry->moved_distance;
#else
	;
#endif

}

int calc_distance(Grid* start_grid) {

	stack_head = (Grid*)malloc(sizeof(Grid));
	stack_head->next = null;
	stack_head->prev = null;

	start_grid->moved_distance = 0;
	start_grid->conquered = 1;
	push_stack(start_grid);

	while (!(stack_head->next->x == gx && stack_head->next->y == gy) && stack_head->next != null) {
		move_surround(stack_head->next);
	}

	if (stack_head->next == null) return -1;

	int distance = stack_head->next->moved_distance;
	free(stack_head);
	return distance;
}

void move_surround(Grid* entry) {
	move(entry, entry->front, UP);
	move(entry, entry->rear, DOWN);
	move(entry, entry->left, LEFT);
	move(entry, entry->right, RIGHT);
	pop_stack(entry);
	entry->conquered = 1;
	// print_stack();
}

void move(Grid* origin, Grid* destination, char* direction) {
	// printf("attemp move (%d, %d)->(%d, %d) ", origin->x, origin->y, destination->x, destination->y);
	if (destination != null && destination->conquered == 0 && destination->is_obstacle == 0) {
		if (destination->in_stack == 1) {
			if (destination->moved_distance >= origin->moved_distance + 1) { // replacement in stack required
				// printf("Replace\n");
				pop_stack(destination);
				destination->moved_distance = origin->moved_distance + 1;
				destination->origin = origin;
				destination->from_direction = direction;
				push_stack(destination);
			} else {
				// printf("Uneccesary\n");
			} // do nothing (current one is better)
		} else {
			// printf("Insert\n");
			destination->moved_distance = origin->moved_distance + 1;
			destination->origin = origin;
			destination->from_direction = direction;
			push_stack(destination);
		}
	} else {
		// printf("Uneccesary\n");
	}
}

void push_stack(Grid* entry) {
	double h_dis = score(entry);
	Grid* node = stack_head;
	while (node->next != null) {
		if (score(node->next) >= h_dis) {
			entry->next = node->next;
			entry->prev = node;
			node->next->prev = entry;
			node->next = entry;
			break;
		}
		node = node->next;
	}
	if (node->next == null) {
		entry->prev = node;
		entry->next = null;
		node->next = entry;
	}
	// printf("pushed to stack:\nP->");
	// print_grid(entry->prev, 1);
	// printf("E->");
	// print_grid(entry, 1);
	// printf("N->");
	// print_grid(entry->next, 1);
	// print_board();
	entry->in_stack = 1;
}

void pop_stack(Grid* entry) {
	// printf("pop stack: \n");
	// print_grid(entry, 1);
	entry->in_stack = 0;
	if (entry->next != null) {
		entry->next->prev = entry->prev;
	}
	entry->prev->next = entry->next;
	entry->prev = null;
	entry->next = null;
}

void print_stack() {
	int i = 0;
	Grid* node = stack_head->next;
	printf("STACK: \n");
	while (node != null) {
		printf("\t%2d: ", ++i);
		print_grid(node, 0);
		node = node->next;
	}
}