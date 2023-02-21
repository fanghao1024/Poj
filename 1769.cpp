#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n = 50010;
const int inf=0x3f3f3f3f;
int tree[max_n<<2];
int N,M;
int ls(int x){return x<<1;}
int rs(int x){return (x<<1)|1;}
void build(int p,int pl,int pr){
    if(pl==pr){
        int val=inf;
        if(pl==1) val=0;
        tree[p]=val;
        return ;
    }
    int mid=(pl+pr)>>1;
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    tree[p]=min(tree[ls(p)],tree[rs(p)]);
}
int query(int p,int pl,int pr,int s,int t){
    if(pl==s&&pr==t) return tree[p];
    int mid=(pl+pr)>>1;
    if(t<=mid) return query(ls(p),pl,mid,s,t);
    else if(s>mid) return query(rs(p),mid+1,pr,s,t);
    else return min(query(ls(p),pl,mid,s,mid),query(rs(p),mid+1,pr,mid+1,t));
}
void update(int p,int pl,int pr,int pos,int v){
    if(pl==pr&&pl==pos){
        tree[p]=v;
        return ;
    }
    int mid=(pl+pr)>>1;
    if(pos<=mid) update(ls(p),pl,mid,pos,v);
    else update(rs(p),mid+1,pr,pos,v);
    tree[p]=min(tree[ls(p)],tree[rs(p)]);
}
int main(){
    while(scanf("%d %d",&N,&M)!=EOF){
        build(1,1,N);
        int s,t;
        while(M--){
            scanf("%d %d",&s,&t);
            int v1=query(1,1,N,s,t)+1;
            int v2=query(1,1,N,t,t);
            update(1,1,N,t,min(v1,v2));
        }
        printf("%d\n",query(1,1,N,N,N));
    }
    return 0;
}