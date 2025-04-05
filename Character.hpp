#pragma once
#include "game_components.hpp"
#include <raylib.h>
#include <list>
#include <memory>
#include <raymath.h>
#include <vector>
#include "Item.hpp"

class Projectile;
class Item;

class Character{
  public:
    Vector2 position;
    const float speed = 100;
    float current_speed;
    float jump_speed;
    float jump_height;
    float max_jump_height;
    Vector2 velocity;
    float width;
    float height;
    Rectangle collision;
    Rectangle image_direction;
    Texture2D texture;
    std::list<std::shared_ptr<Projectile>>projectiles;
    std::vector<Item>inventory;
    int item_count;
    bool is_blocked;

    Character();
    ~Character();

    void ready();
    void draw();
    void update();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void input();
    void fire();
    void populate_projectiles();
    void update_projectiles();
};

class Projectile{
  public:
    Rectangle shape;
    Vector2 velocity;
    Vector2 position;
    const float speed = 100;

};
