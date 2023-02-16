#include<cstdio>

const int max_n=1024;
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
void build_y(int p,int ll,int rr,int id){
	x[id].y[p].l=ll;
	x[id].y[p].r=rr;
	x[id].y[p].sum=0;
	if(x[id].y[p].l==x[id].y[p].r) return ;
	int mid=(x[id].y[p].l+x[id].y[p].r)>>1;
	build_y(ls(p),ll,mid,id);
	build_y(rs(p),mid+1,rr,id);
}
void build_x(int p,int l,int r,int ll,int rr){
	x[p].l=l;
	x[p].r=r;
	build_y(1,ll,rr,p);
	if(x[p].l==x[p].r) return ;
	int mid=(x[p].l+x[p].r)>>1;
	build_x(ls(p),l,mid,ll,rr);
	build_x(rs(p),mid+1,r,ll,rr);
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
	else if(px>mid) update_x(rs(p),px,py,val);
}
int query_y(int p,int l,int r,int id){
	if(x[id].y[p].l==l&&x[id].y[p].r==r) return x[id].y[p].sum;
	int mid=(x[id].y[p].l+x[id].y[p].r)>>1;
	if(r<=mid) return query_y(ls(p),l,r,id);
	else if(l>mid) return query_y(rs(p),l,r,id);
	else return query_y(ls(p),l,mid,id)+query_y(rs(p),mid+1,r,id);
}
int query_x(int p,int l,int r,int ll,int rr){
	if(x[p].l==l&&x[p].r==r) return query_y(1,ll,rr,p);
	int mid=(x[p].l+x[p].r)>>1;
	if(r<=mid) return query_x(ls(p),l,r,ll,rr);
	else if(l>mid) return query_x(rs(p),l,r,ll,rr);
	else return query_x(ls(p),l,mid,ll,rr)+query_x(rs(p),mid+1,r,ll,rr);
}
int main(){
	int ops,S;
	while(scanf("%d",&ops)!=EOF){
		if(ops==0){
			scanf("%d",&S);
			build_x(1,1,S,1,S);
		}
		else if(ops==1){
			int x,y,a;
			scanf("%d %d %d",&x,&y,&a);
			update_x(1,x+1,y+1,a);
		}
		else if(ops==2){
			int x1,y1,x2,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			printf("%d\n",query_x(1,x1+1,x2+1,y1+1,y2+1));
		}
		else break;
	}
	return 0;
}
