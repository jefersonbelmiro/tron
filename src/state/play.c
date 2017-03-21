#include "state/play.h"
#include "core/window.h"
#include "core/board.h"
#include "core/player.h"
#include "core/ai.h"
#include "core/game.h"
#include "common/ptr_array.h"
#include <curses.h>

static void create(Game* game);
static void update(Game* game);
static void draw(Game* game);
static void destroy(Game* game, State* play);
static void draw_game_over(Game* game);
static int generate_random_number(int min, int max);
static int generate_random_positions(int* alpha_position, int* beta_position, Game* game);
static void create_players(Game* game);
static void start_countdown(Game* game, int count);
static void restart(Game* game);

static PtrArray* players;
static int survivors = 0;
static bool game_over = false;
                                          
State* play_create()
{
    return state_create(create, update, draw, destroy);
}

static void create(Game* game)
{
    window_clear();
    create_players(game);
    start_countdown(game, 3);
}

static void destroy(Game* game, State* play)
{
    ptr_array_destroy(players);
    state_destroy(play);
}

static void update(Game* game)
{
    if (game_over) {

        //restart
        if (game->input->key == KEY_ENTER || game->input->key == 10) {
            restart(game);
        }

        return;
    }

    LightCycle* player;
    survivors = 0;

    for (int player_index = 0; player_index < players->length; player_index++) {

        player = ptr_array_get(players, player_index);

        if (!player->alive) {

            game->board->map[player->position] = '#' | COLOR_PAIR(WHITE); 
            continue;
        }

        survivors++;

        player->update(game, player, players);
        game->board->map[player->position] = '#' | COLOR_PAIR(player->color); 
    }

    if (survivors <= 1) {
        game_over = true;
    }
}

static void draw(Game* game)
{
    board_draw(game->board);

    if (game_over) {
        draw_game_over(game);
    } 
}

static void draw_game_over(Game* game)
{
    char *text = " YOU LOST ";
    if (((LightCycle *) ptr_array_get(players, 0))->alive) {
        text = " YOU WON ";
    }
    int x = (game->board->width / 2) - strlen(text)/2;
    attron(COLOR_PAIR(COLOR_WHITE));
    window_draw_string(x, 0, text); 
    attroff(COLOR_PAIR(COLOR_WHITE));
}

static void restart(Game* game)
{
    for (int player_index = 0; player_index < players->length; player_index++) {
        LightCycle* player = ptr_array_get(players, player_index);
        light_cycle_destroy(player);
    }

    board_clear(game->board);
    board_create_bound(game->board);

    game_over = false;
    create(game);
}

static int generate_random_number(int min, int max)
{
    if (max <= min) {
        return min;
    }
    return (rand() % (max - min)) + min;
}

static int generate_random_positions(int* alpha_position, int* beta_position, Game* game)
{
    srand(time(NULL));
    int alpha_x, alpha_y, beta_x = 0, beta_y = 0;
    int min_x = 3;
    int min_y = 3;
    int max_x = game->board->width - 4;
    int max_y = game->board->height - 4;
    int min_dist = 5;

    alpha_x = generate_random_number(min_x, max_x);
    alpha_y = generate_random_number(min_y, max_y);
    *alpha_position = alpha_x + alpha_y * game->board->width;

    do {

        beta_x = generate_random_number(min_x, max_x);
        beta_y = generate_random_number(min_y, max_y);

    } while( abs(alpha_x - beta_x) < min_dist || abs(alpha_y - beta_y) < min_dist);

    *beta_position = beta_x + beta_y * game->board->width;
}

static void create_players(Game* game)
{
    players = ptr_array_create(2);

    int player_pos, ai_pos;
    generate_random_positions(&player_pos, &ai_pos, game);

    LightCycle* player = player_create(player_pos, BLUE, RIGHT);
    LightCycle* ai = ai_create(ai_pos, RED, LEFT);

    ptr_array_push(players, player);
    ptr_array_push(players, ai);

    game->board->map[player_pos] = '#' | COLOR_PAIR(player->color); 
    game->board->map[ai_pos] = '#' | COLOR_PAIR(ai->color); 
}

static void start_countdown(Game* game, int count)
{
    board_draw(game->board);

    while(count-- > 0) {

        char text[20];
        sprintf(text, " START IN %d ", count);
        int x = (game->board->width / 2) - strlen(text)/2;

        attron(COLOR_PAIR(COLOR_WHITE));
        window_draw_string(x, 0, text); 
        attroff(COLOR_PAIR(COLOR_WHITE));
        window_refresh();

        sleep(1);
    }
}
