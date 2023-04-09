#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }
const int N = 20005;
int Tag[N];       // ��־���߶��Ƿ���Ч���ܷ����ڼ�����
double length[N]; // �������i���ܿ��
double xx[N];     // ���x����ֵ���±���lower_bound����
struct ScanLine
{                           // ����ɨ����
    double y;               // �ߵ�y����
    double right_x, left_x; // �ߵ�x����:�ҡ���
    int inout;              // ���Ϊ1������Ϊ-1
    ScanLine() {}
    ScanLine(double y, double x2, double x1, int io) : y(y), right_x(x2), left_x(x1), inout(io) {}
} line[N];
bool cmp(ScanLine &a, ScanLine &b) { return a.y < b.y; } // y��������
void pushup(int p, int pl, int pr)
{ // �������ϴ�������ֵ
    if (Tag[p])
        length[p] = xx[pr] - xx[pl];
    // ����TagΪ��������߶ζԼ�������Ч��������
    else if (pl + 1 == pr)
        length[p] = 0; // Ҷ�ӽ��û�п��
    else
        length[p] = length[ls(p)] + length[rs(p)];
}
void update(int L, int R, int io, int p, int pl, int pr)
{
    if (L <= pl && pr <= R)
    {                 // ��ȫ����
        Tag[p] += io; // ���ı�־�������ж��ܷ�����������
        pushup(p, pl, pr);
        return;
    }
    if (pl + 1 == pr)
        return; // Ҷ�ӽ��
    int mid = (pl + pr) >> 1;
    if (L <= mid)
        update(L, R, io, ls(p), pl, mid);
    if (R > mid)
        update(L, R, io, rs(p), mid, pr); // ע�ⲻ��mid+1
    pushup(p, pl, pr);
}
int main()
{
    int n, t = 0;
    while (scanf("%d", &n), n)
    {
        int cnt = 0; // �ߵ�������������ߺͳ���
        while (n--)
        {
            double x1, x2, y1, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2); // ����һ������
            line[++cnt] = ScanLine(y1, x2, x1, 1);     // ����߸�ֵ
            xx[cnt] = x1;                              // ��¼x����
            line[++cnt] = ScanLine(y2, x2, x1, -1);    // �����߸�ֵ
            xx[cnt] = x2;                              // ��¼x����
        }
        sort(xx + 1, xx + cnt + 1);                        // �����бߵ�x��������
        sort(line + 1, line + cnt + 1, cmp);               // ��ɨ���߰�y�᷽��ӵ͵�������
        int num = unique(xx + 1, xx + cnt + 1) - (xx + 1); // ��ɢ������uniqueȥ�أ����ظ���
        memset(Tag, 0, sizeof(Tag));                       // ��־���߶��Ƿ���Ч���ܷ����ڼ�����
        memset(length, 0, sizeof(length));                 // �������i���ܿ��
        double ans = 0;
        for (int i = 1; i <= cnt; ++i)
        { // ɨ��������ߺͳ���
            int L, R;
            ans += length[1] * (line[i].y - line[i - 1].y); // �ۼӵ�ǰɨ���ߵ����=��*��
            L = lower_bound(xx + 1, xx + num + 1, line[i].left_x) - xx;
            // x������ɢ���������λ�ô�������ֵ
            R = lower_bound(xx + 1, xx + num + 1, line[i].right_x) - xx;
            update(L, R, line[i].inout, 1, 1, num);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++t, ans);
    }
    return 0;
}
