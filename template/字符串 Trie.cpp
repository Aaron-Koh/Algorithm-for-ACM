const int MAXN = 26;
struct Trie
{
    int v;//根据需要变化
    Trie* next[MAXN];
}* root;
void InsertTrie(char* str)
{
    int len = strlen(str);
    Trie* p = root, *q;
    for(int i = 0; i < len; i++)
    {
        int id = str[i] - 'a';
        if(p -> next[id] == NULL)
        {
            q = new Trie;
            q -> v = 1;
            for(int j = 0; j < MAXN; j++)
            {
                q->next[j] = NULL;
            }
            p->next[id] = q;
            p = p->next[id];
        }
        else
        {
            p -> next[id] -> v++;
            p = p -> next[id];
        }
    }
    p->v = -1;//若为结尾，则将v改成-1表示 这地方不是所有模板都适用，小心
}
int SearchTrie(char* str)
{
    int len = strlen(str);
    Trie* p = root;
    for(int i = 0; i < len; i++)
    {
        int id = str[i] - 'a';
        p = p->next[id];
        if(p == NULL)
            return 0; //若为空集，表示不存在以此为前缀的串
        if(p->v == -1)
            return -1;//字符集中已有串是此串的前缀
    }
    return -1;//此串是字符集中某串的前缀
}
int DelTrie(Trie* T)
{
    if(T == NULL)
        return 0;
    for(int i = 0; i < MAXN; i++)
    {
        if(T->next[i] != NULL)
            DelTrie(T->next[i]);
    }
    delete T;
    return 0;
}


























