#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <fstream>
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair
#define hei 5
#define wid 11

using namespace std;

void TextColor(int x) // X là mã màu
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Node
{
    char data;
    int was;
    char view[hei][wid];
    Node *next;
};

typedef struct Node *node;

node makeNode(char x)
{
    node tmp = new Node();
    tmp->data = x;
    if (x != '&')
    {
        tmp->was = 0;
        strcpy(tmp->view[0], " --------- ");
        strcpy(tmp->view[1], "|         |");
        strcpy(tmp->view[2], "|         |");
        strcpy(tmp->view[3], "|         |");
        strcpy(tmp->view[4], " --------- ");
        tmp->view[hei / 2][wid / 2] = x;
    }
    if (x == '&')
        tmp->was = 1;
    tmp->next = NULL;
    return tmp;
}

void printList(node head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
    return;
}

void pushFront(node &head, char x)
{
    node tmp = makeNode(x);
    tmp->next = head;
    head = tmp;
    return;
}

void pushBack(node &head, char x)
{
    node tmp = makeNode(x);
    if (head == NULL)
        return void(pushFront(head, x));
    node p = head;
    while (p->next != NULL)
        p = p->next;
    p->next = tmp;
    return;
}

int size(node head)
{
    int cnt = 0;
    while (head != NULL)
    {
        head = head->next;
        cnt++;
    }
    return cnt;
}

void pushMiddle(node &head, char x, int pos)
{
    int n = size(head);
    if (pos == 1)
        return void(pushFront(head, x));
    if (pos == n + 1)
        return void(pushBack(head, x));
    node p = head, tmp = makeNode(x);
    for (int i = 1; i < pos - 1; i++)
        p = p->next;
    tmp->next = p->next;
    p->next = tmp;
    return;
}

void deleteFirst(node &head)
{
    if (head == NULL)
        return;
    head = head->next;
    return;
}

void deleteLast(node &head)
{
    if (head == NULL)
        return;
    node truoc = NULL, sau = head;
    while (sau->next != NULL)
    {
        truoc = sau;
        sau = sau->next;
    }
    if (truoc == NULL)
        return void(head = NULL);
    truoc->next = NULL;
    return;
}

void deleteMiddle(node &head, int pos)
{
    int n = size(head);
    node truoc = NULL, sau = head;
    for (int i = 1; i < pos; i++)
    {
        truoc = sau;
        sau = sau->next;
    }
    if (truoc == NULL)
        return void(deleteFirst(head));
    truoc->next = sau->next;
    return;
}

node pos(node C, int j)
{

    int dem = 0;
    while (dem != j)
    {
        C = C->next;
        dem++;
    }
    return C;
}

void initC(node *&C, char *c, int n, int m)
{
    int dem = 0;
    C = new node[n + 2];
    for (int i = 0; i <= n + 1; i++)
    {
        C[i] = NULL;
        for (int j = 0; j <= m + 1; j++)
            if (i == 0 || i == n + 1 || j == 0 || j == m + 1)
                pushBack(C[i], '&');
            else
                pushBack(C[i], c[dem++]);
    }
}

void setAte(node &C, int x, int type)
{
    deleteMiddle(C, x + 1);
    if (type & 1)
        pushBack(C, '&');
    else
        pushFront(C, '&');
}

void printBoard(node *C, int n, int m, int type, int y1, int x1, int y2, int x2)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int X = 30, Y = 5;
    gotoxy(X, Y);
    if(type<=2)
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            node curr = pos(C[i], j);
            if (curr->data >= 'A' && curr->data <= 'Z')
            {
                for (int k = 0; k < hei; k++)
                {
                    for (int l = 0; l < wid; l++)
                    {
                        gotoxy((j - 1) * wid + l + X, (i - 1) * hei + k + Y);
                        if (y1 == -2)
                            TextColor(6);
                        else if ((i == y1 && j == x1) || (i == y2 && j == x2))
                        {
                            if (!(k == 0 || k == hei - 1 || l == 0 || l == wid - 1))
                                SetConsoleTextAttribute(hConsole, 240);
                        }
                        cout << curr->view[k][l];
                        if (y1 != -2)
                            SetConsoleTextAttribute(hConsole, 7);
                    }
                }
            }
        }
    }
    else
    for (int j = 0; j <= m + 1; j++)
    {
        for (int i = 0; i <= n + 1; i++)
        {
            node curr = pos(C[i], j);
            if (curr->data >= 'A' && curr->data <= 'Z')
            {
                for (int k = 0; k < hei; k++)
                {
                    for (int l = 0; l < wid; l++)
                    {
                        gotoxy((i - 1) * wid + l + X, (j - 1) * hei + k + Y);
                        if (y1 == -2)
                            TextColor(6);
                        else if ((i == y1 && j == x1) || (i == y2 && j == x2))
                        {
                            if (!(k == 0 || k == hei - 1 || l == 0 || l == wid - 1))
                                SetConsoleTextAttribute(hConsole, 240);
                        }
                        cout << curr->view[k][l];
                        if (y1 != -2)
                            SetConsoleTextAttribute(hConsole, 7);
                    }
                }
            }
        }
    }
}


bool bfs(int y1, int x1, int y2, int x2, int n, int m, node *C)
{
    if (y1 == y2 && x1 == x2)
        return false;

    if (pos(C[y1], x1)->data != pos(C[y2], x2)->data)
        return false;

    if (pos(C[y1], x1)->data == '&')
        return false;

    int graph[200][200];
    ii trace[200][200];
    ii end = mp(y1, x1);
    ii start = mp(y2, x2);
    queue<ii> q;

    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            graph[i][j] = 0;
            trace[i][j] = mp(-1, -1);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            graph[i][j] = !(pos(C[i], j)->was);
        }
    }

    graph[y1][x1] = graph[y2][x2] = 0;
    trace[y1][x1] = mp(-2, -2);
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};

    q.push(end);

    while (!q.empty())
    {
        ii u = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int y = u.f + dy[i];
            int x = u.s + dx[i];
            while (x >= 0 && x <= m + 1 && y >= 0 && y <= n + 1 && graph[y][x] == 0)
            {
                if (trace[y][x] == mp(-1, -1))
                {
                    trace[y][x] = u;
                    q.push(mp(y, x));
                }
                x += dx[i];
                y += dy[i];
            }
        }
    }

    vector<ii> route;

    if (trace[start.f][start.s] == mp(-1, -1))
        return false;

    while (start != end)
    {
        route.push_back(mp(start.f, start.s));
        start = trace[start.f][start.s];
        if (route.size() > 3)
            return false;
    }

    return true;
}

bool canMove(node *C, int n, int m)
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (pos(C[i], j)->data != '&')
                return true;
    return false;
}

void Swap(node &C, int n, int m)
{
    vector<char> adj;
    node curr = C;
    for (int i = 0; i <= m + 1; i++)
    {
        if (curr->data != '&')
            adj.push_back(curr->data);
        curr = curr->next;
    }

    bool was[adj.size()];
    memset(was, false, sizeof(was));
    curr = C;
    for (int i = 0; i < m + 1; i++)
    {
        if (curr->data != '&')
        {
            deleteMiddle(C, i + 1);
            int tmp = rand() % adj.size();
            while (was[tmp])
            {
                tmp = rand() % adj.size();
            }
            was[tmp] = true;
            pushMiddle(C, adj[tmp], i + 1);
        }
        curr = curr->next;
    }
}

void process(node *C, int n, int m, int type)
{
    system("cls");
    while (canMove(C, n, m))
    {
        bool ok = false;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                for (int k = 1; k <= n; k++)
                {
                    for (int l = 1; l <= m; l++)
                    {
                        if (bfs(i, j, k, l, n, m, C))
                        {
                            printBoard(C, n, m, type, -1, -1, -1, -1);

                            ok = true;
                            char ch = getch();
                            {
                                system("cls");
                                printBoard(C, n, m, type, i, j, k, l);
                                Sleep(700);
                                system("cls");
                                if (type&1)
                                {
                                    if (i > k || (i == k && j > l))
                                    {
                                        setAte(C[i], j, type);
                                        setAte(C[k], l, type);
                                    }
                                    else
                                    {
                                        setAte(C[k], l, type);
                                        setAte(C[i], j, type);
                                    }
                                }
                                else
                                {
                                    if (i > k || (i == k && j > l))
                                    {
                                        setAte(C[k], l, type);
                                        setAte(C[i], j, type);
                                    }
                                    else
                                    {
                                        setAte(C[i], j, type);
                                        setAte(C[k], l, type);
                                    }
                                }
                                printBoard(C, n, m, type, -1, -1, -1, -1);
                            }
                        }
                    }
                }
            }
        }
        if (!ok)
        {
            for (int i = 1; i <= n; i++)
                Swap(C[i], n, m);
            system("cls");
            printBoard(C, n, m, type, -2, -1, -1, -1);
        }
    }
    gotoxy(0, 0);
    cout << "Game over!";
    return;
}

int main()
{
    srand(time(0));
    int n = 4, m = 6, x, type;
    cout << "Choose sliding type: \n";
    cout << "1. Left to right.\n";
    cout << "2. Right to left.\n";
    cout << "3. Down to up.\n";
    cout << "4. Up to down.\n";
    cout << "My choice: ";
    cin >> type;
    if(type>2)
        swap(n,m);
    bool was[n * m];
    memset(was, false, sizeof(was));
    char c[n * m];
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
    node *C;
    initC(C, c, n, m);
    // for (int i = 0; i <= n + 1; i++)
    // {
    //     printList(C[i]);
    //     cout << endl;
    // }
    // cout << endl;
    // for(int i = 1; i <= n; i++)
    //     Swap(C[i], n, m);
    // for (int i = 0; i <= n + 1; i++)
    // {
    //     printList(C[i]);
    //     cout << endl;
    // }
    // cout << pos(C[1],1)->data << endl;
    // cout << pos(C[1],2)->data << endl;
    printBoard(C, n, m, type, -1, -1, -1, -1);
    process(C, n, m, type);
}