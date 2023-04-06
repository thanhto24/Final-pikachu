#include "header.h"
#include "player.h"
#include "boardSetting.h"

void setAte(int hei, int wid, int y, int x, char C[200][200], char view[200][200], bool ate[200][200]);

void init(int hei, int wid, int n, int m, char C[200][200], char view[200][200], bool ate[200][200], int choosenLevel, savefile player, bool is_cont)
{
    // cin >> n;
    bool was[n * m];
    int x;
    memset(was, false, sizeof(was));
    char c[n * m];
    if (!is_cont)
        for (int i = 1; i <= n * m / 2; i++)
        {
            x = 65 + rand() % (90 - 65 + 1);
            for (int i = 1; i <= 2; i++)
            {
                int pos = rand() % (n * m);
                while (was[pos])
                    pos = rand() % (n * m);
                was[pos] = true;
                c[pos] = (char)(x);
            }
        }
    else
    {
        savefile tmp;
        ifstream fin;
        fin.open("account\\account.dat", ios::binary);
        while (!fin.eof())
        {
            fin.read((char *)&(tmp), sizeof(savefile));
            if (fin.eof())
                break;
            for (int i = 0; i < strlen(tmp.name); i++)
                tmp.name[i] ^= tmp.mask;
            for (int i = 0; i < strlen(tmp.password); i++)
                tmp.password[i] ^= tmp.mask;
            if (strcmp(tmp.name, player.name) == 0 && strcmp(tmp.password, player.password) == 0)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (tmp.state[i].p_ != 0)
                    {
                        for (int j = 0; j < n * m; j++)
                        {
                            c[j] = tmp.state[i].board[j];
                        }
                        i = 5;
                    }
                }
                break;
            }
        }
        fin.close();
    }

    int dem = 0;
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            if (i == 0 || i == n + 1 || j == 0 || j == m + 1)
                C[i][j] = '&';
            else
                C[i][j] = c[dem++];
            // cin >> C[i][j];
        }
    }

    for (int i = 0; i <= n * hei - (n - 2); i++)
    {
        for (int j = 0; j <= m * wid - (m - 2); j++)
        {
            if (i == 0 || i == n * hei - (n - 2) || j == 0 || j == m * wid - (m - 2))
                view[i][j] = '&';
            else
            {
                if ((i - 1) % (hei - 1) == 0 && (j - 1) % (wid - 1) == 0)
                    view[i][j] = '+';
                else if ((i - 1) % (hei - 1) == 0)
                    view[i][j] = '-';
                else if ((j - 1) % (wid - 1) == 0)
                    view[i][j] = '|';
                else if ((i - 1 - hei / 2) % (hei - 1) == 0 && (j - 1 - wid / 2) % (wid - 1) == 0)
                    view[i][j] = C[(i - 1 - hei / 2) / (hei - 1) + 1][(j - 1 - wid / 2) / (wid - 1) + 1];
                else
                    view[i][j] = '@';
            }
        }
    }

    if(is_cont)
    for (int i = 1; i <= n ; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if(C[i][j] < 'A' || C[i][j] > 'Z')
                setAte(hei, wid, i, j, C, view, ate);
        }
    }
}
