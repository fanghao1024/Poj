#include <cstdio>
#include <algorithm>
const int N = 400010;
int n, i, id[N], root, cmp_d;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
struct node
{
    int d[2], l, r, Max[2], Min[2], val, sum, f, id;
    bool operator<(const node &B) { return d[0] < B.d[0] || (d[0] == B.d[0] && d[1] < B.d[1]); }
} t[N];
inline bool cmp(const node &a, const node &b) { return a.d[cmp_d] < b.d[cmp_d]; }
inline void umax(int &a, int b)
{
    if (a < b)
        a = b;
}
inline void umin(int &a, int b)
{
    if (a > b)
        a = b;
}
inline void up(int x)
{
    if (t[x].l)
    {
        umax(t[x].Max[0], t[t[x].l].Max[0]);
        umin(t[x].Min[0], t[t[x].l].Min[0]);
        umax(t[x].Max[1], t[t[x].l].Max[1]);
        umin(t[x].Min[1], t[t[x].l].Min[1]);
    }
    if (t[x].r)
    {
        umax(t[x].Max[0], t[t[x].r].Max[0]);
        umin(t[x].Min[0], t[t[x].r].Min[0]);
        umax(t[x].Max[1], t[t[x].r].Max[1]);
        umin(t[x].Min[1], t[t[x].r].Min[1]);
    }
}
int build(int l, int r, int D, int f)
{
    int mid = (l + r) >> 1;
    cmp_d = D, std::nth_element(t + l + 1, t + mid + 1, t + r + 1, cmp);
    id[t[mid].f] = mid;
    t[mid].f = f;
    t[mid].Max[0] = t[mid].Min[0] = t[mid].d[0];
    t[mid].Max[1] = t[mid].Min[1] = t[mid].d[1];
    t[mid].val = t[mid].sum = 0;
    if (l != mid)
        t[mid].l = build(l, mid - 1, !D, mid);
    else
        t[mid].l = 0;
    if (r != mid)
        t[mid].r = build(mid + 1, r, !D, mid);
    else
        t[mid].r = 0;
    return up(mid), mid;
}
inline LL sqr(int x) { return (LL)x * x; }
LL ans;
node ansP;
LL ans2;
node ansP2;
int px, py;
inline LL dist(int p1)
{
    LL dis = 0;
    if (px < t[p1].Min[0])
        dis += sqr(t[p1].Min[0] - px);
    if (px > t[p1].Max[0])
        dis += sqr(px - t[p1].Max[0]);
    if (py < t[p1].Min[1])
        dis += sqr(t[p1].Min[1] - py);
    if (py > t[p1].Max[1])
        dis += sqr(py - t[p1].Max[1]);
    return dis;
}
void ask(int x)
{
    LL dl, dr, d0 = sqr(t[x].d[0] - px) + sqr(t[x].d[1] - py);
    if (d0 < ans || (d0 == ans && t[x] < ansP))
        ans2 = ans, ansP2 = ansP, ans = d0, ansP = t[x];
    else if (d0 < ans2 || (d0 == ans2 && t[x] < ansP2))
        ans2 = d0, ansP2 = t[x];
    dl = t[x].l ? dist(t[x].l) : INF;
    dr = t[x].r ? dist(t[x].r) : INF;
    if (dl < dr)
    {
        if (dl <= ans2)
            ask(t[x].l);
        if (dr <= ans2)
            ask(t[x].r);
    }
    else
    {
        if (dr <= ans2)
            ask(t[x].r);
        if (dl <= ans2)
            ask(t[x].l);
    }
}
int getP(int root)
{
    ans = ans2 = INF;
    ask(root);
    return ansP2.id;
}
int T, x, y, Cas = 1, q, f[N];
int sf(int x) { return f[x] == x ? f[x] : f[x] = sf(f[x]); }
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        printf("Case #%d:\n", Cas++);
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &x, &y);
            t[i].d[0] = x, t[i].d[1] = y, t[i].id = i;
        }
        root = build(1, n, 0, 0);
        for (int i = 1; i <= n; i++)
            f[i] = i;
        for (int i = 1; i <= n; i++)
        {
            px = t[i].d[0], py = t[i].d[1];
            x = t[i].id, y = getP(root);
            f[sf(x)] = sf(y);
        }
        while (q--)
        {
            scanf("%d%d", &x, &y);
            puts(sf(x) == sf(y) ? "YES" : "NO");
        }
    }
    return 0;
}