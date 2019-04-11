/*求单个数的欧拉函数*/
int Euler(int n)
{
    int ret = n;
    for(int i = 2; i * i <= n; i++)
        if(n % i == 0)
        {
            ret = ret / i * (i - 1);//先进行除法防止溢出(ret = ret * (1 - 1 / p(i)))
            while(n % i == 0) n /= i;
        }
    if(n > 1) ret = ret / n * (n - 1);
    return ret;
}

/*打表法*/
const int MAXN = 1e5 + 10;
int euler[MAXN];
void getEuler()
{
    memset(euler, 0, sizeof(euler));
    euler[1] = 1;
    for(int i = 2; i < MAXN; i++)
        if(!euler[i])
            for(int j = i; j < MAXN; j += i)
            {
                if(!euler[j]) euler[j] = j;
                euler[j] = euler[j] / i * (i - 1);//先进行除法是为了防止中间数据的溢出
            }
}

/*线性筛（同时得到欧拉函数和素数表）*/
const int MAXN = 1e5 + 10;
bool check[MAXN];
int phi[MAXN];
int prime[MAXN];
int cnt;
void phi_and_prime_table()
{
    memset(check, false, sizeof(check));
    phi[1] = 1;
    cnt = 0;
    for(int i = 2; i < MAXN; i++)
    {
        if(!check[i])
        {
            prime[cnt++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0; j < cnt && prime[j] * i < MAXN; j++)
        {
            check[prime[j] * i] = true;
            if(i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else
            {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}
