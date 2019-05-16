# include <bits/stdc++.h>
using namespace std;

int n;
vector<int> piles;

bool stoneGame(vector<int>& piles)
{
    int dp[510][510];
    int L = piles.size();

    for(int i = 0; i < L; i++)
    {
        dp[i][i] = piles[i];
    }

    for(int len = 2; len <= L; len++)
    {
        for(int i = 0; i + len - 1 < L; i++)
        {
            int j = i + len - 1;
            dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
        }
    }
    // cout << dp[0][L - 1] << endl;
    return dp[0][L - 1] > 0;
}

int main()
{
    cin >> n;
    for(int i = 0, x; i < n; i++)
    {
        cin >> x;
        piles.push_back(x);
    }
    cout << stoneGame(piles) << endl;
}
