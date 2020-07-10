#include <string>
#include <fstream>
#include "Field.h"

class Game
{
public:
    int main_player;
    History strategies;

    void start(int player);
    void history();
    Game(std::string filename);

private:
    Field game_field;

    void append_move(int depth, Move m, Strategy &s, int count);

    int now_recursion(int, Move, Field, Strategy, int);
    int resulter(int old_counter, int part, int player);
    int resulter_no_moves(int player, int depth);
};