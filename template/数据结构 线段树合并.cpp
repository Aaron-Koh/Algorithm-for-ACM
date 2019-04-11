/*
一、用法
线段树合并，就是将已有的两棵线段树合并为一棵，相同位置的信息整合到一起，通常是权值线段树
二、复杂度
1、合并：
取决于两棵线段树重合的部分的大小
每有一个位置权值同样存在，就要O(logn)的复杂度
*/
/*查询某个连通块中点权第K大的点，可连边 BZOJ 2733 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int r[MAXN], fr[MAXN];
int n, m, q;

int p[MAXN];
void init()
{
    for(int i = 1; i <= n; i++)
    {
        p[i] = i;
    }
}
int Find(int x)
{
    if(p[x] == x)
    {
        return x;
    }
    else
    {
        return p[x] = Find(p[x]);
    }
}

int tot, root[MAXN], lson[MAXN << 5], rson[MAXN << 5], sum[MAXN << 5];
void pushUp(int rt)
{
    sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}
void update(int pos, int l, int r, int& rt)
{
    /*注意 ！rt */
    if(!rt) rt = ++tot;
    if(l == r)
    {
        sum[rt] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(pos, l, mid, lson[rt]);
    else update(pos, mid + 1, r, rson[rt]);
    pushUp(rt);
}
int Merge(int rt1, int rt2)
{
    if(!rt1 || !rt2) return rt1 + rt2;
    lson[rt1] = Merge(lson[rt1], lson[rt2]);
    rson[rt1] = Merge(rson[rt1], rson[rt2]);
    sum[rt1] += sum[rt2];
    return rt1;
}
/*值域线段树查询第K小*/
int query(int k, int l, int r, int rt)
{
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int cnt = sum[lson[rt]];
    if(k <= cnt) return query(k, l, mid, lson[rt]);
    else return query(k - cnt, mid + 1, r, rson[rt]);/* k - cnt */
}

int main()
{
    scanf("%d%d", &n, &m);
    init();
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &r[i]);
        fr[r[i]] = i;
    }
    for(int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        u = Find(u), v = Find(v);
        p[u] = v;
    }
    for(int i = 1; i <= n; i++)
    {
        int fa = Find(i);
        update(r[i], 1, n, root[fa]);
    }
    scanf("%d", &q);
    while(q--)
    {
        char op[10];
        scanf("%s", op);
        if(op[0] == 'B')
        {
            int a, b; scanf("%d%d", &a, &b);
            a = Find(a), b = Find(b);
            if(a != b)
            {
                p[a] = b;
                root[b] = Merge(root[a], root[b]);
            }
        }
        else
        {
            int a, b; scanf("%d%d", &a, &b);
            a = Find(a);
            if(sum[root[a]] < b)
            {
                printf("-1\n");
                continue;
            }
            else printf("%d\n", fr[query(b, 1, n, root[a])]);
        }
    }
}
