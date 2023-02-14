#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n = 270000;
const int inf=0x3fffffff;
int T,N,K,cnt,root;
struct Tr{
    int val;
    int size,fa;
    int son[2];
}tr[max_n];
int rec[max_n];
int newNode(int father,int val){
    cnt++;
    tr[cnt].fa=father;
    tr[cnt].son[0]=tr[cnt].son[1]=0;
    tr[cnt].size=1;
    tr[cnt].val=val;
    return cnt;
}
void update(int p){
    tr[p].size=tr[tr[p].son[0]].size+tr[tr[p].son[1]].size+1;
}
void build(int l,int r,int& p,int father){
    if(l>r) return ;
    int mid=(l+r)>>1;
    p=newNode(father,mid);
    build(l,mid-1,tr[p].son[0],p);
    build(mid+1,r,tr[p].son[1],p);
    update(p);
}
void init(){
    cnt=0;
    tr[0].son[0]=tr[0].son[1]=0;
    tr[0].size=0;
    root=newNode(0,-inf);
    tr[root].son[1]=newNode(root,inf);
    build(1,N,tr[tr[root].son[1]].son[0],tr[root].son[1]);
    update(tr[root].son[1]);
    update(root);
}
int Find(int u,int k){
    if(tr[tr[u].son[0]].size+1==k) return u;
    if(tr[tr[u].son[0]].size>=k) return Find(tr[u].son[0],k);
    return Find(tr[u].son[1],k-tr[tr[u].son[0]].size-1);
}
void rotate(int x){
    int f=tr[x].fa,g=tr[f].fa;
    int c=tr[f].son[0]==x;
    tr[f].son[!c]=tr[x].son[c];
    tr[tr[x].son[c]].fa=f;
    tr[x].fa=g;
    if(g) tr[g].son[tr[g].son[1]==f]=x;
    tr[f].fa=x;
    tr[x].son[c]=f;
    update(f);
    update(x);
}
void splay(int x,int goal){
    while(tr[x].fa!=goal){
        int f=tr[x].fa,g=tr[f].fa;
        if(g!=goal) (tr[f].son[0]==x)^(tr[g].son[0]==f)?rotate(x):rotate(f);
        rotate(x);
    }
    if(!goal) root=x;
}
int Delete(int x){
    int a=Find(root,x-1),b=Find(root,x+1);
    splay(a,0);splay(b,a);
    int temp=tr[tr[b].son[0]].val;
    tr[b].son[0]=0;
    update(b);update(a);
    return temp;
}
void Print(int u){
    if(tr[u].son[0]) Print(tr[u].son[0]);
    printf("%d ",tr[u].val);
    if(tr[u].son[1]) Print(tr[u].son[1]);
}
int main(){
    scanf("%d",&T);
    for(int case_no=1;case_no<=T;case_no++){
        scanf("%d %d",&N,&K);
        init();
        int x;
        long long ans=0;
        for(int i=1;i<=K;i++){
            scanf("%d",&x);
            ans+=Delete(x+1);
        }
        printf("Case %d: %lld\n", case_no,ans);
    }
    return 0;
}