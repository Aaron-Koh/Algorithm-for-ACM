//单点更新 区间查询
int a[MAXN], ma[MAXN << 2];
void PushUp(int rt)
{
    ma[rt] = max(ma[rt << 1], ma[rt << 1 | 1]);
    return;
}
void Build(int l, int r, int rt)
{
    if(l == r)
    {
        ma[rt] = a[l];
        return;
    }
    int m = (l + r) >> 1;
    Build(l, m, rt << 1);
    Build(m + 1, r, rt << 1 | 1);
    PushUp(rt);
    return;
}
void Update(int L, int c, int l, int r, int rt)
{
    if(l == r)
    {
        ma[rt] = c;
        return;
    }
    int m = (l + r) >> 1;
    if(L <= m) Update(L, c, l, m, rt << 1);
    else Update(L, c, m + 1, r, rt << 1 | 1);
    PushUp(rt);
    return;
}
int Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && r <= R)
    {
        return ma[rt];
    }
    int m = (l + r) >> 1;
    int ans = -1;
    if(L <= m) ans = max(ans, Query(L, R, l, m, rt << 1));
    if(R > m) ans = max(ans, Query(L, R, m + 1, r, rt << 1 | 1));
    return ans;
}

//区间修改
int arr[MAXN], sum[MAXN << 2], add[MAXN << 2];
void PushUp(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    return;
}
void Build(int l, int r, int rt)
{
    add[rt] = 0;
    if(l == r)
    {
        sum[rt] = arr[l];
        return;
    }
    int m = (l + r) >> 1;
    Build(l, m, rt << 1);
    Build(m + 1, r, rt << 1 | 1);
    PushUp(rt);
    return;
}
void PushDown(int ln, int rn, int rt)
{
    if(add[rt])
    {
        add[rt << 1] += add[rt];
        add[rt << 1 | 1] += add[rt];
        sum[rt << 1] += add[rt] * ln;
        sum[rt << 1 | 1] += add[rt] * rn;
        add[rt] = 0;
    }
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if(L <= l && r <= R)
    {
        sum[rt] += c * (r - l + 1);
        add[rt] += c;
        return;
    }
    int m = (l + r) >> 1;
    PushDown(m - l + 1, r - m, rt);
    if(L <= m) Update(L, R, c, l, m, rt << 1);
    if(R > m) Update(L, R, c, m + 1, r, rt << 1 | 1);
    PushUp(rt);
    return;
}
int Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && r <= R)
    {
        return sum[rt];
    }
    int m = (l + r) >> 1;
    PushDown(m - l + 1, r - m, rt);
    int ans = 0;
    if(L <= m) ans += Query(L, R, l, m, rt << 1);
    if(R > m) ans += Query(L, R, m + 1, r, rt << 1 | 1);
    return ans;
}

//染色问题模板
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 8000 + 5;
int color[MAXN << 2], ans[MAXN], vis;
void PushDown(int rt)
{
    if(color[rt] != -1)
    {
        color[rt << 1] = color[rt << 1 | 1] = color[rt];
        color[rt] = -1;
    }
    return;
}
void Update(int L, int R, int c, int l, int r, int rt)
{
    if(L <= l && R >= r)
    {
        color[rt] = c;
        return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if(L <= m) Update(L, R, c, l, m, rt << 1);
    if(R > m) Update(L, R, c, m + 1, r, rt << 1 | 1);
    return;
}
void Query(int l, int r, int rt)
{
    if(l == r)
    {
        if(color[rt] != -1 && color[rt] != vis)
        {
            ans[color[rt]]++;
        }
        vis = color[rt];
        return;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    Query(l, m, rt << 1);
    Query(m + 1, r, rt << 1 | 1);
    return;
}
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        memset(color, -1, sizeof(color));
        memset(ans, 0, sizeof(ans));
        vis = -1;

        int x1, x2, c;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d%d", &x1, &x2, &c);
            if(x1 < x2)Update(x1 + 1, x2, c, 1, 8000, 1);
        }
        Query(1, 8000, 1);
        for(int i = 0; i <= 8000; i++)
        {
            if(ans[i]) printf("%d %d\n", i, ans[i]);
        }
        printf("\n");
    }
    return 0;
}
