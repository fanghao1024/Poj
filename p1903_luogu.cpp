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
} qq[N], qr[N]; // ��������ֽ��¼ÿһ��ѯ���Լ��޸ĵ�״̬

inline void add(int x)
{
    sum += !cnt[x]++;
}

inline void del(int x)
{
    sum -= !--cnt[x];
}

// add��del����ͨĪ��ԭ�в���

inline void upd(int x, int t) // upd�Ƕ���ʱ���ϵı仯����ɱ仯��ά��
{
    if (qq[x].l <= qr[t].l && qr[t].l <= qq[x].r)
    {
        del(a[qr[t].l]);
        add(qr[t].r);
    }                          // �������޸ĵ�ֵ��[l,r]�����ڣ�����仯���Դ����Ӱ��
    swap(a[qr[t].l], qr[t].r); // ��Ϊ�޸ĺ����һ�β���һ���෴(���޸ĸ�λ��->��ԭ��λ��->�޸ĸ�λ��...���ѭ��)������ֻ�轻�����ɣ�������Ҫд��������
}

bool cmp(const ques &a, const ques &b)
{
    return a.l / sz == b.l / sz ? a.r / sz == b.r / sz ? a.t < b.t : a.r < b.r : a.l < b.l;
} // ħ�İ�cmp����Ҫ�ж�t�Ĵ�С

int main()
{
    cin >> n >> m;
    sz = pow(n, 0.666); // ���ÿ�Ĵ�С
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= m; i++)
    {
        char op[5];
        int l, r;
        scanf("%s%d%d", op, &l, &r);
        if (op[0] == 'Q')
            ++cntq, qq[cntq].id = cntq, qq[cntq].l = l, qq[cntq].r = r, qq[cntq].t = cntr; // ѯ�ʵ�ʱ�伴Ϊ��ѯ����ǰ�Ѿ�ִ���˶��ٴ��޸Ĳ���
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
            upd(i, tcur--);  // ����t���ϵ��ƶ�
        ans[qq[i].id] = sum; // �õ����մ�
    }
    for (int i = 1; i <= cntq; i++)
        printf("%d\n", ans[i]);
    return 0; // ����&AC!
}