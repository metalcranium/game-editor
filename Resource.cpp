#include "Resource.hpp"
#include <raylib.h>
#include <iostream>

Resource::Resource(){
  ready();  
}
Resource::~Resource(){
  std::cout << "resource freed " << std::endl;
}
void Resource::ready(){
  health = 10;
  drop_count = 5;
  position = (Vector2){100, 100};
  is_solid = true;
}

void Resource::draw(){
  DrawRectangle(position.x, position.y, 32, 32, BROWN);
}
void Resource::update(){
  if (health <= 0){
    drop_loot();
    Resource::~Resource();
  }
}
void Resource::drop_loot(){
  std::cout << "loot droped" << std::endl;
}
