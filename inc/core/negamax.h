#ifndef NEGAMAX_H
#define NEGAMAX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

int* negamax_create_dist_map(int* map, int map_width, int map_height, int map_position);
int negamax_evaluate_position(int* map, int map_width, int map_height, int alpha_position, int beta_position);
int negamax(int* map, int map_width, int map_height, 
            int alpha_position, int beta_position, int depth, int alpha, int beta, int best_move);
void negamax_print_dist_map(int* dist_map, int map_width, int map_height);

#endif
