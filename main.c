#include <stdio.h>
#include "calc.h"
#include <time.h>

const int width 	= 15; 	// 横幅
const int height 	= 15; 	// 縦幅
const int start_x 	= 0; 	// 開始x
const int start_y 	= 7; 	// 開始y
const int goal_x 	= 14; 	// 終点x
const int goal_y 	= 7; 	// 終点y

int main (void) {

	clock_t start = clock();

	// グリッドを生成
	Grid* board_start = generate_board(width, height, start_x, start_y, goal_x, goal_y);

	// 壁を描く部分
	for (int i = 1; i < 14; i++) {
		set_obstacle(13, i);
		set_obstacle(i, 13);
	}

	for (int i = 8; i < 13; i++) {
		set_obstacle(1, i);
	}

	for (int i = 2; i < 13; i++) {
		set_obstacle(i, 8);
	}
	
	for (int i = 0; i < 12; i++) {
		set_obstacle(i, 6);
		set_obstacle(i+1, 4);
		set_obstacle(i, 2);
	}

	// 計算する
	int d = calc_distance(board_start);
	if (d > 0) {
		printf("%s, min distance: %d\n", mode, d);
		traverse();
		printf("\nBOARD:\n");
		printf("\033[036mIn exlpore queue: \t(Number)\n");
		printf("\033[033mExplored Terrain: \t(Number)\n");
		printf("\033[031mOptimized Path: \t(Number)(Arrow)\n");
		printf("\033[35mObstacle:\t\t++++\033[00m\n");
		printf("Unexplored Terrain:\t*\n");
		print_board();
	} else {
		printf("%s: no path found!\n", mode);
	}
	clear_board();

	printf("total execution time: %f\n", (float)(clock() - start) / CLOCKS_PER_SEC);

	return 0;
}