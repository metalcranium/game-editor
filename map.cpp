#include "map.hpp"
#include <memory>

Map::Map() { std::cout << "Map object created successfully" << std::endl; }
Map::~Map() { std::cout << "Map closed successfully" << std::endl; }

void Map::make_map() {
  level_map.resize(vec_size, std::vector<std::shared_ptr<Tile>>(vec_size));
  for (int row = 0; row < vec_size; row++) {
    for (int column = 0; column < level_map.size(); column++) {
      if (level_map[row][column] == NULL) {
        std::shared_ptr<Tile> tile = std::make_shared<Tile>();
        tile->source.x = {};
        tile->source.y = {};
        tile->source.width = grid_size;
        tile->source.height = grid_size;
        tile->is_solid = false;
        level_map[row][column] = tile;
        std::cout << level_map[row][column]->source.x << "," << level_map[row][column]->source.y << std::endl;
      }
    }
  }
  std::cout << "Map has been set up\n";
}

void Map::draw_map() {
  for (int row = 0; row < vec_size; row++) {
    for (int column = 0; column < level_map.size(); column++) {
        level_map[row][column]->collision.width = grid_size;
        level_map[row][column]->collision.height = grid_size;
        level_map[row][column]->collision.x = row*grid_size;
        level_map[row][column]->collision.y = column*grid_size;
        DrawTextureRec(
            atlas, level_map[row][column]->source,
            (Vector2){float(row * grid_size), float(column * grid_size)},
            RAYWHITE);
           
    }
  }
}
void Map::save_map() {
  std::cout << "save function\n";
  std::ofstream file;
  file.open(map_name);
  std::cout << "txt opened\n";

  for (int row = 0; row < level_map.size(); row++) {
    std::cout << "row\n";
    for (int column = 0; column < vec_size; column++) {
      std::cout << "column\n";
      file << int(level_map[row][column]->source.x) << " "
           << int(level_map[row][column]->source.y) << " "
           << level_map[row][column]->is_solid
           << "\n"; //<< row * grid_size << "," << column * grid_size << ",";
      std::cout << level_map[row][column]->source.x << ","
                << level_map[row][column]->source.y;
    }
  }
  file.close();
}
void Map::load_map() {
  std::fstream file;
  file.open(map_name);
    std::string line;
    int num1;
    int num2;
    int num3;
    Rectangle source = (Rectangle){float(num1), float(num2), 32, 32};
    for (int row = 0; row < level_map.size(); row++) {
      for (int column = 0; column < vec_size; column++) {
        file >> num1 >> num2 >> num3;
        source.x = num1;
        source.y = num2;
        level_map[row][column]->source = source;
        level_map[row][column]->is_solid = num3;
      }
    }
    std::cout << "end of load_map" << std::endl;
}
