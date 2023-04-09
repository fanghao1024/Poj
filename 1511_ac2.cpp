#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }
const int N = 20005;
int Tag[N];       // 标志：线段是否有效，能否用于计算宽度
double length[N]; // 存放区间i的总宽度
double xx[N];     // 存放x坐标值，下标用lower_bound查找
struct ScanLine
{                           // 定义扫描线
    double y;               // 边的y坐标
    double right_x, left_x; // 边的x坐标:右、左
    int inout;              // 入边为1，出边为-1
    ScanLine() {}
    ScanLine(double y, double x2, double x1, int io) : y(y), right_x(x2), left_x(x1), inout(io) {}
} line[N];
bool cmp(ScanLine &a, ScanLine &b) { return a.y < b.y; } // y坐标排序
void pushup(int p, int pl, int pr)
{ // 从下往上传递区间值
    if (Tag[p])
        length[p] = xx[pr] - xx[pl];
    // 结点的Tag为正，这个线段对计算宽度有效。计算宽度
    else if (pl + 1 == pr)
        length[p] = 0; // 叶子结点没有宽度
    else
        length[p] = length[ls(p)] + length[rs(p)];
}
void update(int L, int R, int io, int p, int pl, int pr)
{
    if (L <= pl && pr <= R)
    {                 // 完全覆盖
        Tag[p] += io; // 结点的标志，用来判断能否用来计算宽度
        pushup(p, pl, pr);
        return;
    }
    if (pl + 1 == pr)
        return; // 叶子结点
    int mid = (pl + pr) >> 1;
    if (L <= mid)
        update(L, R, io, ls(p), pl, mid);
    if (R > mid)
        update(L, R, io, rs(p), mid, pr); // 注意不是mid+1
    pushup(p, pl, pr);
}
int main()
{
    int n, t = 0;
    while (scanf("%d", &n), n)
    {
        int cnt = 0; // 边的数量，包括入边和出边
        while (n--)
        {
            double x1, x2, y1, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2); // 输入一个矩形
            line[++cnt] = ScanLine(y1, x2, x1, 1);     // 给入边赋值
            xx[cnt] = x1;                              // 记录x坐标
            line[++cnt] = ScanLine(y2, x2, x1, -1);    // 给出边赋值
            xx[cnt] = x2;                              // 记录x坐标
        }
        sort(xx + 1, xx + cnt + 1);                        // 对所有边的x坐标排序
        sort(line + 1, line + cnt + 1, cmp);               // 对扫描线按y轴方向从低到高排序
        int num = unique(xx + 1, xx + cnt + 1) - (xx + 1); // 离散化：用unique去重，返回个数
        memset(Tag, 0, sizeof(Tag));                       // 标志：线段是否有效，能否用于计算宽度
        memset(length, 0, sizeof(length));                 // 存放区间i的总宽度
        double ans = 0;
        for (int i = 1; i <= cnt; ++i)
        { // 扫描所有入边和出边
            int L, R;
            ans += length[1] * (line[i].y - line[i - 1].y); // 累加当前扫描线的面积=宽*高
            L = lower_bound(xx + 1, xx + num + 1, line[i].left_x) - xx;
            // x坐标离散化：用相对位置代替坐标值
            R = lower_bound(xx + 1, xx + num + 1, line[i].right_x) - xx;
            update(L, R, line[i].inout, 1, 1, num);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++t, ans);
    }
    return 0;
}
