#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int max_n = 1e6 + 10;
int N, M, block, tot, L, R, res;
struct Node
{
    int l, r;
    int id;
} node[max_n];
int num[max_n],ans[max_n], cnt[max_n],pre[max_n];
int read()
{
    int num = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        num *= 10;
        num += ch - '0';
        ch = getchar();
    }
    return num;
}
bool cmp(const Node &a, const Node &b)
{
    if(a.r==b.r) return a.l<b.l;
    else return a.r<b.r;
}
int lowbit(int x){return x&-x;}
void add(int x,int v){
    while(x<=N){
        cnt[x]+=v;
        x+=lowbit(x);
    }
}
int getsum(int x){
    int res=0;
    while(x){
        res+=cnt[x];
        x-=lowbit(x);
    }
    return res;
}
int main()
{
    N = read();
    block = sqrt(N);
    for (int i = 1; i <= N; i++)
    {
        num[i] = read();
    }
    M = read();
    for (int i = 0; i < M; i++)
    {
        node[i].l = read();
        node[i].r = read();
        node[i].id = i;
    }
    sort(node, node + M, cmp);
    memset(pre,-1,sizeof(pre));
    int ind=1;
    for(int i=0;i<M;i++){
        while(ind<=node[i].r){
            if(pre[num[ind]]==-1){
                add(ind,1);
            }else{
                add(pre[num[ind]],-1);
                add(ind,1);
            }
            pre[num[ind]]=ind;
            ind++;
        }
        ans[node[i].id]=getsum(node[i].r)-getsum(node[i].l-1);
    }
    
    for (int i = 0; i < M; i++)
        printf("%d\n", ans[i]);
    return 0;
}
