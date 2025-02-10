#ifndef GAME_HPP
#define GAME_HPP

#include <board.hpp>

class Game
{
public:
    Game();
    ~Game();
    void loadFEN(std::string fen);
    char* getPlainBoard();
    void setPlainBoard(char* board);
private:
    Board _board;
};

#endif