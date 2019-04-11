int par[MAXN];
int rank[MAXN];

void Init(int n)
{
    for(int i = 0; i < n; i++)
    {
        par[i] = i;
        rank[i] = 0;
    }
}
int Find(int x)
{
    if(par[x] == x)
    {
        return x;
    }
    else
    {
        return par[x] = find[par[x]);
    }
}
void Unite(int x, int y)
{
    x = Find(x);
    y = Find(y);
    if(x == y) return;

    if(rank[x] < rank[y])
    {
        par[x] = y;
    }
    else
    {
        par[y] = x;
        if(rank[x] == rank[y]) rank[x]++;
    }
}
bool Same(int x, int y)
{
    return Find(x) == Find(y);
}
