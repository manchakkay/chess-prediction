#include "Field.h"
#include <iostream>
#include <algorithm>
#include <iterator>

Field Field::apply_move(Move m, Field &now)
{

    now.data[m.from.i][m.from.j] = '0';
    now.data[m.to.i][m.to.j] = m.figure;

    return now;
}

bool Field::is_alive(int player)
{
    int alive = false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (player == 0)
            {
                if (data[i][j] == 'K')
                {
                    alive = true;
                }
            }
            else
            {
                if (data[i][j] == 'k')
                {
                    alive = true;
                }
            }
        }
    }

    return alive;
}

std::vector<Move> Field::get_moves(int player)
{
    std::vector<Move> list;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            switch (data[i][j])
            {

            case 'P':
            case 'R':
            case 'B':
            case 'N':
            case 'Q':
            case 'K':
                if (player == 0)
                {
                    std::vector<Move> figure_list = figure_moves(i, j, data[i][j], player);
                    list.insert(std::end(list), std::begin(figure_list), std::end(figure_list));
                }
                break;
            case 'p':
            case 'r':
            case 'b':
            case 'n':
            case 'q':
            case 'k':
                if (player == 1)
                {
                    std::vector<Move> figure_list = figure_moves(i, j, data[i][j], player);
                    list.insert(std::end(list), std::begin(figure_list), std::end(figure_list));
                }
                break;
            }
        }
    }

    // std::cout << list.size() << std::endl;
    // for (size_t i = 0; i < list.size(); i++)
    // {
    //     std::cout << list[i].figure << ": " << list[i].from.i << "," << list[i].from.j << " -> " << list[i].to.i << "," << list[i].to.j << std::endl;
    // }
    // std::cout << std::endl;

    return list;
}

int Field::is_busy(int player, int i, int j)
{
    int result = 0;
    switch (player)
    {
    case 0:
        // При встрече с фигурой противника
        if (data[i][j] <= 122 && data[i][j] >= 97)
        {
            result = 2;
        }
        else
        {
            // При встрече с фигурой союзника
            if (data[i][j] <= 90 && data[i][j] >= 65)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
        break;
    case 1:
        // При встрече с фигурой противника
        if (data[i][j] <= 90 && data[i][j] >= 65)
        {
            result = 2;
        }
        else
        {
            // При встрече с фигурой союзника
            if (data[i][j] <= 122 && data[i][j] >= 97)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
        break;
    }

    //Выход за границы поля
    if (i < 0 || i > 7 || j < 0 || j > 7)
    {
        result = 1;
    }

    return result;
}

std::vector<Move> Field::figure_moves(int i, int j, char figure, int player)
{
    std::vector<Move> figure_list;

    // Определение фигура вне зависимости от игрока
    char unifigure;
    if (figure >= 90)
    {
        unifigure = figure - 32;
    }
    else
    {
        unifigure = figure;
    }

    //Координаты хода
    Move Full();
    Step From(i, j);
    Step To(i, j);

    //Блокиратор для столкновений (0 - чисто, 1 - союзник, 2 - противник)
    int breaker = 0;

    //Обработка поведения фигур
    switch (unifigure)
    {
    case 'P':
        //Пешка белого
        if (player == 0 && figure == 'P')
        {
            // Скачок
            if (From.i == 6)
            {
                // Скачок вверх
                breaker = 0, To.i = i, To.j = j;
                breaker = is_busy(player, To.i - 2, To.j);
                if (breaker == 0)
                {
                    breaker = is_busy(player, To.i - 1, To.j);
                    if (breaker == 0)
                    {
                        To.i -= 2;
                        figure_list.push_back(Move(From, To, data[From.i][From.j]));
                    }
                }
            }

            // Движение вверх
            breaker = 0, To.i = i, To.j = j;
            breaker = is_busy(player, To.i - 1, To.j);
            if (breaker != 1)
            {
                To.i--;
                figure_list.push_back(Move(From, To, data[From.i][From.j]));
            }

            // Убийство сверху-справа
            breaker = 0, To.i = i, To.j = j;
            breaker = is_busy(player, To.i - 1, To.j + 1);
            if (breaker == 2)
            {
                To.i--;
                To.j++;
                figure_list.push_back(Move(From, To, data[From.i][From.j]));
            }

            // Убийство сверху-слева
            breaker = 0, To.i = i, To.j = j;
            breaker = is_busy(player, To.i - 1, To.j - 1);
            if (breaker == 2)
            {
                To.i--;
                To.j--;
                figure_list.push_back(Move(From, To, data[From.i][From.j]));
            }
        }
        //Пешка чёрного
        else if (player == 1 && figure == 'p')
        {
            // Скачок
            if (From.i == 1)
            {
                // Скачок вниз
                breaker = 0, To.i = i, To.j = j;
                breaker = is_busy(player, To.i + 2, To.j);
                if (breaker == 0)
                {
                    breaker = is_busy(player, To.i + 1, To.j);
                    if (breaker == 0)
                    {
                        To.i += 2;
                        figure_list.push_back(Move(From, To, data[From.i][From.j]));
                    }
                }
            }

            // Движение вниз
            breaker = 0, To.i = i, To.j = j;
            breaker = is_busy(player, To.i + 1, To.j);
            if (breaker != 1)
            {
                To.i++;
                figure_list.push_back(Move(From, To, data[From.i][From.j]));
            }

            // Убийство снизу-справа
            breaker = 0, To.i = i, To.j = j;
            breaker = is_busy(player, To.i + 1, To.j + 1);
            if (breaker == 2)
            {
                To.i++;
                To.j++;
                figure_list.push_back(Move(From, To, data[From.i][From.j]));
            }

            // Убийство снизу-слева
            breaker = 0, To.i = i, To.j = j;
            breaker = is_busy(player, To.i + 1, To.j - 1);
            if (breaker == 2)
            {
                To.i++;
                To.j--;
                figure_list.push_back(Move(From, To, data[From.i][From.j]));
            }
        }
        break;
    case 'R':
        // Движение вправо
        breaker = 0, To.i = i, To.j = j;

        while (To.j < 7)
        {
            breaker = is_busy(player, To.i, To.j + 1);

            if (breaker == 1)
                break;

            To.j++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение влево
        breaker = 0, To.i = i, To.j = j;

        while (To.j > 0)
        {
            breaker = is_busy(player, To.i, To.j - 1);

            if (breaker == 1)
                break;

            To.j--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вниз
        breaker = 0, To.i = i, To.j = j;

        while (To.i < 7)
        {
            breaker = is_busy(player, To.i + 1, To.j);

            if (breaker == 1)
                break;

            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вниз
        breaker = 0, To.i = i, To.j = j;

        while (To.i > 0)
        {
            breaker = is_busy(player, To.i - 1, To.j);

            if (breaker == 1)
                break;

            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }
        break;
    case 'B':
        // Движение вверх-вправо
        breaker = 0, To.i = i, To.j = j;

        while (To.j < 7 && To.i > 0)
        {
            breaker = is_busy(player, To.i - 1, To.j + 1);

            if (breaker == 1)
                break;

            To.j++;
            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вверх-влево
        breaker = 0, To.i = i, To.j = j;

        while (To.j > 0 && To.i > 0)
        {
            breaker = is_busy(player, To.i - 1, To.j - 1);

            if (breaker == 1)
                break;

            To.j--;
            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вниз-вправо
        breaker = 0, To.i = i, To.j = j;

        while (To.j < 7 && To.i < 7)
        {
            breaker = is_busy(player, To.i + 1, To.j + 1);

            if (breaker == 1)
                break;

            To.j++;
            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вниз-влево
        breaker = 0, To.i = i, To.j = j;

        while (To.j > 0 && To.i < 7)
        {
            breaker = is_busy(player, To.i + 1, To.j - 1);

            if (breaker == 1)
                break;

            To.j--;
            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }
        break;
    case 'N':
        // Движение вверх-вправо
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i - 2, To.j + 1);
        if (breaker != 1)
        {
            To.j += 1;
            To.i -= 2;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вверх-влево
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i - 2, To.j - 1);
        if (breaker != 1)
        {
            To.j -= 1;
            To.i -= 2;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вниз-вправо
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i + 2, To.j + 1);
        if (breaker != 1)
        {
            To.j += 1;
            To.i += 2;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вниз-влево
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i + 2, To.j - 1);
        if (breaker != 1)
        {
            To.j -= 1;
            To.i += 2;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вправо-вверх
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i - 1, To.j + 2);
        if (breaker != 1)
        {
            To.j += 2;
            To.i -= 1;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вправо-вниз
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i + 1, To.j + 2);
        if (breaker != 1)
        {
            To.j += 2;
            To.i += 1;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение влево-вверх
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i - 1, To.j - 2);
        if (breaker != 1)
        {
            To.j -= 2;
            To.i -= 1;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение влево-вниз
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i + 1, To.j - 2);
        if (breaker != 1)
        {
            To.j -= 2;
            To.i += 1;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }
        break;
    case 'Q':
        // Движение вправо
        breaker = 0, To.i = i, To.j = j;

        while (To.j < 7)
        {
            breaker = is_busy(player, To.i, To.j + 1);

            if (breaker == 1)
                break;

            To.j++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение влево
        breaker = 0, To.i = i, To.j = j;

        while (To.j > 0)
        {
            breaker = is_busy(player, To.i, To.j - 1);

            if (breaker == 1)
                break;

            To.j--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вниз
        breaker = 0, To.i = i, To.j = j;

        while (To.i < 7)
        {
            breaker = is_busy(player, To.i + 1, To.j);

            if (breaker == 1)
                break;

            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вниз
        breaker = 0, To.i = i, To.j = j;

        while (To.i > 0)
        {
            breaker = is_busy(player, To.i - 1, To.j);

            if (breaker == 1)
                break;

            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вверх-вправо
        breaker = 0, To.i = i, To.j = j;

        while (To.j < 7 && To.i > 0)
        {
            breaker = is_busy(player, To.i - 1, To.j + 1);

            if (breaker == 1)
                break;

            To.j++;
            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вверх-влево
        breaker = 0, To.i = i, To.j = j;

        while (To.j > 0 && To.i > 0)
        {
            breaker = is_busy(player, To.i - 1, To.j - 1);

            if (breaker == 1)
                break;

            To.j--;
            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вниз-вправо
        breaker = 0, To.i = i, To.j = j;

        while (To.j < 7 && To.i < 7)
        {
            breaker = is_busy(player, To.i + 1, To.j + 1);

            if (breaker == 1)
                break;

            To.j++;
            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }

        // Движение вниз-влево
        breaker = 0, To.i = i, To.j = j;

        while (To.j > 0 && To.i < 7)
        {
            breaker = is_busy(player, To.i + 1, To.j - 1);

            if (breaker == 1)
                break;

            To.j--;
            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));

            if (breaker == 2)
                break;
        }
        break;
    case 'K':
        // Движение вправо
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i, To.j + 1);
        if (breaker != 1)
        {
            To.j++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение влево
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i, To.j - 1);
        if (breaker != 1)
        {
            To.j--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вверх
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i - 1, To.j);
        if (breaker != 1)
        {
            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вниз
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i + 1, To.j);
        if (breaker != 1)
        {
            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вверх-вправо
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i - 1, To.j + 1);
        if (breaker != 1)
        {
            To.j++;
            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вверх-влево
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i - 1, To.j - 1);
        if (breaker != 1)
        {
            To.j--;
            To.i--;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вниз-вправо
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i + 1, To.j + 1);
        if (breaker != 1)
        {
            To.j++;
            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }

        // Движение вниз-влево
        breaker = 0, To.i = i, To.j = j;
        breaker = is_busy(player, To.i + 1, To.j - 1);
        if (breaker != 1)
        {
            To.j--;
            To.i++;
            figure_list.push_back(Move(From, To, data[From.i][From.j]));
        }
        break;
    }

    return figure_list;
}