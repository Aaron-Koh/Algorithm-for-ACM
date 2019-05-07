# include <bits/stdc++.h>
using namespace std;

// method 1
/*
const int N = 2e5 + 10;
char s[N];
int dp[N];
int f[3];
int r;

void init()
{
    dp[0] = 0;
    memset(f, -1, sizeof(f));
    r = 0;
    f[0] = 0;
}

int main()
{
    scanf("%s", s);
    init();
    int len = strlen(s);
    for(int i = 1; i <= len; i++)
    {
        r = (r + s[i - 1] - '0') % 3;
        dp[i] = dp[i - 1];
        if(f[r] != -1)
        {
            dp[i] = max(dp[i], dp[f[r]] + 1);
        }
        f[r] = i;
    }
    printf("%d\n", dp[len]);
    return 0;
}
*/

// method 2
const int N = 2e5 + 10;
int dp[N][3][2];
char s[N];

void init()
{
    memset(dp, -1, sizeof(dp));
    dp[0][(s[0] - '0') % 3][0] = 0;
    dp[0][(s[0] - '0') % 3][1] = (s[0] - '0') % 3 == 0 ? 1 : 0;
}

int main()
{
    scanf("%s", s);
    int len = strlen(s);
    init();
    for(int i = 0; i < len - 1; i++)
    {
        int x = s[i + 1] - '0';
        for(int j = 0; j <= 2; j++)
        {
            if(dp[i][j][0] != -1)
            {
                dp[i + 1][(j + x) % 3][0] = max(dp[i + 1][(j + x) % 3][0], dp[i][j][0]);
                dp[i + 1][(j + x) % 3][1] = max(dp[i + 1][(j + x) % 3][1], dp[i][j][0] + ((j + x) % 3 == 0? 1 : 0));
            }
            if(dp[i][j][1] != -1)
            {
                dp[i + 1][x % 3][0] = max(dp[i + 1][x % 3][0], dp[i][j][1]);
                dp[i + 1][x % 3][1] = max(dp[i + 1][x % 3][1], dp[i][j][1] + (x % 3 == 0? 1 : 0));
            }
        }
    }
    int res = -1;
    for(int j = 0; j <= 2; j++)
    {
        for(int k = 0; k <= 1; k++)
        {
            res = max(res, dp[len - 1][j][k]);
        }
    }
    printf("%d\n", res);
    return 0;
}

