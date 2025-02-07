#ifndef GAME_HPP
#define GAME_HPP

#include <board.hpp>

class Game
{
public:
    Game();
    ~Game();
    void loadFEN(char *fen);
    char* getPlainBoard();
private:
    Board _board;
};

#endif