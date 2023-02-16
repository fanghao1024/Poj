#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=810;
const int inf=0x3fffffff;
int rec[max_n][max_n];
int T,N,M,x,y,l,xa,xb,ya,yb,Max,Min;
struct Tr{
    int Max,Min;
}tr[max_n<<2][max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void pushup(int xid,int yid){
    tr[xid][yid].Max=max(tr[xid][ls(yid)].Max,tr[xid][rs(yid)].Max);
    tr[xid][yid].Min=min(tr[xid][ls(yid)].Min,tr[xid][rs(yid)].Min);
}
void build_y(int p,int pl,int pr,int xid,int flag){
    if(pl==pr){
        if(flag==1){
            int val;
            scanf("%d",&val);
            tr[xid][p].Max=tr[xid][p].Min=val;
        }else{
            tr[xid][p].Max=max(tr[ls(xid)][p].Max,tr[rs(xid)][p].Max);
            tr[xid][p].Min = min(tr[ls(xid)][p].Min, tr[rs(xid)][p].Min);
        }
        return ;
    }
    int mid=(pl+pr)>>1;
    build_y(ls(p),pl,mid,xid,flag);
    build_y(rs(p),mid+1,pr,xid,flag);
    pushup(xid,p);
}
void build_x(int p,int pl,int pr){
    if(pl==pr){
        build_y(1,1,N,p,1);
        return ;
    }
    int mid=(pl+pr)>>1;
    build_x(ls(p),pl,mid);
    build_x(rs(p),mid+1,pr);
    build_y(1,1,N,p,2);
}
void query_y(int p,int pl,int pr,int xid){
    if(ya<=pl&&pr<=yb){
        Max=max(Max,tr[xid][p].Max);
        Min=min(Min,tr[xid][p].Min);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(ya<=mid) query_y(ls(p),pl,mid,xid);
    if(yb>mid) query_y(rs(p),mid+1,pr,xid);
}
void query_x(int p,int pl,int pr){
    if(xa<=pl&&pr<=xb){
        query_y(1,1,N,p);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(xa<=mid) query_x(ls(p),pl,mid);
    if(xb>mid) query_x(rs(p),mid+1,pr);
}
void modify_y(int p,int pl,int pr,int xid,int val,int flag){
    if(pl==pr){
        if(flag==1){
            tr[xid][p].Max=tr[xid][p].Min=val;
        }else{
            tr[xid][p].Max=max(tr[ls(xid)][p].Max,tr[rs(xid)][p].Max);
            tr[xid][p].Min=min(tr[ls(xid)][p].Min,tr[rs(xid)][p].Min);
        }
        return ;
    }
    int mid=(pl+pr)>>1;
    if(y<=mid) modify_y(ls(p),pl,mid,xid,val,flag);
    else modify_y(rs(p),mid+1,pr,xid,val,flag);
    pushup(xid,p);
}
void modify_x(int p,int pl,int pr,int temp){
    if(pl==pr){
        modify_y(1,1,N,p,temp,1);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(x<=mid) modify_x(ls(p),pl,mid,temp);
    else modify_x(rs(p),mid+1,pr,temp);
    modify_y(1,1,N,p,temp,2);
}
int main(){
    scanf("%d",&T);
    for(int caseNo=1;caseNo<=T;caseNo++){
        scanf("%d",&N);
        build_x(1,1,N);
        printf("Case #%d:\n",caseNo);
        scanf("%d", &M);
        while(M--){
            scanf("%d %d %d",&x,&y,&l);
            xa=max(1,x-l/2);
            xb=min(N,x+l/2);
            ya=max(1,y-l/2);
            yb=min(N,y+l/2);
            Max=-inf;
            Min=inf;
            query_x(1,1,N);
            int temp=(Max+Min)>>1;
            printf("%d\n",temp);
            modify_x(1,1,N,temp);
        }
    }
    return 0;
}