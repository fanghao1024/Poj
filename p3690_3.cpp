#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;
#define ls tr[u].son[0]
#define rs tr[u].son[1]
struct Tree{
    int val,sum,fa,tag;
    int son[2];
}tr[max_n];

int N,M;
bool isRoot(int u){
    int g=tr[u].fa;
    return tr[g].son[0]!=u&&tr[g].son[1]!=u;
}
void pushup(int u){
    tr[u].sum=tr[ls].sum^tr[rs].sum^tr[u].val;
}
void reverse(int u)
{
    if (!u) return;
    swap(ls, rs);
    tr[u].tag ^= 1;
}
void pushdown(int u){
    if(tr[u].tag){
        reverse(ls);
        reverse(rs);
        tr[u].tag=0;
    }
}
void push(int u){
    if(!isRoot(u)) push(tr[u].fa);
    pushdown(u);
}
void rotate(int u){
    int y=tr[u].fa,z=tr[y].fa;
    int c=tr[y].son[0]==u;
    tr[y].son[!c]=tr[u].son[c];
    if (tr[u].son[c]) tr[tr[u].son[c]].fa = y;
    if(!isRoot(y)) tr[z].son[tr[z].son[1]==y]=u;
    tr[u].fa=z;
    tr[u].son[c]=y;
    tr[y].fa=u;
    pushup(y);
    pushup(u);
}
void rotates(int x)
{
    int y = tr[x].fa;
    int z = tr[y].fa;
    int k = tr[y].son[1] == x;
    if (!isRoot(y))
        tr[z].son[tr[z].son[1] == y] = x;
    tr[x].fa = z;
    tr[y].son[k] = tr[x].son[k ^ 1];
    if (tr[x].son[k ^ 1])
        tr[tr[x].son[k ^ 1]].fa = y;
    tr[y].fa = x;
    tr[x].son[k ^ 1] = y;
    pushup(y);
}

void splay(int u){
    push(u);
    while(!isRoot(u)){
        int f=tr[u].fa,g=tr[f].fa;
        if(!isRoot(f)) (tr[f].son[0]==u)^(tr[g].son[0]==f)?rotate(u):rotate(f);
        rotate(u);
    }
    pushup(u);
}

void access(int u){
    for(int v=0;u;v=u,u=tr[u].fa){
        splay(u);
        tr[u].son[1]=v;
        pushup(u);
    }
}

void makeroot(int u){
    access(u);splay(u);reverse(u);
}
void split(int x,int y){
    makeroot(x);access(y);splay(y);
}
void link(int x,int y){
    makeroot(x);
    tr[x].fa=y;
}
void cut(int x,int y){
    split(x,y);
    if(tr[y].son[0]==x&&!tr[x].son[1]){
        tr[x].fa=tr[y].son[0]=0;
        pushup(y);
    }
}

int findroot(int x){
    access(x);
    splay(x);
    while(tr[x].son[0]){
        pushdown(x);
        x=tr[x].son[0];
    }
    return x;
}


int main(){
    scanf("%d %d",&N,&M);
    for(int i=1;i<=N;i++){
        scanf("%d",&tr[i].val);
        tr[i].sum=tr[i].val;
        tr[i].son[0]=tr[i].son[1]=tr[i].fa=tr[i].tag=0;
    }
    int opt,x,y;
    while(M--){
        scanf("%d %d %d",&opt,&x,&y);
        switch (opt)
        {
            case 0:
                split(x,y);
                printf("%d\n",tr[y].sum);
                break;
            case 1:
                if(findroot(x)!=findroot(y))
                    link(x,y);
                break;
            case 2:
                cut(x,y);
                break;
            case 3:
                splay(x);
                tr[x].val=y;
                break;
        }
    }
    return 0;
}