#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=300010;
const int inf=0x3f3f3f3f;
int N,M;
char ch[10];
int cnt,root;
bool flag;

struct Tr{
    int son[2];
    int val,fa;
    int rev,size;
}tr[max_n];

int newNode(int father,int val){
    cnt++;
    tr[cnt].son[0]=tr[cnt].son[1]=0;
    tr[cnt].fa=father;
    tr[cnt].size=1;
    tr[cnt].rev=0;
    tr[cnt].val=val;
    return cnt;
}
/*
void Update(int p){
    tr[p].size=tr[tr[p].son[0]].size+tr[tr[p].son[1]].size+1;
}
*/
void Update(int x)
{
    tr[x].size = 1;
    if (tr[x].son[0])
        tr[x].size += tr[tr[x].son[0]].size;
    if (tr[x].son[1])
        tr[x].size += tr[tr[x].son[1]].size;
}
void Pushdown(int u)
{
    if (tr[u].rev)
    {
        swap(tr[u].son[0], tr[u].son[1]);
        tr[u].rev ^= 1;
        if (tr[u].son[0])
            tr[tr[u].son[0]].rev ^= 1;
        if (tr[u].son[1])
            tr[tr[u].son[1]].rev ^= 1;
    }
}

void Build(int l,int r,int& p,int fa){
    if(l>r) return ;
    int mid=(l+r)>>1;
    p = newNode(fa, mid);
    Build(l,mid-1,tr[p].son[0],p);
    Build(mid+1,r,tr[p].son[1],p);
    Update(p);
}
void Init(){
    cnt=root=0;
    tr[0].son[0] = tr[0].son[1] = 0;
    root=newNode(0,-inf);
    tr[root].son[1]=newNode(root,inf);
    tr[root].size=2;
    Build(1, N, tr[tr[root].son[1]].son[0], tr[root].son[1]);
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
    int f=tr[x].fa,g=tr[f].fa;
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
void Cut(int a,int b,int c){
    int x=Find(root,a-1),y=Find(root,b+1);
    Splay(x,0);Splay(y,x);
    int temp=tr[y].son[0];
    tr[y].son[0]=0;
    Update(y);Update(x);
    x=Find(root,c);
    y=Find(root,c+1);
    Splay(x,0);Splay(y,x);
    tr[y].son[0]=temp;
    tr[temp].fa=y;
    Update(y);Update(x);
}
void Flip(int a,int b){
    int x = Find(root, a - 1), y = Find(root, b + 1);
    Splay(x, 0);
    Splay(y, x);
    tr[tr[y].son[0]].rev^=1;
}
void print(int u){
    Pushdown(u);
    if(tr[u].son[0]) print(tr[u].son[0]);
    if(tr[u].val!=inf&&tr[u].val!=-inf){
        if(flag){
            printf("%d",tr[u].val);
            flag=0;
        }else{
            printf(" %d",tr[u].val);
        }
    }
    if(tr[u].son[1]) print(tr[u].son[1]);
}
int main(){
    int a,b,c;
    while(scanf("%d %d",&N,&M)){
        if(N==-1&&M==-1) break;
        Init();
        while(M--){
            scanf("%s",ch);
            switch (ch[0])
            {
            case 'C':
                scanf("%d %d %d",&a,&b,&c);
                Cut(++a,++b,++c);
                break;
            
            case 'F':
                scanf("%d%d",&a,&b);
                Flip(++a,++b);
                break;
            }
        }
        flag=1;
        print(root);
        printf("\n");
    }
    return 0;
}