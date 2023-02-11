#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int max_n=100010;
int N,M,root,cnt;
bool flag;
struct Tr{
    int ls,rs;
    int pri,size;
    int val,tag;
}tr[max_n];

int newNode(int val){
    cnt++;
    tr[cnt].ls=tr[cnt].rs=0;
    tr[cnt].size=1;
    tr[cnt].pri=rand();
    tr[cnt].val=val;
    tr[cnt].tag=0;
    return cnt;
}
void Update(int p){
    tr[p].size=tr[tr[p].ls].size+tr[tr[p].rs].size+1;
}
void Pushdown(int p){
    if(tr[p].tag){
        tr[p].tag^=1;
        swap(tr[p].ls,tr[p].rs);
        if(tr[p].ls) tr[tr[p].ls].tag^=1;
        if(tr[p].rs) tr[tr[p].rs].tag^=1;
    }
}
void init(){
    cnt=root=0;
    tr[0].ls=tr[0].rs=0;
}
void Split(int u,int val,int& L,int& R){
    if(!u){L=R=0;return;}
    Pushdown(u);
    if(tr[tr[u].ls].size+1<=val){
        L=u;
        Split(tr[u].rs,val-tr[tr[u].ls].size-1,tr[u].rs,R);
    }else{
        R=u;
        Split(tr[u].ls,val,L,tr[u].ls);
    }
    Update(u);
}
int Merge(int L,int R){
    if(!L||!R) return L+R;
    if(tr[L].pri>tr[R].pri){
        Pushdown(L);
        tr[L].rs=Merge(tr[L].rs,R);
        Update(L);
        return L;
    }else{
        Pushdown(R);
        tr[R].ls=Merge(L,tr[R].ls);
        Update(R);
        return R;
    }
}
void Print(int u){
    Pushdown(u);
    if(tr[u].ls) Print(tr[u].ls);
    if(flag){
        printf("%d",tr[u].val);
        flag=0;
    }else{
        printf(" %d",tr[u].val);
    }
    if(tr[u].rs) Print(tr[u].rs);
}
int main(){
    scanf("%d %d",&N,&M);
    init();
    for(int i=1;i<=N;i++) root=Merge(root,newNode(i));
    int x,y;
    while(M--){
        scanf("%d %d",&x,&y);
        int L,R,p;
        Split(root,y,L,R);
        Split(L,x-1,L,p);
        tr[p].tag^=1;
        root=Merge(Merge(L,p),R);
    }
    flag=1;
    Print(root);
    printf("\n");
    return 0;
}