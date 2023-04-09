#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int max_n=1e6+10;

int tree[max_n<<2],tag[max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
int R[max_n];
int N,M;
void push_up(int p){
    tree[p] = min(tree[ls(p)], tree[rs(p)]);
}
void addtag(int p, int d)
{
    tree[p] -= d;
    tag[p]+= d;
}
void push_down(int p,int pl,int pr){
    if(tag[p]){
        if(pl==pr){tag[p]=0;return;}
        addtag(ls(p),tag[p]);
        addtag(rs(p),tag[p]);
        tag[p]=0;
    }
}

void build(int p,int pl,int pr){
    tag[p] = 0;
    if(pl==pr){
        tree[p]=R[pl];
        return ;
    }
    int mid=(pl+pr)>>1;
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    push_up(p);
}
void update(int p,int pl,int pr,int l,int r,int d){
    if(l<=pl&&pr<=r){
        addtag(p,d);
        return ;
    }
    push_down(p,pl,pr);
    int mid=(pl+pr)>>1;
    if(l<=mid) update(ls(p),pl,mid,l,r,d);
    if(r>mid) update(rs(p),mid+1,pr,l,r,d);
    push_up(p);
}
int query(int p,int pl,int pr,int l,int r){
    if(l<=pl&&pr<=r) return tree[p];
    push_down(p,pl,pr);
    int mid=(pl+pr)>>1;
    if(r<=mid) return query(ls(p),pl,mid,l,r);
    else if(l>mid) return query(rs(p),mid+1,pr,l,r);
    else return min(query(ls(p),pl,mid,l,mid),query(rs(p),mid+1,pr,mid+1,r));
}
int main(){
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++) scanf("%d",&R[i]);
    build(1,1,N);
    bool flag=true;
    int d,s,t;
    int pos=-1;
    for(int i=1;i<=M;i++){
        scanf("%d %d %d",&d,&s,&t);
        if(!flag) continue;
        update(1,1,N,s,t,d);
        if(query(1,1,N,s,t)<0){
            flag=false;
            pos=i;
        }
    }
    if(flag){
        printf("0\n");
    }else{
        printf("-1\n");
        printf("%d\n",pos);
    }
    return 0;
}
