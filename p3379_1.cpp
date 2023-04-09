#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e5+10;

int N,M,S;
struct Tree{
    int fa,son[2],tag;
}tr[max_n];
bool isroot(int x){
    int f=tr[x].fa;
    return tr[f].son[0]!=x&&tr[f].son[1]!=x;
}
void reverse(int x)
{
    swap(tr[x].son[0], tr[x].son[1]);
    tr[x].tag ^= 1;
}
void pushdown(int x){
    if(tr[x].tag){
        reverse(tr[x].son[0]);
        reverse(tr[x].son[1]);
        tr[x].tag=0;
    }
}
void push(int x){
    if(!isroot(x)) push(tr[x].fa);
    pushdown(x);
}
void rotate(int x){
    int f=tr[x].fa,g=tr[f].fa;
    int c=tr[f].son[0]==x;
    tr[f].son[!c]=tr[x].son[c];
    if(tr[x].son[c]) tr[tr[x].son[c]].fa=f;
    if(!isroot(f)) tr[g].son[tr[g].son[1]==f]=x;
    tr[x].fa=g;
    tr[x].son[c]=f;
    tr[f].fa=x;
}
void splay(int x){
    push(x);
    while(!isroot(x)){
        int f=tr[x].fa,g=tr[f].fa;
        if(!isroot(f)) (tr[f].son[0]==x)^(tr[g].son[0]==f)?rotate(x):rotate(f);
        rotate(x);
    }
}
void access(int x){
    for(int y=0;x;y=x,x=tr[x].fa){
        splay(x);
        tr[x].son[1]=y;
    }
}
void makeroot(int x){
    access(x);
    splay(x);
    reverse(x);
}
void link(int x,int y){
    makeroot(x);
    tr[x].fa=y;
}
int query_LCA(int x,int y){
    access(x);
    int ans;
    for(int child=0;y;child=y,y=tr[y].fa){
        splay(y);
        tr[y].son[1]=child;
        ans=y;
    }
    return ans;
}
int main(){
    scanf("%d %d %d",&N,&M,&S);
    int x,y;
    for(int i=1;i<N;i++){
        scanf("%d %d",&x,&y);
        link(x,y);
    }
    makeroot(S);
    while(M--){
        scanf("%d%d",&x,&y);
        printf("%d\n",query_LCA(x,y));
    }
    return 0;
}