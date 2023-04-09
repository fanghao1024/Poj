#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;
int N,M,block,tot,L,R,res;
struct Node{
    int l,r;
    int id;
}node[max_n];
int num[max_n],belong[max_n],ans[max_n],cnt[max_n];
int read(){
    int num=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){
        num*=10;
        num+=ch-'0';
        ch=getchar();
    }
    return num;
}
bool cmp(const Node& a,const Node& b){
    if(belong[a.l]==belong[b.l]){
        if(belong[a.l]&1) return a.r>b.r;
        else return a.r<b.r; 
    }else{
        return belong[a.l]<belong[b.l];
    }
}
int main(){
    N=read();
    block=sqrt(N);
    for(int i=1;i<=N;i++){
        num[i]=read();
        belong[i]=(i-1)/block+1;
    }
    M=read();
    for(int i=0;i<M;i++){
        node[i].l=read();
        node[i].r=read();
        node[i].id=i;
    }
    sort(node,node+M,cmp);
    L=1,R=0,res=0;
    for(int i=0;i<M;i++){
        while(L<node[i].l) if(--cnt[num[L++]]==0) res--;
        while(R<node[i].r) if(++cnt[num[++R]]==1) res++;
        while(L>node[i].l) if(++cnt[num[--L]]==1) res++;
        while(R>node[i].r) if(--cnt[num[R--]]==0) res--;
        ans[node[i].id]=res;
    }
    for(int i=0;i<M;i++) printf("%d\n",ans[i]);
    return 0;
}
