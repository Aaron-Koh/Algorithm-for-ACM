#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;
const int INF = 1 << 29;
const int N = 2010;
const int M = 20010;
int head[N], ver[M], edge[M], nxt[M], v[N], incf[N], pre[N];
int n, m, s, t, tot, maxflow;
void addEdge(int x, int y, int z)
{
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
    ver[++tot] = x, edge[tot] = 0, nxt[tot] = head[y], head[y] = tot;
}
bool bfs()
{
    memset(v, 0, sizeof(v));
    queue<int> q;
    q.push(s); v[s] = 1;
    incf[s] = INF; // 增广路上各边的最小剩余容量
    while(q.size())
    {
        int x = q.front(); q.pop();
        for(int i = head[x]; i; i = nxt[i])
        {
            if(edge[i])
            {
                int y = ver[i];
                if(v[y]) continue;
                incf[y] = min(incf[x], edge[i]);
                pre[y] = i; // 记录前驱， 便于找到最长路的实际方案
                q.push(y), v[y] = 1;
                if(y == t) return 1;
            }
        }
    }
    return 0;
}
void update()
{
    int x = t;
    while(x != s)
    {
        int i = pre[x];
        edge[i] -= incf[t];
        edge[i ^ 1] += incf[t];
        x = ver[i ^ 1];
    }
    maxflow += incf[t];
}
int main()
{
    while(cin >> m >> n)
    {
        memset(head, 0, sizeof(head));
        s = 1, t = n; tot = 1; maxflow = 0;
        for(int i = 1, x, y, c; i <= m; i++)
        {
            scanf("%d%d%d", &x, &y, &c);
            addEdge(x, y, c);
        }
        while(bfs())
        {
            update();
        }
        cout << maxflow << endl;
    }
}
