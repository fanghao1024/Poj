#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=100010;
int N,M;
struct Node{
    int v,id;
    int l,r,d,fa,del;
}node[max_n];
int find(int x){
    if(x!=node[x].fa) node[x].fa=find(node[x].fa);
    return node[x].fa;
}
int merge(int x,int y){
    if(!x) return y;
    if(!y) return x;
    if(node[x].v>node[y].v||(node[x].v==node[y].v&&node[x].id>node[y].id)) swap(x,y);
    node[x].r=merge(node[x].r,y);
    node[node[x].r].fa=x;
    if(node[node[x].l].d<node[node[x].r].d) swap(node[x].l,node[x].r);
    node[x].d=node[node[x].r].d+1;
    return x;
}
int pop(int x){
    node[node[x].l].fa=node[x].l;
    node[node[x].r].fa=node[x].r;
    node[x].fa=merge(node[x].l, node[x].r);
    node[x].del=1;
    return node[x].v;
}
int main(){
    node[0].d=-1;
    scanf("%d %d",&N,&M);
    for(int i=1;i<=N;i++){
        scanf("%d",&node[i].v);
        node[i].l=node[i].r=node[i].d=node[i].del=0;
        node[i].id=i;
        node[i].fa=i;
    }
    int ops,x,y,fx,fy;
    while(M--){
        scanf("%d",&ops);
        switch(ops){
            case 1:
            scanf("%d %d",&x,&y);
            if(node[x].del||node[y].del) break;
            fx=find(x),fy=find(y);
            if(fx==fy) break;
            merge(fx,fy);
            break;
            case 2:
            scanf("%d",&x);
            if(node[x].del){printf("-1\n");break;}
            fx=find(x);
            printf("%d\n",pop(fx));
            break;
        }
    }
    return 0;
}