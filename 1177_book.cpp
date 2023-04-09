#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }
const int N = 200005;
struct ScanLine
{
    int l, r, h, inout; // inout=1 下边, inout=-1 上边
    ScanLine() {}
    ScanLine(int a, int b, int c, int d) : l(a), r(b), h(c), inout(d) {}
} line[N];
bool cmp(ScanLine &a, ScanLine &b) { return a.h < b.h; } // y坐标排序
bool lbd[N << 2], rbd[N << 2];                           // 标记这个结点的左右两个端点是否被覆盖（0表示没有，1表示有）
int num[N << 2];                                         // 这个区间有多少条独立的边
int Tag[N << 2];                                         // 标记这个结点是否有效
int length[N << 2];                                      // 这个区间的有效宽度
void pushup(int p, int pl, int pr)
{
    if (Tag[p])
    { // 结点的Tag为正，这个线段对计算宽度有效
        lbd[p] = rbd[p] = 1;
        length[p] = pr - pl + 1;
        num[p] = 1; // 每条边有两个端点
    }
    else if (pl == pr)
        length[p] = num[p] = lbd[p] = rbd[p] = 0; // 叶子结点
    else
    {
        lbd[p] = lbd[ls(p)]; // 和左儿子共左端点
        rbd[p] = rbd[rs(p)]; // 和右儿子共右端点
        length[p] = length[ls(p)] + length[rs(p)];
        num[p] = num[ls(p)] + num[rs(p)];
        if (lbd[rs(p)] && rbd[ls(p)])
            num[p] -= 1; // 合并边
    }
}
void update(int L, int R, int io, int p, int pl, int pr)
{
    if (L <= pl && pr <= R)
    { // 完全覆盖
        Tag[p] += io;
        pushup(p, pl, pr);
        return;
    }
    int mid = (pl + pr) >> 1;
    if (L <= mid)
        update(L, R, io, ls(p), pl, mid);
    if (mid < R)
        update(L, R, io, rs(p), mid + 1, pr);
    pushup(p, pl, pr);
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int cnt = 0;
        int lbd = 10000, rbd = -10000;
        for (int i = 0; i < n; i++)
        {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);  // 输入矩形
            lbd = min(lbd, x1);                     // 横线最小x坐标
            rbd = max(rbd, x2);                     // 横线最大x坐标
            line[++cnt] = ScanLine(x1, x2, y1, 1);  // 给入边赋值
            line[++cnt] = ScanLine(x1, x2, y2, -1); // 给出边赋值
        }
        sort(line + 1, line + cnt + 1, cmp); // 排序。数据小，不用离散化
        int ans = 0, last = 0;               // last：上一次总区间被覆盖长度
        for (int i = 1; i <= cnt; i++)
        { // 扫描所有入边和出边
            if (line[i].l < line[i].r)
                update(line[i].l, line[i].r - 1, line[i].inout, 1, lbd, rbd - 1);
            ans += num[1] * 2 * (line[i + 1].h - line[i].h); // 竖线
            ans += abs(length[1] - last);                    // 横线
            last = length[1];
        }
        printf("%d\n", ans);
    }
    return 0;
}
