#include <iostream>
#include <queue>
#include <cstdio>
#include<cstring>
using namespace std;

#define MAX 100
#define Fi "GRAPH.INP"
#define Fo "GRAPH.OUT"

int n, m, u, v, Trace[MAX];
bool A[MAX][MAX];
void docTep()
{
    ios_base::sync_with_stdio(0);
    freopen(Fi, "r", stdin);
    freopen(Fo, "w", stdout);
    cin >> n >> m >> u >> v;
    for (int k = 0; k < m; k++)
    {
        int x, y;
        cin >> x >> y;
        A[x][y] = true;
        A[y][x] = true;
    }
}

void DFS(int x)
{
    for (int y = 1; y <= n; y++)
        if (A[x][y] && Trace[y] == 0)
        {
            Trace[y] =x;
            DFS(y);
        }
}

void xuatKetQua()
{
    for (int y = 1; y <= n; y++)
        if (Trace[y] != 0)
            cout << y << " ";
    cout << endl;
    if (Trace[v] == 0)
        cout << "Not found";
    else
    {
        while (u != v)
        {
            cout << v << " ";
            v = Trace[v];

        }
        cout << u;

    }
}
int main()
{
    memset(A, false, sizeof(A));
    docTep();
    memset(Trace, 0, sizeof(Trace));
    Trace[u] = -1;
    DFS(u);
    xuatKetQua();
    return 0;

}
