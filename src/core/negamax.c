#include "core/negamax.h"

// unit-cost specialization of dijkstra's algorithm 
int* negamax_create_dist_map(int* map, int map_width, int map_height, int map_position) 
{
    int map_length = map_width * map_height;
    int map_moves[4] = {-1, -map_width, 1, map_width };
    int dist_score = 1;

    int* dist_map = calloc(map_length, sizeof(int));
    dist_map[map_position] = 1;

    int queue[map_length];
    int queue_length = 1;
    queue[0] = map_position;

    while (queue_length) {

        dist_score++;

        int buff[map_length];
        int buff_length = 0;

        for (int i = 0; i < queue_length; i++) {

            int curr_pos = queue[i];

            for (int move = 0; move < 4; move++) {

                int next_pos = curr_pos + map_moves[move];

                // bounding 
                // @TODO not necessary after adding walls to the corners
                if (next_pos < 0 || next_pos > map_length) continue;

                // first column, ignore left move
                // @TODO not necessary after adding walls to the corners
                if (move == 0 && curr_pos % map_width == 0) continue;

                // last column, ignore right move
                // @TODO not necessary after adding walls to the corners
                if (move == 2 && (curr_pos + 1) % map_width == 0) continue;

                // duplicate move
                if (map[next_pos] || dist_map[next_pos]) continue;

                dist_map[next_pos] = dist_score;
                buff[buff_length++] = next_pos;
            }
        }

        memcpy(queue, buff, map_length);
        queue_length = buff_length;
    }

    return dist_map;
}

void negamax_print_dist_map(int* dist_map, int map_width, int map_height)
{
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            printf("[%3d]", dist_map[x + y * map_width]);
        }
        printf("\n");
    } 
}

int negamax_evaluate_position(int* map, int map_width, int map_height, int alpha_position, int beta_position)
{
    int score = 0;
    int map_length = map_width * map_height;
    int* alpha_dist_map = negamax_create_dist_map(map, map_width, map_height, alpha_position);
    int* beta_dist_map = negamax_create_dist_map(map, map_width, map_height, beta_position);

    for (int i = 0; i < map_length; i++) {

        if (map[i]) {
            continue;
        }

        if (alpha_dist_map[i] && beta_dist_map[i]) {
            int diff = alpha_dist_map[i] - beta_dist_map[i];
            if (diff < 0) {
                score++;
            } else {
                score--;
            }
        } 
        else if (alpha_dist_map[i]) score++;
        else if (beta_dist_map[i]) score--; 
    }

    return score;
}

int negamax(int* map, int map_width, int map_height, 
            int alpha_position, int beta_position, int depth, int alpha, int beta, int best_move)
{
    if (depth == 0) return negamax_evaluate_position(map, map_width, map_height, alpha_position, beta_position);

    int map_moves[4] = {-1, -map_width, 1, map_width };

    for (int move = 0; move < 4; move++) {

        int next_pos = alpha_position + map_moves[move];

        if (map[next_pos]) {
            continue;
        }

        map[next_pos] = 1;
        int score = -negamax(map, map_width, map_height, beta_position, next_pos, depth - 1, -beta, -alpha, -1);
        map[next_pos] = 0;

        if (score > alpha) {

            alpha = score;
            best_move = best_move != -1 ? move : -1;

            // alpha-beta pruning
            if (alpha >= beta) {
                break;
            }
        }
    }

    if (best_move != -1) {
        return best_move;
    }

    return alpha;
}
