//整型
int ans = -1;
int l = 1, r = maxl + 1;//左闭右开
while(r - l > 1)
{
    //cout << "l: " << l << " r: " << r << endl;
    int mid = (l + r) >> 1;
    if(check(mid))
    {
        l = mid;
        ans = mid;
    }
    else
    {
        r = mid;
    }
}

//浮点数
double l = 0, r = 1;
for(int i = 0; i < 100; i++)
{
    //cout << "l: " << l << " r: " << r << endl;
    double mid = (l + r) / 2;
    if(check(mid))
    {
        l = mid;
    }
    else
    {
        r = mid;
    }
}
