#include <vector>
#include "Move.h"
#include <tuple>

class Strategy
{
public:
    int type = 0;

    Move m1;
    double strats1 = 0;
    Move m2;
    double strats2 = 0;
    Move m3;
};

class Formatted_Strategy
{
public:
    int type = 0;

    Move m1;
    double m2_found = 1;
    double m2_all = 1;
    Move m2;
    double m3_found = 1;
    double m3_all = 1;
    Move m3;

    bool operator<(Formatted_Strategy &r)
    {
        if (!(m1 == r.m1))
        {
            return m1 < r.m1;
        }
        else
        {
            if (!(m2 == r.m2))
            {
                return m2 < r.m2;
            }
            else
            {
                if (!(m3 == r.m3))
                {
                    return m3 < r.m3;
                }
                else
                {
                    return false;
                }
            }
        }

        return false;
    }
};

class History
{
public:
    std::vector<Strategy> list;
    std::vector<Formatted_Strategy> formatted_list;

    void format_list();
    void append_strategy(Strategy s, int result);
};