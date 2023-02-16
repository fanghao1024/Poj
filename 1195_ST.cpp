#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=1030;
int S;
struct Tr{
    int sum;
}tr[max_n<<2][max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void pushup(int xid,int yid){
    tr[xid][yid].sum=tr[xid][ls(yid)].sum+tr[xid][rs(yid)].sum;
}
void modify_y(int p,int pl,int pr,int y,int xid,int val,int flag){
    if(pl==pr){
        if(flag){
            tr[xid][p].sum+=val;
        }else{
            tr[xid][p].sum=tr[ls(xid)][p].sum+tr[rs(xid)][p].sum;
        }
        return ;
    }
    int mid=(pl+pr)>>1;
    if(y<=mid) modify_y(ls(p),pl,mid,y,xid,val,flag);
    else modify_y(rs(p),mid+1,pr,y,xid,val,flag);
    pushup(xid,p);
}
void modify_x(int p,int pl,int pr,int x,int y,int val){
    if(pl==pr){
        modify_y(1,1,S,y,p,val,1);
        return ;
    }
    int mid=(pl+pr)>>1;
    if(x<=mid) modify_x(ls(p),pl,mid,x,y,val);
    else modify_x(rs(p),mid+1,pr,x,y,val);
    modify_y(1,1,S,y,p,val,2);
}
int query_y(int p,int pl,int pr,int b,int t,int xid){
    if(b<=pl&&pr<=t){
        return tr[xid][p].sum;
    }
    int mid=(pl+pr)>>1;
    if(t<=mid) return query_y(ls(p),pl,mid,b,t,xid);
    else if(b>mid) return query_y(rs(p),mid+1,pr,b,t,xid);
    else return query_y(ls(p),pl,mid,b,mid,xid)+query_y(rs(p),mid+1,pr,mid+1,t,xid);
}
int query_x(int p,int pl,int pr,int l,int b,int r,int t){
    if(pl>r||pr<l) return 0;
    if(l<=pl&&pr<=r){
        return query_y(1,1,S,b,t,p);
    }
    int ans=0;
    int mid=(pl+pr)>>1;
    if(r<=mid) return query_x(ls(p),pl,mid,l,b,r,t);
    else if(l>mid) return query_x(rs(p),mid+1,pr,l,b,r,t);
    else return query_x(ls(p),pl,mid,l,b,mid,t)+query_x(rs(p),mid+1,pr,mid+1,b,r,t);
}
int main(){
    int ops;
    int x,y,a;
    int l,b,r,t;
    while(scanf("%d",&ops)!=EOF){
        if(ops==0){
            scanf("%d",&S);
            //memset(tr,0,sizeof(tr));
        }
        else if(ops==1){
            scanf("%d %d %d",&x,&y,&a);
            modify_x(1,1,S,x+1,y+1,a);
        }
        else if(ops==2){
            scanf("%d %d %d %d",&l,&b,&r,&t);
            printf("%d\n",query_x(1,1,S,l+1,b+1,r+1,t+1));
        }
        else if(ops==3) break;
    }
    return 0;
}