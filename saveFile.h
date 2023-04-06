#pragma once
#pragma pack(1)
#include "player.h"
#include "play.h"

void updateFile(savefile player);

bool haveSavefile(savefile player)
{
    savefile tmp;
    ifstream fin;
    fin.open("account\\template.bin", ios::in | ios::binary);

    if (!fin.is_open())
        return false;

    while (!fin.eof())
    {
        fin.read((char *)&tmp, sizeof(tmp));
        if (fin.eof())
            break;
        for (int i = 0; i < strlen(tmp.name); i++)
            tmp.name[i] = tmp.name[i] ^ tmp.mask;

        for (int i = 0; i < strlen(tmp.password); i++)
            tmp.password[i] = tmp.password[i] ^ tmp.mask;

        if (strcmp(tmp.name, player.name) == 0 && strcmp(tmp.password, player.password) == 0)
        {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

bool getSaveFile(savefile &player)
{
    savefile tmp;
    ifstream fin;
    fin.open("account\\template.bin", ios::in | ios::binary);

    if (!fin.is_open())
        return false;

    while (!fin.eof())
    {
        fin.read((char *)&tmp, sizeof(savefile));
        if (fin.eof())
            break;
        for (int i = 0; i < strlen(tmp.name); i++)
            tmp.name[i] = tmp.name[i] ^ tmp.mask;

        for (int i = 0; i < strlen(tmp.password); i++)
            tmp.password[i] = tmp.password[i] ^ tmp.mask;

        if (strcmp(tmp.name, player.name) == 0 && strcmp(tmp.password, player.password) == 0)
        {
            for (int i = 0; i < 5; i++)
            {
                player.record[i].points = tmp.record[i].points;
                player.record[i].date.dd = tmp.record[i].date.dd;
                player.record[i].date.mm = tmp.record[i].date.mm;
                player.record[i].date.yy = tmp.record[i].date.yy;
                player.state[i].q = tmp.state[i].q;
                player.state[i].q_ = tmp.state[i].q_;
                player.state[i].p = tmp.state[i].p;
                player.state[i].p_ = tmp.state[i].p_;

                for (int j = 0; j < BOARDSIZE; j++)
                    if (tmp.state[i].board[j] != '\0')
                        player.state[i].board[j] = tmp.state[i].board[j] ^ tmp.mask;
                    else
                        player.state[i].board[j] = '\0';

                for (int j = 0; j < URLSIZE; j++)
                    if (tmp.state[i].file_background[j] != '\0')
                        player.state[i].file_background[j] = tmp.state[i].file_background[j] ^ tmp.mask;
                    else
                        player.state[i].file_background[j] = '\0';

                for (int j = 0; j < PADDING; j++)
                    player.state[i].padding[j] = player.record[i].padding[j] = '\0';
            }
            fin.close();
            updateFile(player);
            return true;
        }
    }
    fin.close();
    return false;
}
