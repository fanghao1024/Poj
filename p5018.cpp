#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;

struct Tree{
    bool flag;
    int sonsum;
    int l,r;
    int val;
}tree[max_n];

int N;
bool compare(int i,int j){
    if(!i&&!j) return true;
    if(i&&!j||j&&!i) return false;
    if(tree[i].val!=tree[j].val) return false;
    return compare(tree[i].l,tree[j].r)&&compare(tree[i].r,tree[j].l);
}
void build(int p){
    int l = tree[p].l, r = tree[p].r;
    if(tree[p].l) build(tree[p].l);
    if(tree[p].r) build(tree[p].r);
    tree[p].sonsum = tree[l].sonsum + tree[r].sonsum + 1;
    if(!tree[p].l&&!tree[p].r){
        tree[p].flag=1;
        return ;
    }
    if(compare(l,r)){
        tree[p].flag=1;
    }else{
        tree[p].flag=0;
    }
}
int main(){
    int x,l,r;
    scanf("%d",&N);
    tree[0].flag=1;
    tree[0].sonsum=0;
    tree[0].l=tree[0].r=0;

    for(int i=1;i<=N;i++){
        scanf("%d",&x);
        tree[i].val=x;
    }
    for(int i=1;i<=N;i++){
        scanf("%d %d",&l,&r);
        tree[i].l=(l==-1)?0:l;
        tree[i].r=(r==-1)?0:r;
    }
    build(1);
    int ans=0;
    for(int i=1;i<=N;i++){
        //printf("%d %d %d\n",i,tree[i].flag,tree[i].sonsum);
        if(tree[i].flag) ans=max(ans,tree[i].sonsum);
    }
    printf("%d\n",ans);
    return 0;
}
