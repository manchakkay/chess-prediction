#include <fstream>
#include <iostream>

#include "Game.h"

Game::Game(std::string filename)
{
    std::ifstream input_file(filename);
    if (input_file.is_open())
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                input_file >> game_field.data[i][j];
            }
        }
        input_file.close();
    }
    else
    {
        exit(-1000);
    }
}

int Game::resulter_no_moves(int player, int depth)
{
    int counter = 0;

    if (player == main_player)
    {
        counter = 0;
    }
    else
    {
        switch (depth)
        {
        case 6:
            counter = 1;
            break;
        case 4:
            counter = 2;
            break;
        case 2:
            counter = 3;
            break;
        case 0:
            counter = 4;
            break;
        }
    }

    return counter;
}

int Game::resulter(int old_counter, int part, int player)
{
    int counter;

    // Поиск лучшего результата (хотя бы одного) - ход игрока
    if (player == main_player)
    {
        counter = old_counter;
        if (part > 0)
        {
            if (part < counter || counter == 0)
            {
                counter = part;
            }
        }
    }
    // Проверка, что результаты успешны (все) - ход противника
    else
    {
        counter = 3;
        if (part > 0)
        {
            if (part < counter)
            {
                counter = part;
            }
        }
        else
        {
            counter = 0;
        }
    }

    return counter;
}

void Game::start(int player)
{
    strategies = *(new History);
    main_player = player;

    std::vector<Move> available_moves = game_field.get_moves(player);

    int depth = 7;
    int result = 0;
    int counter = 0;

    for (size_t i = 0; i < available_moves.size(); i++)
    {
        Move now_move = available_moves[i];
        Field now_field(game_field);
        Strategy now_strat;

        append_move(depth, now_move, now_strat, (int)available_moves.size());
        now_field = game_field.apply_move(now_move, now_field);

        int now_player = (player == 0) ? 1 : 0;
        int now_result = now_recursion(depth - 1, now_move, now_field, now_strat, now_player);

        counter = resulter(counter, now_result, player);
    }

    if (available_moves.size() == 0)
    {
        counter = resulter_no_moves(player, depth);
    }
    result = counter;

    if (result == 0)
    {
        std::cout << "Chechmate not available" << std::endl;
    }
    else if (result == 1)
    {
        std::cout << "Mate available in 1 turn" << std::endl;
    }
    else if (result == 2)
    {
        std::cout << "Checkmate available in 1 turn" << std::endl;
    }
    else if (result == 3)
    {
        std::cout << "Checkmate available in 2 turns" << std::endl;
    }

    strategies.format_list(result);
}

void Game::history()
{
    for (int i = 0; i < (int)strategies.formatted_list.size(); i++)
    {
        std::cout << strategies.formatted_list[i].type << " turns: " << strategies.formatted_list[i].m1.convert();
        if (strategies.formatted_list[i].m2.figure != '0')
        {
            std::cout << "  " << strategies.formatted_list[i].m2.convert();

            if (strategies.formatted_list[i].m3.figure != '0')
            {
                std::cout << "  " << strategies.formatted_list[i].m3.convert();
            }
        }

        std::cout << std::endl;
    }
}

int Game::now_recursion(int depth, Move m, Field f, Strategy s, int player)
{
    int result = 0;
    int counter = 0;
    bool no_moves = false;
    bool alive = f.is_alive(player);

    History now_strategies;

    // Никто не проиграл - Продолжение рекурсии
    if (alive)
    {
        // Лимит рекурсии - Закрытие рекурсии
        if (depth == 0)
            result = 0;
        // Рекурсия доступна для расширения - Продолжение рекурсии
        else
        {
            int strats_count = 0;

            std::vector<Move> available_moves = f.get_moves(player);
            strats_count = (int)available_moves.size();

            for (int i = 0; i < strats_count; i++)
            {
                Move now_move = available_moves[i];
                Field now_field(f);
                Strategy now_strat(s);

                append_move(depth, now_move, now_strat, strats_count);

                now_field = game_field.apply_move(now_move, now_field);

                int now_player = (player == 0) ? 1 : 0;
                int now_result = now_recursion(depth - 1, now_move, now_field, now_strat, now_player);

                counter = resulter(counter, now_result, player);

                if (player != main_player && counter == 0)
                {
                    result = 0;
                    break;
                }
            }

            if (available_moves.size() == 0)
            {
                no_moves = true;
                counter = resulter_no_moves(player, depth);
            }

            // Получение результата из передач или просчёта ходов
            result = counter;
        }
    }
    // Один из игроков проиграл
    else
    {
        // Ход игрока (он проиграл) — Мат от противника
        if (main_player == player)
            result = 0;
        // Ход противника (он проиграл) — Мат (закрытие рекурсии)
        else
        {
            // Мат за один ход
            if (depth == 6)
                result = 1;
            // Мат за два хода
            else if (depth == 4)
                result = 2;
            // Мат за три хода
            else if (depth == 2)
                result = 3;
            // Мат за четыре хода
            else if (depth == 0)
                result = 4;
        }
    }

    // Если мы закончили рекурсию на этом этапе, тогда сохраняем значение
    if ((result != counter || no_moves) && (result > 0))
    {
        strategies.append_strategy(s, result);
    }

    return result;
}

void Game::append_move(int depth, Move m, Strategy &s, int count)
{
    switch (depth)
    {
    case 7:
        s.m1 = m;
        break;
    case 5:
        s.strats1 = count;
        s.m2 = m;
        break;
    case 3:
        s.strats2 = count;
        s.m3 = m;
        break;
    case 1:
        s.strats3 = count;
        s.m4 = m;
        break;
    }
}
