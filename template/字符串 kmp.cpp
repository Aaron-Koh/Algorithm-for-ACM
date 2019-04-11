void getnext()
{
    next[0] = -1;//长度为0时没有意义
    int i = 0,j = -1;//i为即将比较的后缀下标， j为即将比较的前缀下标
    while(i < m)//保证模式串下标不超长度
    {
        while(j >= 0 && p[i] != p[j])//若因为j = -1, 则无串可配，若因为失配， 则前缀下标前移
        {
            j = next[j];
        }
        //直到匹配到了， 两个下标就同时前移
        i++; j++;
        next[i] = j;
    }
}
void kmp()
{
    int i = 0, j = 0;//前者大串的下标， 后者模式串下标
    while(i < n)
    {
        while(j >= 0 && t[i] != p[j])
        {
            j = next[j];
        }
        i++; j++;
        if(j == m)
        {
            printf("%d\n",i-m);
            j = next[m];
        }
    }
}

