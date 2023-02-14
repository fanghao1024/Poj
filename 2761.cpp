#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=100100;
const int max_m=50010;
const int inf=0x3fffffff;

int N,M,cnt,root;
int num[max_n];
struct Query{
    int l,r,k,id;
    bool operator <(const Query& a) const{
        return l<a.l;
    }
}query[max_m];

struct Tr{
    int fa;
    int son[2];
    int size,val;
}tr[max_n];
int ans[max_n];
int newNode(int father,int val){
    cnt++;
    tr[cnt].son[0]=tr[cnt].son[1]=0;
    tr[cnt].size=1;
    tr[cnt].val=val;
    tr[cnt].fa=father;
    return cnt;
}
void update(int p){
    tr[p].size=tr[tr[p].son[0]].size+tr[tr[p].son[1]].size+1;
}
void Init(){
    cnt=0;
    tr[0].size=0;
    tr[0].son[0]=tr[0].son[1]=0;
    root=newNode(0,-inf);
    tr[root].son[1]=newNode(root,inf);
    update(tr[root].son[1]);
    update(root);
}
void rotate(int x){
    int f=tr[x].fa,g=tr[f].fa;
    int c=tr[f].son[0]==x;
    tr[f].son[!c]=tr[x].son[c];
    tr[tr[x].son[c]].fa=f;
    tr[x].fa=g;
    if(g) tr[g].son[tr[g].son[1]==f]=x;
    tr[x].son[c]=f;
    tr[f].fa=x;
    update(f);update(x);
}
void splay(int x,int goal){
    while(tr[x].fa!=goal){
        int f=tr[x].fa,g=tr[f].fa;
        if(g!=goal) (tr[g].son[0]==f)^(tr[f].son[0]==x)?rotate(x):rotate(f);
        rotate(x);
    }
    if(!goal) root=x;
}
int Findk(int u,int k){
    if(tr[tr[u].son[0]].size+1==k){splay(u,0);return u;}
    if(tr[tr[u].son[0]].size>=k) return Findk(tr[u].son[0],k);
    return Findk(tr[u].son[1],k-tr[tr[u].son[0]].size-1);
}
int getRankByValue(int u,int val){
    if(tr[u].val==val) {splay(u,0);return u;}
    if(tr[u].val>val) return getRankByValue(tr[u].son[0],val);
    return getRankByValue(tr[u].son[1],val);
}
void Insert(int val){
    int x;
    for(x=root;tr[x].son[tr[x].val<val];x=tr[x].son[tr[x].val<val]);
    tr[x].son[tr[x].val<val]=newNode(x,val);
    splay(tr[x].son[tr[x].val<val],0);
}
void Print(int u)
{
    if (tr[u].son[0])
        Print(tr[u].son[0]);
    printf("%d ", tr[u].val);
    if (tr[u].son[1])
        Print(tr[u].son[1]);
}
void Delete(int val){
    int id=getRankByValue(root,val);
    //int pos=tr[tr[id].son[0]].size+1;
    //int a=Findk(root,pos-1),b=Findk(root,pos+1);
    int a=tr[id].son[0];
    while(tr[a].son[1]) a=tr[a].son[1];
    int b=tr[id].son[1];
    while(tr[b].son[0]) b=tr[b].son[0];
    if(!a){
        splay(b,0);
        tr[b].son[0]=0;
        update(b);
        return ;
    }
    if(!b){
        splay(a,0);
        tr[a].son[1]=0;
        update(a);
        return ;
    }
    splay(a,0);
    splay(b,a);
    tr[b].son[0]=0;
    update(b);
    update(a);
}

int main(){
    scanf("%d %d",&N,&M);
    for(int i=1;i<=N;i++) scanf("%d",&num[i]);
    for(int i=0;i<M;i++) {scanf("%d %d %d",&query[i].l,&query[i].r,&query[i].k);query[i].id=i;}
    sort(query,query+M);
    Init();
    for(int i=query[0].l;i<=query[0].r;i++){
        Insert(num[i]);
    }
    ans[query[0].id]=tr[Findk(root,query[0].k+1)].val;
    for(int i=1;i<M;i++){
        for(int j=query[i-1].l;j<query[i].l&&j<=query[i-1].r;j++) Delete(num[j]);
        for(int j=max(query[i-1].r+1,query[i].l);j<=query[i].r;j++) Insert(num[j]);
        ans[query[i].id]=tr[Findk(root,query[i].k+1)].val;
    }
    for(int i=0;i<M;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}