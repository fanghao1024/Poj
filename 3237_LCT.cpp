#include <cstdio>
#include <algorithm>
using namespace std;

const int max_n = 20010;
const int inf = 0x3f3f3f3f;
int T, N;
struct Linked_Cut_Tree
{
    int v[max_n], fa[max_n], siz[max_n], son[max_n][2], st[max_n], Max[max_n], Min[max_n], top;
    bool rev[max_n], tag[max_n];
    void init()
    {
        for (int i = 1; i <= N; i++)
        {
            fa[i] = rev[i] = tag[i] = son[i][0] = son[i][1] = v[i] = 0;
            siz[i] = 1;
        }
        siz[0] = 0;
        Max[0] = -inf;
        Min[0] = inf;
    }
    void initial(int x, int val)
    {
        fa[x] = rev[x] = tag[x] = son[x][0] = son[x][1] = 0;
        v[x] = val;
        siz[x] = 1;
    }
    void update(int x)
    {
        int l = son[x][0], r = son[x][1];
        if (!l || !r)
        {
            Max[x] = Max[l + r];
            Min[x] = Min[l + r];
        }
        else
            Max[x] = max(Max[l], Max[r]), Min[x] = min(Min[l], Min[r]);
        if (x > N)
        {
            Max[x] = max(Max[x], v[x]);
            Min[x] = min(Min[x], v[x]);
        }
        siz[x] = siz[l] + siz[r] + 1;
    }
    void phr(int x)
    { // 先修改+打懒标
        tag[x] ^= 1,
            v[x] = -v[x];
        Max[x] = -Max[x];
        Min[x] = -Min[x];
        swap(Max[x], Min[x]);
    }
    void pushdown(int x)
    {
        int l = son[x][0], r = son[x][1];
        if (rev[x])
        {
            rev[x] ^= 1;
            swap(son[x][0], son[x][1]);
            if (l)
                rev[l] ^= 1;
            if (r)
                rev[r] ^= 1;
        }
        if (tag[x])
        {
            tag[x] ^= 1;
            if (l)
                phr(l);
            if (r)
                phr(r);
        }
    }
    void negate(int x)
    {
        tag[x] ^= 1;
    }
    bool isroot(int x)
    {
        return son[fa[x]][0] != x && son[fa[x]][1] != x;
    }
    void rotate(int x)
    {
        int f = fa[x], g = fa[f];
        int c = son[f][0] == x;
        son[f][!c] = son[x][c];
        fa[son[x][c]] = f;
        fa[x] = g;
        if (!isroot(f))
            son[g][son[g][1] == f] = x;
        son[x][c] = f;
        fa[f] = x;
        update(f);
        update(x);
    }
    void splay(int x)
    {
        st[top = 1] = x;
        for (int i = x; !isroot(i); i = fa[i])
            st[++top] = fa[i];
        while (top)
            pushdown(st[top--]);
        while (!isroot(x))
        {
            int f = fa[x], g = fa[f];
            if (!isroot(f))
                (son[f][0] == x) ^ (son[g][0] == f) ? rotate(x) : rotate(f);
            rotate(x);
        }
    }
    void access(int x)
    {
        for (int y = 0; x; x = fa[y = x])
        {
            splay(x);
            son[x][1] = y;
            update(x);
        }
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        rev[x] ^= 1;
    }
    void split(int x, int y)
    {
        makeroot(x);
        access(y);
        splay(y);
    }
    void link(int x, int y)
    {
        makeroot(x);
        fa[x] = y;
    }
} LCT;
int main()
{
    scanf("%d", &T);
    int a, b, c;
    char s[10];
    while (T--)
    {
        scanf("%d", &N);
        LCT.init();
        for (int i = 1; i < N; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            LCT.initial(N + i, c);
            LCT.link(a, N + i);
            LCT.link(N + i, b);
        }
        while (scanf("%s", s))
        {
            if (s[0] == 'D')
                break;
            scanf("%d %d", &a, &b);
            switch (s[0])
            {
            case 'C':
                LCT.splay(N + a);
                LCT.v[N + a] = b;
                break;
            case 'N':
                LCT.split(a, b);
                LCT.phr(b);
                break;
            case 'Q':
                if (a == b)
                {
                    printf("0\n");
                }
                else
                {
                    LCT.split(a, b);
                    printf("%d\n", LCT.Max[b]);
                }
                break;
            }
        }
    }
    return 0;
}