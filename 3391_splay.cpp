#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=100010;
const int inf=0x3f3f3f3f;
struct Tr{
    int son[2];
    int fa,size;
    int val,tag;
}tr[max_n];

int N,M,cnt,root;
bool flag;
void Update(int p){
    tr[p].size=tr[tr[p].son[0]].size+tr[tr[p].son[1]].size+1;
}
int newNode(int father,int val){
    cnt++;
    tr[cnt].son[0]=tr[cnt].son[1]=0;
    tr[cnt].val=val;
    tr[cnt].size=1;
    tr[cnt].fa=father;
    tr[cnt].tag=0;
    return cnt;
}
void Pushdown(int u){
    if(tr[u].tag){
        tr[u].tag^=1;
        swap(tr[u].son[0],tr[u].son[1]);
        if(tr[u].son[0]) tr[tr[u].son[0]].tag^=1;
        if(tr[u].son[1]) tr[tr[u].son[1]].tag^=1;
    }
}
void Build(int l,int r,int& p,int fa){
    if(l>r) return ;
    int mid=(l+r)>>1;
    p=newNode(fa,mid);
    Build(l,mid-1,tr[p].son[0],p);
    Build(mid+1,r,tr[p].son[1],p);
    Update(p);
}
void Init(){
    cnt=root=0;
    tr[0].son[0]=tr[0].son[1]=0;
    root=newNode(0,-inf);
    tr[root].son[1]=newNode(root,inf);
    Build(1,N,tr[tr[root].son[1]].son[0],tr[root].son[1]);
    Update(tr[root].son[1]);
    Update(root);
}
int Find(int u,int k){
    Pushdown(u);
    if(tr[tr[u].son[0]].size+1==k) return u;
    if(tr[tr[u].son[0]].size>=k) return Find(tr[u].son[0],k);
    return Find(tr[u].son[1],k-tr[tr[u].son[0]].size-1);
}
void Rotate(int x){
    Pushdown(x);
    int f = tr[x].fa, g = tr[f].fa;
    int c=tr[f].son[0]==x;
    tr[f].son[!c]=tr[x].son[c];
    tr[tr[x].son[c]].fa=f;
    tr[x].fa=g;
    if(g) tr[g].son[tr[g].son[1]==f]=x;
    tr[x].son[c]=f;
    tr[f].fa=x;
    Update(f);
    Update(x);
}
void Splay(int x,int goal){
    while(tr[x].fa!=goal){
        int f=tr[x].fa,g=tr[f].fa;
        if(g!=goal) (tr[f].son[0]==x)^(tr[g].son[0]==f)?Rotate(x):Rotate(f);
        Rotate(x);
    }
    if(!goal) root=x;
}
void Flip(int x,int y){
    int a=Find(root,x-1),b=Find(root,y+1);
    Splay(a,0);Splay(b,a);
    tr[tr[b].son[0]].tag^=1;
}
void Print(int u){
    Pushdown(u);
    if(tr[u].son[0]) Print(tr[u].son[0]);
    if(tr[u].val!=inf&&tr[u].val!=-inf){
        if (flag)
        {
            printf("%d", tr[u].val);
            flag = 0;
        }
        else
        {
            printf(" %d", tr[u].val);
        }
    }
    
    if(tr[u].son[1]) Print(tr[u].son[1]);
}
int main(){
    scanf("%d %d",&N,&M);
    Init();
    int x,y;
    while(M--){
        scanf("%d %d",&x,&y);
        Flip(++x,++y);
    }
    flag=1;
    Print(root);
    printf("\n");
    return 0;
}