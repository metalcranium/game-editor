#include "map.hpp"
#include "raylib.h"
#include "rlgl.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include "game.cpp"


class Mouse {
public:
  int x;
  int y;

  void get_mouse_vector(float grid_size) {
    x = GetMouseX() / grid_size;
    y = GetMouseY() / grid_size;
  }
  int get_mouse_x() { return GetMouseX() / 32; }
  int get_mouse_y() { return GetMouseY() / 32; }
  void print_mouse_vector() {
    std::cout << x / 32 << "," << y / 32 << std::endl;
  }
  void update_mouse(Map &map) {}
};

// void cameraInput(Camera2D camera);
// void cameraUpdate(Camera2D camera);

int main() {
  // screen information
  std::cout << "main\n";

  int screen_width = 2000;
  int screen_height = 1200;
  InitWindow(screen_width, screen_height, "Level Editor");
  SetTargetFPS(60);

  // Load map information

  int current_rec = 0;
  std::unique_ptr<Mouse> mouse = std::make_unique<Mouse>();

  // Camera information
  Camera2D camera;
  camera.offset = {200, 200};
  camera.rotation = 0;
  camera.zoom = 2;

  float speed = 300.0;

  RenderTexture view_port = LoadRenderTexture(screen_width/2, screen_height);
  Rectangle screen_rect = {0.0,0.0,float(view_port.texture.width), -float(view_port.texture.height)};
  

  Tile tile;
  std::unique_ptr<Map> map = std::make_unique<Map>();
  map->map_name = "map.txt";
  map->atlas = LoadTexture("forestgroundtileset.png");
  map->grid_size = 32;
  map->vec_size = 50;
  map->make_map();
  map->load_map();
  int map_size = map->vec_size * map->grid_size;
  std::cout << "map\n";
  // Game loop
  while (!WindowShouldClose()) {
    // Udating goes below here
    // Mouse location information
    mouse->get_mouse_vector(float(map->grid_size));
    mouse->update_mouse(*map);
    // User/mouse input
    if (mouse->x * map->grid_size < map_size && mouse->y * map->grid_size >= 0 && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        map->level_map[mouse->x][mouse->y]->source = tile.source;
        map->level_map[mouse->x][mouse->y]->is_solid = false;
       }
    else if (mouse->x * map->grid_size < map_size && mouse->y * map->grid_size >= 0 && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
             map->level_map[mouse->x][mouse->y]->source = tile.source;
             map->level_map[mouse->x][mouse->y]->is_solid = true;
      }
    else if (mouse->x * map->grid_size >= map_size && mouse->y * map->grid_size >= 0 &&
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Rectangle current_tile =
          (Rectangle){float(mouse->x - map->vec_size) * map->grid_size,
                      float(mouse->y) * map->grid_size, float(map->grid_size), float(map->grid_size)};
      tile.source = current_tile;
      std::cout << "Tile Source: " << tile.source.x << "," << tile.source.y << std::endl;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

      std::cout << "Mouse Location: " << mouse->x << "," << mouse->y
                << std::endl;
    }
    if (IsKeyPressed(KEY_ENTER)) {
      map->save_map();
    }
    
    if (IsKeyPressed(KEY_F5)){
      runGame(screen_width, screen_height, *map);
      main();
    }
        // Drawing information

    BeginTextureMode(view_port);
    BeginMode2D(camera);


    map->draw_map();

    EndMode2D();
    EndTextureMode();

    BeginDrawing();

    // This is just for a little bit of screen formatting to make look more
    // readable

    // DrawRectangle(0, 0, map->vec_size * map->grid_size, screen_height, GRAY);
    // DrawRectangle(map->vec_size * map->grid_size, 0, screen_width - map->vec_size * map->grid_size, screen_height, DARKGRAY);
    DrawTextureRec(view_port.texture, screen_rect, {0,0}, WHITE);

    // Drawing the map/atlas


    DrawTexture(map->atlas, map->vec_size * map->grid_size, 0, RAYWHITE);
    ClearBackground(BLACK);
    EndDrawing();
  }
  CloseWindow();

}
