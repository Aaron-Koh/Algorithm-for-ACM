class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res;
        res.push_back(0);
        int n = -1;
        for(int i = 1; i <= num; i++)
        {
            if(i & (1 << (n + 1)))
            {
                n = n + 1;
            }
            res.push_back(res[i - (1 << n)] + 1);
        }
        return res;
    }
};
