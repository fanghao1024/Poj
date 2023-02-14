#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n = 200010;
const int inf=0x3f3f3f3f;
int N,M,root,cnt,num[max_n],top,tag[max_n];
bool rev[max_n];
struct Tr{
    int fa;
    int val,size,mx;
    int son[2];
}tr[max_n];
int newNode(int father,int val){
    cnt++;
    tr[cnt].son[0]=tr[cnt].son[1]=0;
    tr[cnt].val=val;
    tr[cnt].fa=father;
    tr[cnt].size=1;
    tr[cnt].mx=val;
    tag[cnt]=0;
    rev[cnt]=0;
    return cnt;
}
void update(int p){
    int l=tr[p].son[0],r=tr[p].son[1];
    tr[p].size=1;
    tr[p].mx=tr[p].val;
    if(l) {tr[p].mx=min(tr[p].mx,tr[l].mx);tr[p].size+=tr[l].size;}
    if(r) {tr[p].mx=min(tr[p].mx,tr[r].mx);tr[p].size+=tr[r].size;}
}
void build(int l,int r,int& p,int father){
    if(l>r) return ;
    int mid=(l+r)>>1;
    p=newNode(father,num[mid]);
    build(l,mid-1,tr[p].son[0],p);
    build(mid+1,r,tr[p].son[1],p);
    update(p);
}
void init(){
    cnt=0;
    tr[0].son[0]=tr[0].son[1]=0;
    root=newNode(0,-inf);
    tr[root].son[1]=newNode(root,inf);
    //update(root);
    tr[root].size=2;
    build(1, N, tr[tr[root].son[1]].son[0],tr[root].son[1]);
    update(tr[root].son[1]);
    update(root);
}
void addtag(int p,int val){
    tag[p]+=val;
    tr[p].val+=val;
    tr[p].mx+=val;
}
void pushdown(int p){
    int l=tr[p].son[0],r=tr[p].son[1];
    if(rev[p]){
        rev[p]^=1;
        swap(tr[p].son[0],tr[p].son[1]);
        if(l) rev[l]^=1;
        if(r) rev[r]^=1;
    }
    if(tag[p]){
        if(l) addtag(l,tag[p]);
        if(r) addtag(r,tag[p]);
        tag[p]=0;
    }
}
void rotate(int x){
    pushdown(x);
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
    //st[top=1]=x;
    //for(int i=x;i;i=tr[i].fa) st[++top]=tr[i].fa;
    //while(top) pushdown(st[top--]);
    while(tr[x].fa!=goal){
        int f=tr[x].fa,g=tr[f].fa;
        if(g!=goal) (tr[g].son[0]==f)^(tr[f].son[0]==x)?rotate(x):rotate(f);
        rotate(x);
    }
    if(!goal) root=x;
}
int find(int u, int val)
{
    pushdown(u);
    int l = tr[u].son[0], r = tr[u].son[1];
    if (tr[l].size + 1 == val)
        return u;
    if (tr[l].size >= val)
        return find(l, val);
    return find(r, val - tr[l].size - 1);
}
int findx(int x, int k)
{
    while (1)
    {
        pushdown(x);
        int sn = tr[x].son[0] ? tr[tr[x].son[0]].size + 1 : 1;
        if (k == sn)
            return x;
        if (k > sn)
            k -= sn, x = tr[x].son[1];
        else
            x = tr[x].son[0];
    }
}
void insert(int x,int d){
    int a=find(root,x),b=find(root,x+1);
    splay(a,0);
    splay(b,a);
    tr[b].son[0]=newNode(b,d);
    update(b);
    update(a);
}
void addval(int x, int y, int d)
{
    int a=find(root,x-1),b=find(root,y+1);
    splay(a, 0);
    splay(b, a);
    addtag(tr[b].son[0], d);
    update(b);
    update(a);
}
void query(int x,int y){
    int a=find(root,x-1),b=find(root,y+1);
    splay(a,0);
    splay(b,a);
    printf("%d\n",tr[tr[b].son[0]].mx);
}
void remove(int x){
    int a = find(root, x-1), b = find(root, x + 1);
    splay(a,0);
    splay(b,a);
    tr[b].son[0]=0;
    update(b);
    update(a);
}
void reve(int x,int y){
    int a=find(root,x-1),b=find(root,y+1);
    splay(a,0);
    splay(b,a);
    rev[tr[b].son[0]]^=1;
}
void revo(int x,int y,int t){
    t%=y-x+1;
    if(t==0) return ;
    int a=find(root,y-t),b=find(root,y+1);
    splay(a,0);splay(b,a);
    int temp=tr[b].son[0];
    tr[b].son[0]=0;
    update(b);update(a);
    a=find(root,x-1);
    b=find(root,x);
    splay(a,0);
    splay(b,a);
    tr[b].son[0]=temp;
    tr[temp].fa=b;
    update(b);update(a);
}
int main(){
    while(scanf("%d",&N)!=EOF){
    for(int i=1;i<=N;i++){
        scanf("%d",&num[i]);
    }
    init();
    scanf("%d",&M);
    char ch[20];
    int x,y,z;
    while(M--){
        scanf("%s",ch);
        switch(ch[0]){
            case 'A':
                scanf("%d %d %d",&x,&y,&z);
                addval(x+1,y+1,z);
                break;
            case 'I':
                scanf("%d %d",&x,&y);
                insert(x+1,y);
                break;
            case 'D':
                scanf("%d",&x);
                remove(x+1);
                break;
            case 'M':
                scanf("%d %d",&x,&y);
                query(x+1,y+1);
                break;
            case 'R':
                if(ch[3]=='E'){
                    scanf("%d %d",&x,&y);
                    reve(x+1,y+1);
                }else{
                    scanf("%d %d %d",&x,&y,&z);
                    revo(x+1,y+1,z);
                }
                break;
        }
    }
    }
    return 0;
}