#include <stdio.h>
const int N = 1e5;
int num[N];                 // num[v]：点v后加的数字，num[v]=0~9
int st_edge[10 * N], top_s; // 栈，用于存边。top_s指示栈顶
char st_ans[10 * N];
int top_a; // 栈，存序列结果。top_a指示栈顶
int m;
void no_dfs(int v)
{             // 模拟递归，递归搜点v的10条边，放进st_edge中
    int edge; // 边的值
    while (num[v] < 10)
    {                            // 在点v(是一个n-1位序列)后加0~9构成10条边
        edge = 10 * v + num[v];  // 数字edge代表一个边
        num[v]++;                // 点v添的下一个数字。按字典序递增
        st_edge[top_s++] = edge; // 把边存入到栈st_edge中,它是字典序的
                                  printf("%02d -> ",v);  //打印边的起点
        v = edge % m; // 更新起点为原来的终点，往下走。点值等于edge的后几位
                       printf("%02d: edge=%03d\n",v,edge); //打印边的终点、边的权值
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
            m *= 10; // m是点的数量，共10^(n-1)个点
        for (int i = 0; i < m; i++)
            num[i] = 0;
        no_dfs(0); // 从起点0开始，递归点0的10条边
        while (top_s)
        { // 继续走
            printf("-----while start------\n");
            edge = st_edge[--top_s];
            st_ans[top_a++] = edge % 10 + '0'; // 只需要存边值的最后一位
            no_dfs(edge / 10);                 // 边值的前n-1位，即上一个点，作用类似DFS的回溯
        }
        for (int i = 1; i < n; ++i)
            printf("0"); // 打印第一组数，就是n-1个0
        while (top_a)
            printf("%c", st_ans[--top_a]); // 打印其他组数，每组打印1位
        printf("\n");
    }
    return 0;
}
