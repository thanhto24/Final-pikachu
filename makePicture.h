#pragma once
#include "header.h"

bool haveSavefile(savefile player);

void makePic(int hei, int wid, int n, int m, char pic[200][200], int num, savefile player)
{
    ifstream fin;
    for (int i = 0; i <= n * hei - (n - 2); i++)
    {
        for (int j = 0; j <= m * wid - (m - 2); j++)
        {
            pic[i][j] = ' ';
        }
    }
    string picName = "";
    if (!haveSavefile(player))
    {
        picName += "picture\\pic";
        picName += num + '0';
        picName += ".txt";
        fin.open(picName.c_str());
        int dem = 0;
        string S;
        while (!fin.eof())
        {
            getline(fin, S);
            if (fin.eof())
                break;
            for (int i = 0; i < S.size(); i++)
                pic[dem][i] = S[i];
            dem++;
        }
        fin.close();
    }
    else
    {
        for (int i = 0; i < 5; i++)
            if (player.state[i].p_ != 0 && player.state[i].q_ != 0)
            {
                for (int j = 0; j < URLSIZE; j++)
                    picName += player.state[i].file_background[j];
                break;
            }
        fin.open(picName.c_str(), ios::binary);
        int dem = 0;
        string S;
        while (!fin.eof())
        {
            getline(fin, S);
            if (fin.eof())
                break;
            for (int i = 0; i < S.size(); i++)
                pic[dem][i] = S[i] ^ player.mask;
            dem++;
        }
        fin.close();
    }
}
