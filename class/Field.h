#include <vector>
#include "History.h"

class Field
{
public:
    char data[8][8];

    std::vector<Move> get_moves(int player);
    Field apply_move(Move m, Field &now);
    bool is_alive(int player);

private:
    int is_busy(int player, int i, int j);
    std::vector<Move> figure_moves(int i, int j, char figure, int player);
};