Dependancies:
Raylib
Zig
*DISCLAIMER* These are the only dependancies that I needed for arch linux. If you are using another operating system you may need
to download whatever ones are needed for raylib and/or C++.

-Run the Commands below.
zig c++ main.cpp -lraylib Character.cpp map.cpp Resource.cpp -o Editor
./Editor


Replace the text in map->atlas = LoadTexture("forestgroundtileset.png") to change the atlas.
Example is map->atlas = LoadTexture("path/to/tileset.png")

-Controls
Left click the atlas that you want to select.
To draw left click any area to draw the selected tile.
Right click if you want this tile to be solid. This will set a is_solid to true.
Enter to save the map and export to txt file. This file is in a csv type format. 
Also all solid tiles with save with a 1 in the text file and non solids will be 0.
