#include "Move.h"

Step::Step(int i, int j)
{
    this->i = i;
    this->j = j;
}

Step::Step()
{
    this->i = 0;
    this->j = 0;
}

Move::Move(Step from, Step to, char figure)
{
    this->from = from;
    this->to = to;
    this->figure = figure;
}

Move::Move()
{
    this->from = Step();
    this->to = Step();
    this->figure = '0';
}

bool Move::operator==(Move &right)
{
    int count = 0;

    if (this->from.i == right.from.i)
        count++;
    if (this->from.j == right.from.j)
        count++;
    if (this->to.i == right.to.i)
        count++;
    if (this->to.j == right.to.j)
        count++;
    if (this->figure == right.figure)
        count++;

    return (count == 5) ? true : false;
}

std::string Move::convert()
{
    std::string result = "";

    result += "[";
    result += (char)(65 + (from.j + 1));
    result += (char)(48 + 8 - from.i);
    result += "]->[";
    result += (char)(65 + (to.j + 1));
    result += (char)(48 + 8 - to.i);
    result += "]";

    return result;
}