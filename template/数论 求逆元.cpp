//法一
//当p是个质数的时候有
//inv(a) = (p - p / a) * inv(p % a) % p
typedef long long ll;
ll inv(ll t, ll p)
{
    //求t关于p的逆元，注意:t要小于p，最好传参前先把t%p一下.
    return t == 1 ? 1 : (p - p / t) * inv(p % t, p) % p;
}
//这个方法不限于求单个逆元，它可以在O(n)的复杂度内算出n个数的逆元
ll inv[N];
void init()
{
    inv[1] = 1;
    for(int i = 2; i < N; i++)
    {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
}
//--------------------------------------------

//法二 扩展欧几里得
//求a关于m的逆元，a、m互质
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    ll d = a;
    if(b != 0LL)
    {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else
    {
        x = 1; y = 0;
    }
    return d;
}
ll mod_inverse(ll a, ll m)
{
    ll x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}
//--------------------------------------------

//法三 欧拉定理、费马小定理
//两个定理的大前提：（a,m) = 1
//当p为素数时，inv(a) = a^(p-2) (mod p)
//当p为整数(不一定是素数时， inv(a) = a^(euler(p) - 1) (mod p)
//所以只要计算快速幂即可

LL pow_mod(ll a, ll b, ll p){//a的b次方求余p
    ll ret = 1;
    a = a % p;
    while(b){
        if(b & 1) ret = (ret * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ret;
}
ll Fermat(ll a, ll p){
    //费马求a关于b的逆元
    return pow_mod(a, p-2, p);
}































