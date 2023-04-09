#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

#define N 233333
#define M 1111111

int sum, cnt[M], a[N], ans[N], cntq = 0, cntr = 0, n, m, sz;

struct ques
{
    int l, r, t, id;
} qq[N], qr[N]; // 两个数组分解记录每一个询问以及修改的状态

inline void add(int x)
{
    sum += !cnt[x]++;
}

inline void del(int x)
{
    sum -= !--cnt[x];
}

// add与del是普通莫队原有操作

inline void upd(int x, int t) // upd是对于时间上的变化所造成变化的维护
{
    if (qq[x].l <= qr[t].l && qr[t].l <= qq[x].r)
    {
        del(a[qr[t].l]);
        add(qr[t].r);
    }                          // 如果这个修改的值在[l,r]区间内，则其变化将对答案造成影响
    swap(a[qr[t].l], qr[t].r); // 因为修改后的下一次操作一定相反(即修改该位置->还原该位置->修改该位置...如此循环)，所以只需交换即可，而不需要写两个函数
}

bool cmp(const ques &a, const ques &b)
{
    return a.l / sz == b.l / sz ? a.r / sz == b.r / sz ? a.t < b.t : a.r < b.r : a.l < b.l;
} // 魔改版cmp，需要判断t的大小

int main()
{
    cin >> n >> m;
    sz = pow(n, 0.666); // 设置块的大小
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= m; i++)
    {
        char op[5];
        int l, r;
        scanf("%s%d%d", op, &l, &r);
        if (op[0] == 'Q')
            ++cntq, qq[cntq].id = cntq, qq[cntq].l = l, qq[cntq].r = r, qq[cntq].t = cntr; // 询问的时间即为该询问以前已经执行了多少次修改操作
        else
            qr[++cntr].l = l, qr[cntr].r = r;
    }
    sort(qq + 1, qq + cntq + 1, cmp);
    int lcur = 1, rcur = 0, tcur = 0;
    for (int i = 1; i <= cntq; i++)
    {
        while (lcur > qq[i].l)
            add(a[--lcur]);
        while (lcur < qq[i].l)
            del(a[lcur++]);
        while (rcur > qq[i].r)
            del(a[rcur--]);
        while (rcur < qq[i].r)
            add(a[++rcur]);
        while (tcur < qq[i].t)
            upd(i, ++tcur);
        while (tcur > qq[i].t)
            upd(i, tcur--);  // 增加t轴上的移动
        ans[qq[i].id] = sum; // 得到最终答案
    }
    for (int i = 1; i <= cntq; i++)
        printf("%d\n", ans[i]);
    return 0; // 结束&AC!
}