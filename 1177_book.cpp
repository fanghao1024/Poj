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
    int l, r, h, inout; // inout=1 �±�, inout=-1 �ϱ�
    ScanLine() {}
    ScanLine(int a, int b, int c, int d) : l(a), r(b), h(c), inout(d) {}
} line[N];
bool cmp(ScanLine &a, ScanLine &b) { return a.h < b.h; } // y��������
bool lbd[N << 2], rbd[N << 2];                           // �������������������˵��Ƿ񱻸��ǣ�0��ʾû�У�1��ʾ�У�
int num[N << 2];                                         // ��������ж����������ı�
int Tag[N << 2];                                         // ����������Ƿ���Ч
int length[N << 2];                                      // ����������Ч���
void pushup(int p, int pl, int pr)
{
    if (Tag[p])
    { // ����TagΪ��������߶ζԼ�������Ч
        lbd[p] = rbd[p] = 1;
        length[p] = pr - pl + 1;
        num[p] = 1; // ÿ�����������˵�
    }
    else if (pl == pr)
        length[p] = num[p] = lbd[p] = rbd[p] = 0; // Ҷ�ӽ��
    else
    {
        lbd[p] = lbd[ls(p)]; // ������ӹ���˵�
        rbd[p] = rbd[rs(p)]; // ���Ҷ��ӹ��Ҷ˵�
        length[p] = length[ls(p)] + length[rs(p)];
        num[p] = num[ls(p)] + num[rs(p)];
        if (lbd[rs(p)] && rbd[ls(p)])
            num[p] -= 1; // �ϲ���
    }
}
void update(int L, int R, int io, int p, int pl, int pr)
{
    if (L <= pl && pr <= R)
    { // ��ȫ����
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
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);  // �������
            lbd = min(lbd, x1);                     // ������Сx����
            rbd = max(rbd, x2);                     // �������x����
            line[++cnt] = ScanLine(x1, x2, y1, 1);  // ����߸�ֵ
            line[++cnt] = ScanLine(x1, x2, y2, -1); // �����߸�ֵ
        }
        sort(line + 1, line + cnt + 1, cmp); // ��������С��������ɢ��
        int ans = 0, last = 0;               // last����һ�������䱻���ǳ���
        for (int i = 1; i <= cnt; i++)
        { // ɨ��������ߺͳ���
            if (line[i].l < line[i].r)
                update(line[i].l, line[i].r - 1, line[i].inout, 1, lbd, rbd - 1);
            ans += num[1] * 2 * (line[i + 1].h - line[i].h); // ����
            ans += abs(length[1] - last);                    // ����
            last = length[1];
        }
        printf("%d\n", ans);
    }
    return 0;
}
