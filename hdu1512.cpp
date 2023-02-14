#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=100100;

int N,M;
int v[max_n],d[max_n],l[max_n],r[max_n],fa[max_n];
int find(int x){
    if(x!=fa[x]) fa[x]=find(fa[x]);
    return fa[x];
}
int merge(int x,int y){
    if(!x) return y;
    if(!y) return x;
    if(v[x]<v[y]) swap(x,y);
    r[x]=merge(r[x],y);
    fa[r[x]]=x;
    if(d[l[x]]<d[r[x]]) swap(l[x],r[x]);
    d[x]=d[r[x]]+1;
    return x;
}
int pop(int x){
    fa[l[x]]=l[x];
    fa[r[x]]=r[x];
    return merge(l[x],r[x]);
}
int main(){
    d[0]=-1; //空节点的深度为-1
    int x,y;
    while(scanf("%d",&N)!=EOF){
        for(int i=1;i<=N;i++){
            scanf("%d",&v[i]);
            l[i]=r[i]=d[i]=0;
            fa[i]=i;
        }
        scanf("%d",&M);
        while(M--){
            scanf("%d %d",&x,&y);
            int fx=find(x),fy=find(y);
            if(fx==fy){printf("-1\n");continue;}
            int rt=pop(fx);
            v[fx]/=2;l[fx]=r[fx]=d[fx]=0;
            fx=merge(rt,fx);
            rt=pop(fy);
            v[fy]/=2;l[fy]=r[fy]=d[fy]=0;
            fy=merge(rt,fy);
            rt=merge(fx,fy);
            printf("%d\n",v[rt]);
        }
    }
    return 0;
}