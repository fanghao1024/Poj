#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=200010;
const int inf=0x3f3f3f3f;

int N,M,k1,k2,cnt,root;
int num[max_n],sum;
struct Tr{
    int son[2];
    int fa,val;
    int size,rev,add;
}tr[max_n];
int newNode(int father,int val){
    cnt++;
    tr[cnt].son[0]=tr[cnt].son[1]=0;
    tr[cnt].val=val;
    tr[cnt].fa=father;
    tr[cnt].size=1;
    tr[cnt].add=tr[cnt].rev=0;
    return cnt;
}
void update(int p){
    tr[p].size=1;
    if(tr[p].son[0]) tr[p].size+=tr[tr[p].son[0]].size;
    if(tr[p].son[1]) tr[p].size+=tr[tr[p].son[1]].size;
}
void addtag(int p,int d){
    tr[p].add+=d;
    tr[p].val+=d;
}
void pushdown(int p){
    if(tr[p].rev){
        tr[p].rev^=1;
        swap(tr[p].son[0],tr[p].son[1]);
        if(tr[p].son[0]) tr[tr[p].son[0]].rev^=1;
        if(tr[p].son[1]) tr[tr[p].son[1]].rev^=1;
    }
    if(tr[p].add){
        if(tr[p].son[0]) addtag(tr[p].son[0],tr[p].add);
        if(tr[p].son[1]) addtag(tr[p].son[1],tr[p].add);
        tr[p].add=0;
    }
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
    sum=N;
    tr[0].son[0]=tr[0].son[1]=0;
    tr[0].size=0;
    root=newNode(0,-inf);
    tr[root].son[1]=newNode(root,inf);
    tr[root].size=2;
    build(1,N,tr[tr[root].son[1]].son[0],tr[root].son[1]);
    update(tr[root].son[1]);
    update(root);
}
int Findx(int u,int k){
    pushdown(u);
    if(tr[tr[u].son[0]].size+1==k) return u;
    if(tr[tr[u].son[0]].size>=k) return Findx(tr[u].son[0],k);
    return Findx(tr[u].son[1],k-tr[tr[u].son[0]].size-1);
}
int Find(int x, int k)
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
void Add(int d){
    int a = Find(root, 1), b = Find(root, 2+k2);
    splay(a, 0);
    splay(b, a);
    addtag(tr[b].son[0], d);
}
void Rev(){
    int a=Find(root,1),b=Find(root,2+k1);
    splay(a,0);
    splay(b,a);
    tr[tr[b].son[0]].rev^=1;
}
void Insert(int pos,int val){
    int a=Find(root,pos),b=Find(root,pos+1);
    splay(a,0);splay(b,a);
    tr[b].son[0]=newNode(b,val);
    update(b);
    update(a);
    sum++;
}
int Delete(int pos){
    int a=Find(root,pos-1),b=Find(root,pos+1);
    splay(a,0);splay(b,a);
    int temp=tr[tr[b].son[0]].val;
    tr[b].son[0]=0;
    update(b);
    update(a);
    sum--;
    return temp;
}
void Move(int x){
    int a,b,lens;
    if(x==1){
        lens = tr[root].size;
        a = Find(root, lens - 2);
        b = Find(root, lens);
        splay(a, 0);
        splay(b, a);
        int temp = tr[b].son[0];
        tr[b].son[0] = 0;
        update(b);
        update(a);

        a = Find(root, 1);
        b = Find(root, 2);
        splay(a, 0);
        splay(b, a);
        tr[b].son[0] = temp;
        update(b);
        update(a);
    }else{
        a=Find(root,1);b=Find(root,3);
        splay(a,0);splay(b,a);
        int temp=tr[b].son[0];
        tr[b].son[0]=0;
        update(b);update(a);
        lens=tr[root].size;
        //printf("root:%d lens:%d\n",root,lens);
        a=Find(root,lens-1);b=Find(root,lens);
        splay(a,0);splay(b,a);
        tr[b].son[0]=temp;
        update(b);update(a);
    }
}
void query(){
    int a=Find(root,2);
    printf("%d\n",tr[a].val);
}
void Print(int u){
    if(tr[u].son[0]) Print(tr[u].son[0]);
    //printf("%d==%d ",tr[u].val,tr[u].size);
    if(tr[u].son[1]) Print(tr[u].son[1]);
}
int main(){
    int case_no=1;
    while(scanf("%d %d %d %d",&N,&M,&k1,&k2)!=EOF){
        if(N==0&&M==0&&k1==0&&k2==0) break;
        k1%=N;
        k2%=N;
        for(int i=1;i<=N;i++) scanf("%d",&num[i]);
        init();
        printf("Case #%d:\n",case_no++);
        char ops[20];
        int x,pos=2;
        
        while(M--){
            scanf("%s",ops);
            switch(ops[0]){
                case 'a':
                    scanf("%d",&x);
                    Add(x);
                    break;
                case 'r':
                    Rev();
                    break;
                case 'i':
                    scanf("%d",&x);
                    Insert(2,x);
                    break;
                case 'd':
                    Delete(2);
                    break;
                case 'm':
                    scanf("%d",&x);
                    if(x==1){int y=Delete(sum+1);Insert(1,y);}
                    else{int y=Delete(2);Insert(sum+1,y);}
                    break;
                case 'q':
                    query();
                    break;
            }
        }
    }
    return 0;
}