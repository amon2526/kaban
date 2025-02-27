#ifndef LAYOUT_MANAGER_HPP
#define LAYOUT_MANAGER_HPP

#include <navigation.hpp>
#include <string>
#include <unordered_map>

struct Sector {
  int x, y, width, height;
};

class LayoutManager {
private:
  std::unordered_map<std::string, Sector> sectors;

public:
  void defineSector(const std::string &name, int x, int y, int w, int h) {
    sectors[name] = {x, y, w, h};
  }

  const Sector &getSector(const std::string &name) const {
    return sectors.at(name);
  }

  Square getBoardSquarePosition(int mouseX, int mouseY) const {
    Sector gameSector = getSector("game");
    if (mouseX < gameSector.x || mouseX > gameSector.x + gameSector.width ||
        mouseY < gameSector.y || mouseY > gameSector.y + gameSector.height)
      return SQ_NONE;

    int cellSizeX = gameSector.width / 8;
    int cellSizeY = gameSector.height / 8;

    int col = (mouseX - gameSector.x) / cellSizeX;
    int row = ((gameSector.height - mouseY) - gameSector.y) / cellSizeY;

    return (Square)(row * 8 + col);
  }
};

#endif