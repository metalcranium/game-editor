#pragma once
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

struct Tile {
  Rectangle source;
  Rectangle collision;
  bool is_solid;
};
class Map {
public:
  int width;
  int height;
  int grid_size;
  int vec_size;
  std::string map_name;
  Texture2D atlas;
  std::vector<std::vector<std::shared_ptr<Tile>>> level_map;

  Map();
  ~Map();
  void make_map();
  void draw_map();
  void save_map();
  void load_map();
};
