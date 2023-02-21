#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxL=1e6+10;
const int inf=0x3f3f3f3f;
int N,L;
int A,B;
int S,E;
int tree[maxL<<2];
bool flag[maxL];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void build(int p,int pl,int pr){
    if(pl==pr){
        tree[p]=inf;
        return ;
    }
    int mid=(pl+pr)>>1;
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    tree[p]=inf;
}
void update(int p,int pl, int pr,int pos,int v){
    if(pl==pr&&pl==pos){
        tree[p]=min(tree[p],v);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(pos<=mid) update(ls(p),pl,mid,pos,v);
    else update(rs(p),mid+1,pr,pos,v);
    tree[p]=min(tree[ls(p)],tree[rs(p)]);
}
int query(int p,int pl,int pr,int l,int r){
    if(l<=pl&&pr<=r) return tree[p];
    int mid=(pl+pr)>>1;
    if(r<=mid) return query(ls(p),pl,mid,l,r);
    else if(l>mid) return query(rs(p),mid+1,pr,l,r);
    else return min(query(ls(p),pl,mid,l,mid),query(rs(p),mid+1,pr,mid+1,r));
}
int solve(){
    build(1,0,L/2);
    update(1,0,L/2,0,0);
    for(int i=2*A;i<=L;i+=2){
        if(flag[i])
        {
            int l=i/2-B,r=i/2-A;
            l=max(0,l);
            int temp=query(1,0,L/2,l,r);
            if(temp<inf) update(1,0,L/2,i/2,temp+1);
        }
    }
    return query(1,0,L/2,L/2,L/2);
}
int main(){
    while(scanf("%d %d",&N,&L)!=EOF){
        scanf("%d %d",&A,&B);
        memset(flag,1,sizeof(flag));
        while(N--){
            scanf("%d %d",&S,&E);
            for(int i=S+1;i<E;i++) flag[i]=0;
        }
        int ans=solve();
        printf("%d\n",ans<inf?ans:-1);
    }
    return 0;
}