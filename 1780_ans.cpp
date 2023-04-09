#include <stdio.h>
const int N = 1e5;
int num[N];                 // num[v]����v��ӵ����֣�num[v]=0~9
int st_edge[10 * N], top_s; // ջ�����ڴ�ߡ�top_sָʾջ��
char st_ans[10 * N];
int top_a; // ջ�������н����top_aָʾջ��
int m;
void no_dfs(int v)
{             // ģ��ݹ飬�ݹ��ѵ�v��10���ߣ��Ž�st_edge��
    int edge; // �ߵ�ֵ
    while (num[v] < 10)
    {                            // �ڵ�v(��һ��n-1λ����)���0~9����10����
        edge = 10 * v + num[v];  // ����edge����һ����
        num[v]++;                // ��v�����һ�����֡����ֵ������
        st_edge[top_s++] = edge; // �ѱߴ��뵽ջst_edge��,�����ֵ����
                                  printf("%02d -> ",v);  //��ӡ�ߵ����
        v = edge % m; // �������Ϊԭ�����յ㣬�����ߡ���ֵ����edge�ĺ�λ
                       printf("%02d: edge=%03d\n",v,edge); //��ӡ�ߵ��յ㡢�ߵ�Ȩֵ
    }
}
int main()
{
    int n, edge;
    while (scanf("%d", &n) && n != 0)
    {
        top_s = top_a = edge = 0;
        m = 1;
        for (int i = 0; i < n - 1; ++i)
            m *= 10; // m�ǵ����������10^(n-1)����
        for (int i = 0; i < m; i++)
            num[i] = 0;
        no_dfs(0); // �����0��ʼ���ݹ��0��10����
        while (top_s)
        { // ������
            printf("-----while start------\n");
            edge = st_edge[--top_s];
            st_ans[top_a++] = edge % 10 + '0'; // ֻ��Ҫ���ֵ�����һλ
            no_dfs(edge / 10);                 // ��ֵ��ǰn-1λ������һ���㣬��������DFS�Ļ���
        }
        for (int i = 1; i < n; ++i)
            printf("0"); // ��ӡ��һ����������n-1��0
        while (top_a)
            printf("%c", st_ans[--top_a]); // ��ӡ����������ÿ���ӡ1λ
        printf("\n");
    }
    return 0;
}
