#include "raylib/include/raylib.h"
#include "raylib/include/rlgl.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ROWS 50
#define COLS 90
#define MARGIN 0
#define CELL_SIZE 20
#define OFFSET (CELL_SIZE + MARGIN)

int front[ROWS][COLS] = {0};
int back[ROWS][COLS] = {0};

long generation = 0;

void displayFront() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      Vector2 pos = {j * OFFSET, OFFSET * i};
      if (front[i][j]) {
        DrawRectangleV(pos, (Vector2){CELL_SIZE, CELL_SIZE}, RAYWHITE);
      } else {
        DrawRectangleV(pos, (Vector2){CELL_SIZE, CELL_SIZE}, BLACK);
      }
    }
  }
}

void clear() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      front[i][j] = 0;
    }
  }
}

int countNeighbors(int x, int y) {
  int start_x = 0;
  int end_x = COLS;

  int start_y = 0;
  int end_y = ROWS;

  int neighbors = 0;

  if (x != 0) {
    start_x = x - 1;
  }
  if (x != COLS) {
    end_x = x + 1;
  }
  if (y != 0) {
    start_y = y - 1;
  }
  if (y != COLS) {
    end_y = y + 1;
  }
  for (int i = start_y; i <= end_y; ++i) {
    for (int j = start_x; j <= end_x; ++j) {
      if (i == y && j == x) {
        continue;
      }
      if (front[i][j] == 1) {
        neighbors++;
      }
    }
  }
  return neighbors;
}
void applyBackToFront() {
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      if (back[y][x] == 2) {
        // death
        front[y][x] = 0;
      } else if (back[y][x] == 3) {
        // ressurection
        front[y][x] = 1;
      }
    }
  }
}

void step() {
  generation += 1;
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      int numOfNeighbors = countNeighbors(x, y);
      // printf("(%d, %d) has %d neighbors\n", x, y, numOfNeighbors);
      if (front[y][x]) {
        if (numOfNeighbors < 2) {
          // if it's ded we put 2
          back[y][x] = 2;
        } else if (numOfNeighbors > 3) {
          back[y][x] = 2;
        }
      } else {
        if (numOfNeighbors == 3) {
          // surrection is 3
          back[y][x] = 3;
        }
      }
    }
  }
}

long countPopulation() {
  long pop = 0;
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      if (front[y][x]) {
        pop += 1;
      }
    }
  }
  return pop;
}

int main() {
  int windowWidth = COLS * CELL_SIZE + (COLS * MARGIN);
  int windowHeight = ROWS * CELL_SIZE + (ROWS * MARGIN);
  // WARN: this doesn't work for some reason
  // int numOfMonis = GetMonitorCount();
  // int currentMoni = GetCurrentMonitor();
  // printf("number of moni: %d\n", numOfMonis);
  // printf("current moni: %d\n", currentMoni);
  // SetWindowMonitor(1);
  InitWindow(windowWidth, windowHeight, "deez games");
  SetTargetFPS(60);
  int paused = 1;
  char pausedStr[50];

  // Vector2 rectSize = {CELL_SIZE, CELL_SIZE};

  while (!WindowShouldClose()) {

    // do some calculations ands stuff
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 mouse = GetMousePosition();

      int x = (mouse.x - OFFSET) / CELL_SIZE + 1;
      int y = (mouse.y - OFFSET) / CELL_SIZE + 1;
      x = x < 0 ? 0 : x;
      y = y < 0 ? 0 : y;
      // x = x > windowWidth  ? COLS-1 : x;
      // y = y > windowHeight ? ROWS-1 : y;
      front[y][x] = 1;
    }

    if (IsKeyPressed(KEY_P)) {
      paused = paused ? 0 : 1;
    }
    if (IsKeyPressed(KEY_S)) {
      if (paused) {
        step();
      }
    }
    if (IsKeyPressed(KEY_R)) {
      clear();
      displayFront();
    }

    if (!paused) {
      step();
      sprintf(pausedStr, " ");
    } else {
      sprintf(pausedStr, "paused");
    }
    // apply changes
    applyBackToFront();

    // count population
    long population = countPopulation();

    // display the dingus
    displayFront();

    // info text
    DrawText(TextFormat("Generation: %ld", generation), 20, 20, 25, RED);
    DrawText(TextFormat("Population: %ld", population), 20, 50, 25, RED);
    DrawText(pausedStr, windowWidth / 2 - 200, windowHeight / 2 - 100, 100, RED);
    // TODO: keys

    EndDrawing();
  }
  CloseWindow();
}
