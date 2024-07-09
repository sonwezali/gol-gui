#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define COLS 96
#define ROWS 54
// 20px*20px squares
int sq = 20;

int grid[ROWS][COLS] = {0};
int nextGrid[ROWS][COLS] = {0};

int nextState[2][9] = {
                        {0, 0, 0, 1, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0, 0, 0, 0}
                      };

int neighbors[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},
                        { 0, -1}, { 0, 1},
                        { 1, -1}, { 1, 0}, { 1, 1}
                      };

int randomState() {
    float x = (float)rand()/(float)RAND_MAX;
    return (x > 0.5f) ? 1 : 0;
}

void computeLiveNeighbors(int y, int x, int *c) {
    for (size_t i = 0; i < sizeof(neighbors)/sizeof(neighbors[0]); i++) {
        if (grid[(y + neighbors[i][0] + ROWS) % ROWS][(x + neighbors[i][1] + COLS) % COLS]) *c = *c + 1;
    }
}

void computeNextGrid() {
    int liveNeighbor = 0;
    for (size_t y = 0; y < ROWS; y++) {
        for (size_t x = 0; x < COLS; x++) {
            computeLiveNeighbors(y, x, &liveNeighbor);
            nextGrid[y][x] = nextState[grid[y][x]][liveNeighbor];
            liveNeighbor = 0;
        }
    }

    for (size_t y = 0; y < ROWS; y++) {
        for (size_t x = 0; x < COLS; x++) {
            grid[y][x] = nextGrid[y][x];
        }
    }
}

void initGrid() {
    srand(time(NULL));
    for (size_t y = 0; y < ROWS; y++) {
        for (size_t x = 0; x < COLS; x++) {
            grid[y][x] = randomState();
        }
    }
}

void delay(int n) {
    int tn = 1000 * n;
    clock_t start_time = clock();
 
    while (clock() < start_time + tn);
}

void drawGrid(){
    for (size_t y = 0; y < ROWS; y++) {
        for (size_t x = 0; x < COLS; x++) {
            if (grid[y][x])
                DrawRectangleV((Vector2){x * sq, y * sq}, (Vector2){16.0, 16.0}, MAGENTA);
        }
    }
}

int main() {
    int screenWidth = COLS * sq;
    int screenHeight = ROWS * sq;
    InitWindow(screenWidth, screenHeight, "game of life");

    initGrid();

    while (!WindowShouldClose()) {
        delay(150);
        computeNextGrid();
        ClearBackground(BLACK);
        BeginDrawing();
            drawGrid();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

