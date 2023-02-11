#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int max_n=100010;
struct Tr{
    int son[2];
    int val,size;
    int pri,tag;
}tr[max_n];
int N,M,cnt,root;
bool flag;
void Pushdown(int u){
    if(tr[u].tag){
        swap(tr[u].son[0],tr[u].son[1]);
        tr[u].tag^=1;
        if(tr[u].son[0]) tr[tr[u].son[0]].tag^=1;
        if (tr[u].son[1]) tr[tr[u].son[1]].tag ^= 1;
    }
}
void init(){
    cnt=root=0;
    tr[0].son[0]=tr[0].son[1]=0;
}
int newNode(int val){
    cnt++;
    tr[cnt].son[0]=tr[cnt].son[1]=0;
    tr[cnt].size=1;
    tr[cnt].pri=rand();
    tr[cnt].tag=0;
    tr[cnt].val=val;
    return cnt;
}
void Update(int p){
    tr[p].size=tr[tr[p].son[0]].size+tr[tr[p].son[1]].size+1;
}
void Split(int u,int val,int& L,int &R){
    if(!u){L=R=0;return ;}
    Pushdown(u);
    if(tr[tr[u].son[0]].size+1<=val){
        L=u;
        Split(tr[u].son[1],val-tr[tr[u].son[0]].size-1,tr[u].son[1],R);
    }else{
        R=u;
        Split(tr[u].son[0],val,L,tr[u].son[0]);
    }
    Update(u);
}
int Merge(int L,int R){
    if(!L||!R) return L+R;
    if(tr[L].pri>tr[R].pri){
        Pushdown(L);
        tr[L].son[1]=Merge(tr[L].son[1],R);
        Update(L);
        return L;
    }else{
        Pushdown(R);
        tr[R].son[0]=Merge(L,tr[R].son[0]);
        Update(R);
        return R;
    }
}
void print(int u){
    Pushdown(u);
    if(tr[u].son[0]) print(tr[u].son[0]);
    if(flag){
        printf("%d",tr[u].val);
        flag=0;
    }else{
        printf(" %d",tr[u].val);
    }
    if(tr[u].son[1]) print(tr[u].son[1]);
}
int main(){
    int x,y;
    scanf("%d %d",&N,&M);
    init();
    for(int i=1;i<=N;i++) root=Merge(root,newNode(i));
    while(M--){
        scanf("%d %d",&x,&y);
        int L,R,p;
        Split(root,y,L,R);
        Split(L,x-1,L,p);
        tr[p].tag^=1;
        root=Merge(Merge(L,p),R);
    }
    flag=1;
    print(root);
    printf("\n");
    return 0;
}