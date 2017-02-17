#include "common/test.h"
#include "core/negamax.h"

int width = 10;
int height = 10;
int* map = NULL;

void test_dist_map()
{
    int x = width/2, y = height/2;
    int map_position = x + y * width;
    int* dist_map = negamax_create_dist_map(map, width, height, map_position);

    // up and down
    for (int i = 0; i < height/2; i++) {
        assert_equal(dist_map[x + (y- (i+1)) * width], i + 2);
        assert_equal(dist_map[x + (y+i) * width], i + 1);
    }

    // left and right
    for (int i = 0; i < width/2; i++) {
        assert_equal(dist_map[(x - (i + 1)) + y * width], i + 2);
        assert_equal(dist_map[x + i + y * width], i + 1);
    } 
}

void test_evaluate_position()
{
    int alpha_x = width/2;
    int alpha_y = height/2;
    int alpha_position = alpha_x + alpha_y * width;

    int beta_x = 1;
    int beta_y = 1;
    int beta_position = beta_x + beta_y * width; 

    map[alpha_position] = 1;
    map[beta_position] = 1;

    int score = negamax_evaluate_position(map, width, height, alpha_position, beta_position);

    assert_equal(score, 16);
}

void test_negamax()
{
    int alpha_x = width/2;
    int alpha_y = height/2;
    int alpha_position = alpha_x + alpha_y * width;

    int beta_x = 1;
    int beta_y = 1;
    int beta_position = beta_x + beta_y * width; 

    int alpha_move = 1;

    map[alpha_position] = 1;
    map[beta_position] = 1;

    int best_move = negamax(
        map, 
        width, 
        height, 
        alpha_position, 
        beta_position, 
        6,
        -99999, 
        99999,
        alpha_move
    );

    assert_equal(best_move, 2);
}

void test_setup()
{
    map = calloc(width * height, sizeof(int));
}

void test_teardown()
{
    free(map);
    map = NULL;
}

int main(int argc, char* argv[]) 
{
    describe("negamax()", {
        setup(test_setup);
        teardown(test_teardown);
        it("test unit-cost specialization of dijkstra's algorithm", test_dist_map);
        it("test evaluate position", test_evaluate_position);
        it("test negamax algorithm", test_negamax);
    });

    return Test_run();
}
