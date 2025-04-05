#pragma once
#include <raylib.h>

enum Type{
  wood,
  stone,
  metal,
};

class Resource{
  public:
    Vector2 position;
    int health;
    int drop_count;
    bool is_solid;
    Type resource_type;


    Resource();
    ~Resource();
    virtual void ready();
    virtual void draw();
    virtual void update();
    virtual void drop_loot();
};

