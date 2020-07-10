#include "History.h"
#include <vector>
#include <algorithm>

void History::format_list(int result)
{
    for (int l_i = 0; l_i < (int)list.size(); l_i++)
    {
        if (list[l_i].type == result)
        {
            Formatted_Strategy a;

            a.type = list[l_i].type;

            a.m1 = list[l_i].m1;
            a.m2 = list[l_i].m2;
            a.m3 = list[l_i].m3;
            a.m4 = list[l_i].m4;

            if (a.type >= 2)
            {
                a.m2_found = 1;
                a.m2_all = list[l_i].strats1;
            }
            if (a.type >= 3)
            {
                a.m3_found = 1;
                a.m3_all = list[l_i].strats2;
            }
            if (a.type >= 4)
            {
                a.m4_found = 1;
                a.m4_all = list[l_i].strats2;
            }

            formatted_list.push_back(a);
        }
    }

    for (int l_i = 0; l_i < (int)formatted_list.size(); l_i++)
    {
        for (int f_i = 0; f_i < (int)formatted_list.size(); f_i++)
        {
            if (l_i != f_i)
            {
                if ((formatted_list[l_i].m1 == formatted_list[f_i].m1) && (formatted_list[l_i].m2 == formatted_list[f_i].m2) && (formatted_list[l_i].m3 == formatted_list[f_i].m3)&& (formatted_list[l_i].m4 == formatted_list[f_i].m4))
                {
                    if ((formatted_list[l_i].m1.figure != '0') && (formatted_list[l_i].m2.figure != '0') && (formatted_list[l_i].m3.figure != '0') && (formatted_list[l_i].m4.figure != '0'))
                    {
                        formatted_list[l_i].m4_found++;
                    }

                    formatted_list.erase(formatted_list.begin() + f_i);
                }
            }
        }
    }

    std::sort(formatted_list.begin(), formatted_list.end());
}

void History::append_strategy(Strategy s, int result)
{
    s.type = result;
    list.push_back(s);
}