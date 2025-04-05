#include <iostream>
#include "Character.hpp"
#include <raylib.h>
#include <raymath.h>

Character::Character(){
  ready();
};

Character::~Character(){};

void Character::ready(){
  position = (Vector2){300,300};
  current_speed = speed;
  jump_speed = 1000;
  max_jump_height = 200;
  width = 25;
  height = 32;
  velocity = (Vector2){0,1};
  collision.x = width;
  collision.y = height;
  texture = LoadTexture("hero.png");
  image_direction = (Rectangle){0, 0, 32, 32};
  is_blocked = false;
}

void Character::update(){
  std::cout << is_blocked << std::endl;
  // std::cout << position.x << "," << position.y << std::endl;
  input();
  position.x += velocity.x * current_speed * GetFrameTime();
  position.y += velocity.y * current_speed * GetFrameTime();
  // TODO fix this blocking
  if (is_blocked){
    velocity = {0,0};
  }
  update_projectiles();
}
void Character::draw(){
  DrawTextureRec(texture,image_direction, (Vector2){position.x, position.y},RAYWHITE);
  populate_projectiles();
}

void Character::moveRight(){
  velocity.x = 1;
}
void Character::moveLeft(){
  velocity.x = -1;
}
void Character::moveUp(){
  velocity.y = -1;
}
void Character::moveDown(){
  velocity.y = 1;
}
void Character::fire(){
  std::shared_ptr<Projectile>projectile = std::make_shared<Projectile>();
  projectile->shape = (Rectangle){position.x + (width/2), position.y, 10, 10};
  projectile->velocity = Vector2Normalize((Vector2){GetMousePosition().x - position.x, GetMousePosition().y - position.y});
  std::cout << GetMouseX() << "," << GetMouseY() << std::endl;
  projectiles.push_back(projectile);
}
void Character::populate_projectiles(){
  for (auto i : projectiles){
    DrawRectangleRec(i->shape, ORANGE);
  }
}
void Character::update_projectiles(){
  for (auto i : projectiles){
    i->shape.x += i->velocity.x * i->speed * GetFrameTime();
    i->shape.y += i->velocity.y * i->speed * GetFrameTime();
  }
}
void Character::input(){
  if (IsKeyDown(KEY_RIGHT)){
    image_direction.width = -32;
    moveRight();
  }  
  else if(IsKeyDown(KEY_LEFT)){
    image_direction.width = 32;
    moveLeft();
  }
  else{
    velocity.x = 0;
  }

  if(IsKeyDown(KEY_DOWN)){
    moveDown();
  }
  else if(IsKeyDown(KEY_UP)){
    moveUp();
  }
  // else{
  //   velocity.y = 0;
  // }
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    fire();
  }
}
