#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int N = 200 + 10;
const int INF = 1 << 29;
int n, m;
int s, t, tot, maxflow;
int head[N];
struct Edge
{
    int to, nxt, c;
}edge[N << 1];
void init()
{
    tot = 1;
    s = 1, t = n;
    maxflow = 0;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int c)
{
    edge[++tot].to = v;
    edge[tot].c = c;
    edge[tot].nxt = head[u];
    head[u] = tot;

    edge[++tot].to = u;
    edge[tot].c = 0;
    edge[tot].nxt = head[v];
    head[v] = tot;
}
int d[N];
bool bfs()
{
    memset(d, 0, sizeof(d));
    queue<int> q;
    while(q.size()) q.pop();
    q.push(s);
    d[s] = 1;
    while(q.size())
    {
        int x = q.front();
        q.pop();
        for(int i = head[x]; ~i; i = edge[i].nxt)
        {
            int y = edge[i].to;
            if(!d[y] && edge[i].c)
            {
                q.push(y);
                d[y] = d[x] + 1;
                if(y == t) return true;
            }
        }
    }
    return false;
}
int dinic(int x, int flow)
{
    if(x == t) return flow;
    int rest = flow, k;
    for(int i = head[x]; ~i && rest; i = edge[i].nxt)
    {
        int y = edge[i].to;
        if(edge[i].c && d[y] == d[x] + 1)
        {
            k = dinic(y, min(rest, edge[i].c));
            if(!k) d[y] = 0;
            edge[i].c -= k;
            edge[i ^ 1].c += k;
            rest -= k;
        }
    }
    return flow - rest;
}
int main()
{
    while(~scanf("%d%d", &m, &n))
    {
        init();
        for(int i = 1, u, v, c; i <= m; i++)
        {
            scanf("%d%d%d", &u, &v, &c);
            addEdge(u, v, c);
        }
        int flow = 0;
        while(bfs())
        {
            while(flow = dinic(s, INF))
            {
                maxflow += flow;
            }
        }
        printf("%d\n", maxflow);
    }
    return 0;
}
