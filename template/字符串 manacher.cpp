/*
1、用法：求最长回文子串
2、复杂度：O（n）
3、注释：
（1）原理：看注释
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
char a[MAXN * 2];//aba -> $#a#b#a# 如此就可不管回文串的奇偶
char s[MAXN];
int p[MAXN * 2];//p[i] 代表以i为中心的回文串的最大半径（包括i）
int len;
void manacher()
{
    int l = 0;
    a[l++] = '$';
    a[l++] = '#';
    len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        a[l++] = s[i];
        a[l++] = '#';
    }
    a[l] = 0;
    int maxRight = 0, id = 0;//至今回文串能拓展到的最右端+1 和 其对应的下标
    for(int i = 0; i < l; i++)
    {
        p[i] = maxRight > i ? min(p[2 * id - i], maxRight - i) : 1; //如果 i < maxRight, 那么我们就能借助p[0-i-1]得到p[i], 否则定为1， 然后继续拓展
        while(a[i + p[i]] == a[i - p[i]]) p[i]++;
        if(i + p[i] > maxRight)
        {
            maxRight = i + p[i];
            id = i;
        }
    }
}
int main()
{
    while(~scanf("%s", s))
    {
        manacher();
        int ans = 0;
        for(int i = 0; i < 2 * len + 2; i++)
        {
            ans = max(ans, p[i] - 1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
