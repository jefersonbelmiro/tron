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

void test_setup()
{
    map = malloc(sizeof(int) * width * height);
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
    });

    return Test_run();
}
