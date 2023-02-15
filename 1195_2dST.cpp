#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1030;
int S;
struct node_y{
	int l,r;
	int sum;
};
struct node_x{
	int l,r;
	node_y y[max_n<<2];	
}x[max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void build_y(int p,int pl,int pr,int id){
	x[id].y[p].l=pl;
	x[id].y[p].r=pr;
	x[id].y[p].sum=0;
	if(pl==pr) return ;
	int mid=(pl+pr)>>1;
	build_y(ls(p),pl,mid,id);
	build_y(rs(p),mid+1,pr,id);
}
void build_x(int p,int pl,int pr,int ypl,int ypr){
	x[p].l=pl;
	x[p].r=pr;
	build_y(1,ypl,ypr,p);
	if(pl==pr) return;
	int mid=(pl+pr)>>1;
	build_x(ls(p),pl,mid,ypl,ypr);
	build_x(rs(p),mid+1,pr,ypl,ypr);
}
void update_y(int p,int py,int val,int id){
	x[id].y[p].sum+=val;
	if(x[id].y[p].l==x[id].y[p].r) return ;
	int mid=(x[id].y[p].l+x[id].y[p].r)>>1;
	if(py<=mid) update_y(ls(p),py,val,id);
	else update_y(rs(p),py,val,id);
}
void update_x(int p,int px,int py,int val){
	update_y(1,py,val,p);
	if(x[p].l==x[p].r) return ;
	int mid=(x[p].l+x[p].r)>>1;
	if(px<=mid) update_x(ls(p),px,py,val);
	else update_x(rs(p),px,py,val);
}
int query_y(int p,int ll,int rr,int id){
	if(x[id].y[p].l==ll&&x[id].y[p].r==rr) return x[id].y[p].sum;
	int mid=(x[id].y[p].l+x[id].y[p].r)>>1;
	if(rr<=mid) return query_y(ls(p),ll,rr,id);
	else if(ll>mid) return query_y(rs(p),ll,rr,id);
	else return query_y(ls(p),ll,mid,id)+query_y(rs(p),mid+1,rr,id);
}
int query_x(int p,int l,int r,int ll,int rr){
	if(x[p].l==l&&x[p].r==r) return query_y(1,ll,rr,p);
	int mid=(x[p].l+x[p].r)>>1;
	if(r<=mid) return query_x(ls(p),l,r,ll,rr);
	else if(l>mid) return query_x(rs(p),l,r,ll,rr);
	else return query_x(ls(p),l,mid,ll,rr)+query_x(rs(p),mid+1,r,ll,rr);
	
}
int main(){
	int op,x,y,a;
	while(scanf("%d",&op)!=EOF){
		if(op==0){
			scanf("%d",&S);
			build_x(1,1,S,1,S);
		}else{
			if(op==1){
				scanf("%d %d %d",&x,&y,&a);
				update_x(1,x+1,y+1,a);
			}else{
				if(op==2){
					int x1,y1,x2,y2;
					scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
					printf("%d\n",query_x(1,x1+1,x2+1,y1+1,y2+1));
				}else{
					if(op==3) break;
				}
			}	
		}
	}
	return 0;
}
