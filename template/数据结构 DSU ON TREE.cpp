/*
CF600E 给定一棵树，每个节点有颜色c[i]，定义子树u中出现次数最多的颜色为u的主要颜色(可以有多个)，求每个节点的主要颜色数值和。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
int c[MAXN], cc[MAXN];//cc记录某种颜色的数量
ll ans[MAXN], sum;
int n, mx;
bool skip[MAXN];

int tot, head[MAXN];
struct Edge{int to, nxt;}edge[MAXN << 1];
void addEdge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].nxt = head[u];
    head[u] = tot++;
}

int sz[MAXN], son[MAXN];

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    memset(son, -1, sizeof(son));
}

void dfs1(int u, int pre)
{
    sz[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v == pre) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(son[u] == -1 || sz[v] > sz[son[u]])
        {
            son[u] = v;
        }
    }
}

void cal(int u, int pre, int val)
{
    cc[c[u]] += val;
    if(val > 0 && cc[c[u]] > mx)
    {
        mx = cc[c[u]];
        sum = c[u];
    }
    else if(val > 0 && cc[c[u]] == mx)
    {
        sum += c[u];
    }
    for(int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v == pre || skip[v]) continue;
        cal(v, u, val);
    }
}

void dfs2(int u, int pre, bool keep)
{
    for(int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v == pre || v == son[u]) continue;
        dfs2(v, u, 0);
    }
    if(son[u] != -1)
    {
        dfs2(son[u], u, 1);
        skip[son[u]] = 1;
    }

    cal(u, pre, 1);
    ans[u] = sum;

    if(son[u] != -1)
    {
        skip[son[u]] = 0;
    }
    if(!keep)
    {
        mx = 0;
        sum = 0;
        cal(u, pre, -1);
    }
}

void solve()
{
    dfs1(1, 0);
    dfs2(1, 0, 0);
    for(int i = 1; i <= n; i++)
    {
        printf("%lld%c", ans[i], " \n"[i == n]);
    }
    return;
}

int main()
{
    init();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
    }
    for(int i = 1; i <= n - 1; i++)
    {
        int u, v; scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    solve();
	return 0;
}
