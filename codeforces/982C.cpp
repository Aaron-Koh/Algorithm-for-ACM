# include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n;
vector<int> graph[N];
int num[N];
int ans;
void dfs1(int u, int fa)
{
    num[u] = 1;
    for(int i = 0; i < (int)graph[u].size(); i++)
    {
        int v = graph[u][i];
        if(v == fa) continue;
        dfs1(v, u);
        num[u] += num[v];
    }
}
void dfs(int u, int fa)
{
    for(int i = 0; i < (int)graph[u].size(); i++)
    {
        int v = graph[u][i];
        if(v == fa) continue;
        if(num[v] % 2 == 0)
        {
            ans++;
            dfs(v, u);
        }
        else
        {
            dfs(v, u);
        }
    }
}
void debug()
{
    for(int i = 1; i <= n; i++)
    {
        printf("%d: %d\n", i, num[i]);
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 0, u, v; i < n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        graph[v].emplace_back(u);
        graph[u].emplace_back(v);
    }
    if(n & 1) printf("-1\n");
    else
    {
        dfs1(1, 0);
        dfs(1, 0);
        printf("%d\n", ans);
    }
    // debug();
    return 0;
}
