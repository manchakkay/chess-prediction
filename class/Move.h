#include <string>

class Step
{
public:
    int i = 0;
    int j = 0;

    Step(int i, int j);
    Step();
};

class Move
{
public:
    Step from;
    Step to;
    char figure;

    Move(Step from, Step to, char figure);
    Move();

    std::string convert();

    bool operator==(Move &h);
    bool operator<(Move &r)
    {
        if (figure != r.figure)
        {
            return figure < r.figure;
        }
        else
        {
            if (from.i != r.from.i)
            {
                return from.i < r.from.i;
            }
            else
            {
                if (from.j != r.from.j)
                {
                    return from.j < r.from.j;
                }
                else
                {
                    if (to.i != r.to.i)
                    {
                        return to.i < r.to.i;
                    }
                    else
                    {
                        if (to.j != r.to.j)
                        {
                            return to.i < r.to.j;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }
        }

        return false;
    }
};