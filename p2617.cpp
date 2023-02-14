#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

#define lson node[p].son[0]
#define rson node[p].son[1]

const int max_n = 50010;
const int inf = 2147483647;
int N, M, cnt;
int num[max_n];
struct Node
{
    int son[2];
    int val;
    int pri, size, ct;
} node[max_n * 50];
int newNode(int val)
{
    node[++cnt].val = val;
    node[cnt].son[0] = node[cnt].son[1] = 0;
    node[cnt].size = node[cnt].ct = 1;
    node[cnt].pri = rand();
    return cnt;
}
struct Tr
{
    int root;
    void update(int p)
    {
        node[p].size = node[lson].size + node[rson].size + node[p].ct;
    }
    void rotate(int &p, bool c)
    {
        int son = node[p].son[c];
        node[p].son[c] = node[son].son[!c];
        node[son].son[!c] = p;
        update(p);
        update(p = son);
    }
    void insert(int &p, int val)
    {
        if (!p)
        {
            p = newNode(val);
            return;
        }
        node[p].size++;
        if (node[p].val == val)
        {
            node[p].ct++;
            return;
        }
        bool c = node[p].val < val; //  加入右节点为1
        insert(node[p].son[c], val);
        update(p);
        if (node[node[p].son[c]].pri > node[p].pri)
            rotate(p, c);
    }
    void del(int &p, int val)
    {
        if (!p)
            return;
        if (node[p].val == val)
        {
            if (node[p].ct > 1)
            {
                node[p].ct--;
                node[p].size--;
                return;
            }
            if (!lson || !rson)
                p = lson + rson;
            else
            {
                bool c = node[lson].pri < node[rson].pri;
                rotate(p, c);
                del(p, val);
            }
        }
        else
        {
            node[p].size--;
            del(node[p].son[node[p].val < val], val);
        }
    }
    int rank(int p, int val)
    {
        if (!p)
            return 0;
        if (node[p].val == val)
            return node[lson].size;
        else if (node[p].val > val)
            return rank(lson, val);
        else
            return rank(rson, val) + node[lson].size + node[p].ct;
    }
    int Pre(int p, int val)
    {
        if (!p)
            return -inf;
        if (node[p].val < val)
        {
            return max(node[p].val, Pre(rson, val));
        }
        else
        {
            return Pre(lson, val);
        }
    }
    int Nxt(int p, int val)
    {
        if (!p)
            return inf;
        if (node[p].val > val)
        {
            return min(node[p].val, Nxt(lson, val));
        }
        else
        {
            return Nxt(rson, val);
        }
    }
} tr[max_n << 2];
void init()
{
    cnt = 0;
    node[0].size = node[0].ct = 0;
    node[0].son[0] = node[0].son[1] = 0;
}
int ls(int x) { return x << 1; }
int rs(int x) { return x << 1 | 1; }
void build(int p, int pl, int pr)
{
    tr[p].root = 0;
    for (int i = pl; i <= pr; i++)
    {
        tr[p].insert(tr[p].root, num[i]);
    }
    if (pl == pr)
        return;
    int mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
}
int queryRank(int L, int R, int val, int p, int pl, int pr)
{
    if (L > pr || R < pl)
        return 0;
    if (L <= pl && pr <= R)
        return tr[p].rank(tr[p].root, val);
    int ans = 0, mid = (pl + pr) >> 1;
    ans += queryRank(L, R, val, ls(p), pl, mid);
    ans += queryRank(L, R, val, rs(p), mid + 1, pr);
    return ans;
}
int queryValue(int L, int R, int val, int p, int pl, int pr)
{
    int l = 0, r = 1e8;
    int ans = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (queryRank(L, R, mid, p, pl, pr) + 1 <= val)
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return ans;
}
void modify(int pos, int val, int p, int pl, int pr)
{
    if (pos < pl || pos > pr)
        return;
    tr[p].del(tr[p].root, num[pos]);
    tr[p].insert(tr[p].root, val);
    if (pl == pr)
        return;
    int mid = (pl + pr) >> 1;
    modify(pos, val, ls(p), pl, mid);
    modify(pos, val, rs(p), mid + 1, pr);
}
int getPre(int L, int R, int val, int p, int pl, int pr)
{
    if (L > pr || R < pl)
        return -inf;
    if (L <= pl && pr <= R)
        return tr[p].Pre(tr[p].root, val);
    int mid = (pl + pr) >> 1;
    int ans = getPre(L, R, val, ls(p), pl, mid);
    ans = max(ans, getPre(L, R, val, rs(p), mid + 1, pr));
    return ans;
}
int getNxt(int L, int R, int val, int p, int pl, int pr)
{
    if (L > pr || R < pl)
        return inf;
    if (L <= pl && pr <= R)
        return tr[p].Nxt(tr[p].root, val);
    int mid = (pl + pr) >> 1;
    int ans = getNxt(L, R, val, ls(p), pl, mid);
    ans = min(ans, getNxt(L, R, val, rs(p), mid + 1, pr));
    return ans;
}
int main()
{
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%d", &num[i]);
    init();
    build(1, 1, N);
    char opt[10];
    int l, r, k, pos;
    while (M--)
    {
        scanf("%s", opt);
        switch (opt[0])
        {
        case 'Q':
            scanf("%d %d %d", &l, &r, &k);
            printf("%d\n", queryValue(l, r, k, 1, 1, N));
            break;
        case 'C':
            scanf("%d %d", &pos, &k);
            modify(pos, k, 1, 1, N);
            num[pos] = k;
            break;

        }
    }
    return 0;
}