#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=805;
const int inf=0x3fffffff;
int T,N,Q,xa,xb,ya,yb,ma,mi;
int x, y, l;
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
struct Node{
    int Max,Min;
}tr[max_n<<2][max_n<<2];
void push_up(int xid,int yid){
    tr[xid][yid].Max=max(tr[xid][ls(yid)].Max,tr[xid][rs(yid)].Max);
    tr[xid][yid].Min = min(tr[xid][ls(yid)].Min, tr[xid][rs(yid)].Min);
}
void build_y(int id,int py,int pl,int pr,int flag){
    int mid,val;
    if(pl==pr){
        if(flag==1){
            scanf("%d",&val);
            tr[id][py].Max=tr[id][py].Min=val;
        }else{
            tr[id][py].Max=max(tr[ls(id)][py].Max,tr[rs(id)][py].Max);
            tr[id][py].Min=min(tr[ls(id)][py].Min,tr[rs(id)][py].Min);
        }
        return ;
    }
    mid=(pl+pr)>>1;
    build_y(id,ls(py),pl,mid,flag);
    build_y(id,rs(py),mid+1,pr,flag);
    push_up(id,py);
}
void build_x(int p,int pl,int pr){
    if(pl==pr){
        build_y(p,1,1,N,1);
        return ;
    }
    int mid=(pl+pr)>>1;
    build_x(ls(p),pl,mid);
    build_x(rs(p),mid+1,pr);
    build_y(p,1,1,N,2);
}
void query_y(int py,int pl,int pr,int xid,int yl,int yr){
    if(yl<=pl&&pr<=yr){
        ma=max(ma,tr[xid][py].Max);
        mi=min(mi,tr[xid][py].Min);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(yl<=mid) query_y(ls(py),pl,mid,xid,yl,yr);
    if(yr>mid) query_y(rs(py),mid+1,pr,xid,yl,yr);

}
void query_x(int p,int pl,int pr,int xl,int xr){
    if(xl<=pl&&pr<=xr){
        query_y(1,1,N,p,ya,yb);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(xl<=mid) query_x(ls(p),pl,mid,xl,xr);
    if(xr>mid) query_x(rs(p),mid+1,pr,xl,xr);
}
void modify_y(int p,int pl,int pr,int xid,int val,int flag){
    if(pl==pr){
        if(flag==1) tr[xid][p].Max=tr[xid][p].Min=val;
        else{
            tr[xid][p].Max=max(tr[ls(xid)][p].Max,tr[rs(xid)][p].Max);
            tr[xid][p].Min=min(tr[ls(xid)][p].Min,tr[rs(xid)][p].Min);
        }
        return ;
    }
    int mid=(pl+pr)>>1;
    if(y<=mid) modify_y(ls(p),pl,mid,xid,val,flag);
    else modify_y(rs(p),mid+1,pr,xid,val,flag);
    push_up(xid,p);
}
void modify_x(int p,int pl,int pr,int val){
    if(pl==pr){
        modify_y(1,1,N,p,val,1);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(x<=mid) modify_x(ls(p),pl,mid,val);
    else modify_x(rs(p),mid+1,pr,val);
    modify_y(1,1,N,p,val,2);
}
int main(){
    scanf("%d",&T);
    for(int caseNo=1;caseNo<=T;caseNo++){
        scanf("%d",&N);
        build_x(1,1,N);
        printf("Case #%d:\n", caseNo);
        scanf("%d",&Q);
        
        while(Q--){
            scanf("%d %d %d",&x,&y,&l);
            xa=max(1,x-l/2);
            xb=min(N,x+l/2);
            ya=max(1,y-l/2);
            yb=min(N,y+l/2);
            ma=-inf;
            mi=inf;
            query_x(1,1,N,xa,xb);
            int temp=(ma+mi)/2;
            printf("%d\n",temp);
            modify_x(1,1,N,temp);
        }
    }
    
    return 0;
}