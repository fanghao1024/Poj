#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

int ls(int x) { return x << 1; }
int rs(int x) { return x << 1 | 1; }
const int max_n=10010;

int N,cnt;
struct Tree{
    int y;
    int lx,rx;
    int inout;
    Tree(){};
    Tree(int _y,int _lx,int _rx,int _inout){
        y=_y;lx=_lx;rx=_rx;inout=_inout;
    }
}tr[max_n<<1];
bool cmp(const Tree &m, const Tree &n)
{
    return m.y < n.y||(m.y==n.y&&m.inout>n.inout);
}

bool left[max_n<<3],right[max_n<<3];
int num[max_n<<3],length[max_n<<3],tag[max_n<<3];


void pushup(int p,int pl,int pr){
    if(tag[p]){
        left[p] = right[p] =1;
        length[p] = pr - pl + 1;
        num[p]=1;
    }
    else if(pl==pr)
    {
        left[p] = right[p] = length[p]=num[p]=0;
    }else{
        length[p]=length[ls(p)]+length[rs(p)];
        left[p]=left[ls(p)];
        right[p]=right[rs(p)];
        num[p]=num[ls(p)]+num[rs(p)];
        if(right[ls(p)]&&left[rs(p)]) num[p]--;
    }
}
void update(int p,int pl,int pr,int L,int R,int inout){
    if(L<=pl&&pr<=R){
        tag[p]+=inout;
        pushup(p,pl,pr);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(L<=mid) update(ls(p),pl,mid,L,R,inout);
    if(R>mid) update(rs(p),mid+1,pr,L,R,inout);
    pushup(p,pl,pr);
}
int main(){
    int x1,y1,x2,y2;
    while(scanf("%d",&N)!=EOF){
        cnt=0;
        int L = 10000, R = -10000;
        for (int i = 1; i <= N; i++)
        {
            scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            tr[++cnt]=Tree(y1,x1,x2,1);
            tr[++cnt]=Tree(y2,x1,x2,-1);
            L=min(L,min(x1,x2));
            R=max(R,max(x1,x2));
        }
        sort(tr+1,tr+1+cnt,cmp);
        int ans=0,last=0;
        memset(left,0,sizeof(left));
        memset(right,0,sizeof(right));
        memset(num,0,sizeof(num));
        memset(length,0,sizeof(length));
        memset(tag,0,sizeof(tag));
        for(int i=1;i<=cnt;i++){
            if(tr[i].lx<tr[i].rx)
            update(1, L, R - 1, tr[i].lx, tr[i].rx - 1, tr[i].inout);
            ans+=2*num[1]*(tr[i+1].y-tr[i].y);
            ans+=abs(length[1]-last);
            last=length[1];
        }
        printf("%d\n",ans);
    }
    return 0;
}