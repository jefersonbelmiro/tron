#include "core/negamax.h"

// unit-cost specialization of dijkstra's algorithm 
int* negamax_create_dist_map(int* map, int map_width, int map_height, int map_position) 
{
    int map_length = map_width * map_height;
    int map_moves[4] = {-1, -map_width, 1, map_width };
    int dist_score = 1;

    int* dist_map = malloc(sizeof(int) * map_length);
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

