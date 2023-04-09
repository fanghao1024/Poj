#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e5+10;
const int max_m=2e5+10;
const int K=2;
const double alpha=0.75;

struct Point{
    int dim[K];
    int val;
    Point(){};
    Point(int x,int y,int vall){
        dim[0]=x;dim[1]=y;val=vall;
    }
};
struct Tree{
    int l,r;
    int siz;
    int sum;
    int Min[K],Max[K];
    Point p;
}tr[max_m];
int N,opt,root,tot,now;
int tree_stack[max_n],top;
Point order[max_n];
int cnt;
bool cmp(const Point& a,const Point& b){
    return a.dim[now]<b.dim[now];
}
int ls(int x){return tr[x].l;}
int rs(int x){return tr[x].r;}
bool notbalance(int u){
    if(tr[u].siz*alpha<max(tr[ls(u)].siz,tr[rs(u)].siz)) return true;
    return false;
}
void Update(int u){
    tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
    tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum+tr[u].p.val;
    for(int i=0;i<K;i++){
        tr[u].Min[i]=tr[u].Max[i]=tr[u].p.dim[i];
        if(tr[u].l){
            tr[u].Min[i]=min(tr[u].Min[i],tr[ls(u)].Min[i]);
            tr[u].Max[i]=max(tr[u].Max[i],tr[ls(u)].Max[i]);
        }
        if(tr[u].r){
            tr[u].Min[i] = min(tr[u].Min[i], tr[rs(u)].Min[i]);
            tr[u].Max[i] = max(tr[u].Max[i], tr[rs(u)].Max[i]);
        }
    }
}
void inorder(int u){
    if(!u) return ;
    inorder(ls(u));
    tree_stack[++top]=u;
    order[++cnt]=tr[u].p;
    inorder(rs(u));
}
int build(int l,int r,int d){
    if(l>r) return 0;
    int u;
    if(top) u=tree_stack[top--];
    else u=++tot;
    int mid=(l+r)>>1;
    now=d;
    nth_element(order+l,order+mid,order+1+r,cmp);
    tr[u].p=order[mid];
    tr[u].l=build(l,mid-1,d^1);
    tr[u].r=build(mid+1,r,d^1);
    Update(u);
    return u;
}
void rebuild(int& u){
    cnt=0;
    inorder(u);
    if(!cnt) u=0;
    else u=build(1,cnt,0);
}
void Insert(int& u,Point x,int d){
    if(!u){
        if(top) u=tree_stack[top--];
        else u=++tot;
        tr[u].l=tr[u].r=0;
        tr[u].p = x;
        tr[u].siz=1;
        tr[u].Min[0]=tr[u].Max[0]=x.dim[0];
        tr[u].Min[1]=tr[u].Max[1]=x.dim[1];
        tr[u].sum=x.val;
        return ;
    }

    if(x.dim[d]>tr[u].p.dim[d]) Insert(tr[u].r,x,d^1);
    else Insert(tr[u].l,x,d^1);
    Update(u);
    if(notbalance(u)) rebuild(u);
}
int query(int u,int x1,int y1,int x2,int y2){
    if(!u) return 0;
    int X1=tr[u].Min[0],X2=tr[u].Max[0];
    int Y1=tr[u].Min[1],Y2=tr[u].Max[1];
    if(x1<=X1&&X2<=x2&&y1<=Y1&&Y2<=y2) return tr[u].sum;
    if(X1>x2||X2<x1||Y1>y2||Y2<y1) return 0;
    int mid1=(x1+x2)>>1,mid2=(y1+y2)>>1;
    int res=0;
    if(x1<=tr[u].p.dim[0]&&tr[u].p.dim[0]<=x2&&y1<=tr[u].p.dim[1]&&tr[u].p.dim[1]<=y2) res+=tr[u].p.val;
    res+=query(ls(u),x1,y1,x2,y2);
    res+=query(rs(u),x1,y1,x2,y2);
    return res;
}
int main(){
    scanf("%d",&N);
    int last_ans=0;
    int x1,x2,y1,y2,A;
    while(1){
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d %d %d",&x1,&y1,&A);
            x1^=last_ans;y1^=last_ans;A^=last_ans;
            Insert(root,Point(x1,y1,A),0);
        }
        else if(opt==2){
            scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            x1^=last_ans;y1^=last_ans;x2^=last_ans;y2^=last_ans;
            last_ans=query(root,x1,y1,x2,y2);
            printf("%d\n",last_ans);
        }
        else if(opt==3) break;
    }
    return 0;
}

