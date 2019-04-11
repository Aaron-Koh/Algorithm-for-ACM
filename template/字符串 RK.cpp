/*
1、用法：字符串匹配
2、复杂度：O(|S|) S 为总串
3、注释：
（1）原理：H(C) = (c[1] * b^(m-1) + c[2] * b^(m-2) + ... + c[m] * b^0) % h;
            H(S[k + 1 ... k + m]) = H(S[k ... k + m - 1] * b - S[k] * b^m + s[k + m]) % h;
            b 和 h为两个合适的互素常数，取 h 为 2^64 ，通过自然溢出省去求模运算。
*/
typedef unsigned long long ull;
const ull B = 1e8 + 7; //哈希的基数

//a是否在b中出现
bool contain(string& a, string& b)
{
    int al = a.length(), bl = b.length();
    if(al > bl) return false;

    //计算B的al次方
    ull t = 1;
    for(int i = 0; i < al; i++) t *= B;

    //计算a和b长度为al的前缀对应的哈希值
    ull ah = 0, bh = 0;
    for(int i = 0; i < al; i++) ah = ah * B + a[i];
    for(int i = 0; i < al; i++) bh = bh * B + b[i];

    //对b不断右移一位，更新哈希值并判断
    for(int i = 0 ; i + al <= bl; i++)
    {
        if(ah == bh) return true; //b从位置i开始长度为al的字符串子串等于a
        if(i + al < bl) bh = bh * B + b[i + al] - b[i] * t;
    }
    return false;
}

//a的后缀和b的前缀相等的最大长度
int overlap(string& a, string& b)
{
    int al = a.length(), bl = b.length();
    int ans = 0;
    ull ah = 0, bh = 0, t = 1;
    for(int i = 1; i <= min(al, bl); i++)
    {
        ah = ah + a[al - i] * t;
        bh = bh * B + b[i - 1];
        if(ah == bh) ans = i;
        t *= B;
    }
    return ans;
}

//BKDR hash
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int Hash = 0;

    while (*str)
    {
        Hash = Hash * seed + (*str++);
    }

    return (Hash & 0x7FFFFFFF);
}
