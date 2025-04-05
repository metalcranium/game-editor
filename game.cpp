#include "raylib.h"
#include "rlgl.h"
#include <memory>
#include <vector>
#include "map.hpp"
#include "Character.hpp"
#include "game_components.hpp"
// #include "Item.hpp"
#include "Resource.hpp"
#include <iostream>

void runGame(int screen_width, int screen_height, Map map){
  map.load_map();
  std::unique_ptr<Character>player = std::make_unique<Character>();
  std::shared_ptr<Resource>resource = std::make_shared<Resource>();
  // std::vector<std::shared_ptr<Resource>>resources;
  // resources.push_back(resource);
  std::string count = std::to_string(player->item_count);
  Camera2D camera;
  camera.target = player->position;
  camera.offset = (Vector2){screen_width/2.0f, screen_height/2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 2.0f;
  while(!WindowShouldClose()){
    player->update();
  // TODO: update camera position.
    camera.target = player->position;
    camera.offset = GetScreenToWorld2D(camera.target, camera);
    if (resource->health >= 0) {
      resource->update();
    }
    for (int i = 0; i < map.level_map.size(); i++ ){
      for(int j = 0; j < map.vec_size; j++){
        auto block = map.level_map[i][j];
        if (block->is_solid && player->position.x > block->collision.x - player->width && 
                               player->position.x < block->collision.x + player->width&&
                               player->position.y > block->collision.y - player->height && 
                               player->position.y < block->collision.y + player->height){
          // player->position.x -= player->velocity.x * player->current_speed * GetFrameTime();
          // player->position.y -= player->velocity.y * player->current_speed * GetFrameTime();                
          player->is_blocked = true;
          std::cout << "Blocked" << std::endl;
        }else{
          player->is_blocked = false;
          std::cout << "Not blocked" << std::endl;
        }
      }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > resource->position.x - 32 && 
                               GetMouseX() < resource->position.x + 32 &&
                               GetMouseY() > resource->position.y - 32 && 
                               GetMouseY() < resource->position.y + 32 && 
                               player->position.x - resource->position.x <= 40 && player->position.y - resource->position.y <= 40
        ){
      std::cout << "resource clicked" << std::endl;
      // std::cout << "resource position: " << resource.position.x << "," << resource.position.y << std::endl;
      // std::cout << "mouse position: " << GetMouseX() << "," << GetMouseY() << std::endl;
      resource->health -= 5;
      
    }
    if (IsKeyPressed(KEY_F8)){
      break;
    }

    BeginDrawing();
    BeginMode2D(camera);
    map.draw_map();
    player->draw();
    if (resource->health > 0){
      resource->draw();
    }

    DrawText(TextFormat("%i", player->item_count), 50, 50, 50, BLACK);
    //DrawText("Run game function", screen_width/2, screen_height/2, 50, GRAY);
        
    ClearBackground(BLACK);
    
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
  

}
// void updateCollisions(){
  
// }
