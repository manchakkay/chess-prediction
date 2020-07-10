#include <iostream>
#include "class/Game.h"

using namespace std;

int main()
{
    int player = 0, history = 0;
    cout << "Select player [0 - white, 1 - black]: ";
    cin >> player;

    if (player >= 0 && player <= 1)
    {

        Game Go("chessdesk.txt");
        Go.start(player);

        cout << "Show all available strategies? [0 - no, 1 - yes]: ";
        cin >> history;

        if (history == 1)
        {
            Go.history();
        }
    }

    return 0;
}