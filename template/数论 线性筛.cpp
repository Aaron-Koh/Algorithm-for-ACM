/*
1、用处：筛素数
2、复杂度：O（n）
3、注释：
（1）基本思想：1、a 为任何数， b 为质数， 那么 a * b 不是质数 2、对于每一个合数，我们只用其最小质因数筛掉一次
（2）prime数组中的数是递增的，倘若 i % prime[j] == 0 时不 break 掉，
    那么 i * prime[j + 1] 也会被筛掉， 然而 i * prime[j + 1] 能被 prime[j] 筛掉。
*/
/*普通（欧拉）线性筛*/
const int MAXN = 1000;
bool notPrime[MAXN];
int prime[MAXN];
int cnt;
void primeSieve()
{
    notPrime[1] = 1;
    for(int i = 2; i < MAXN; i++)
    {
        if(notPrime[i] == 0)
        {
            prime[cnt++] = i;
        }
        for(int j = 0; j < cnt && prime[j] * i < MAXN; j++)
        {
            notPrime[ prime[j] * i ] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
