#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e4+10;
int N,M;
struct Tree{
	int sum,lsum,rsum,tag;
}tr[max_n<<2];
int read(){
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num*=10;
		num+=ch-'0';
		ch=getchar();
	}
	return num*f;
}
inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}
void push_up(int p,int len){
	tr[p].sum=max(max(tr[ls(p)].sum,tr[rs(p)].sum),tr[ls(p)].rsum+tr[rs(p)].lsum);
	tr[p].lsum=tr[ls(p)].lsum;
	tr[p].rsum=tr[rs(p)].rsum;
	if(tr[ls(p)].lsum==len-(len>>1)) tr[p].lsum=tr[ls(p)].lsum+tr[rs(p)].lsum;
	if(tr[rs(p)].rsum==(len>>1)) tr[p].rsum=tr[rs(p)].rsum+tr[ls(p)].rsum;
}
void build(int p,int pl,int pr){
	if(pl==pr){
		tr[p].sum=tr[p].lsum=tr[p].rsum=1;
		tr[p].tag=-1;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p,pr-pl+1);
}
void push_down(int p,int pl,int pr){
	if(tr[p].tag!=-1){
		tr[ls(p)].tag=tr[rs(p)].tag=tr[p].tag;
		int mid=(pl+pr)>>1;
		tr[ls(p)].sum=tr[ls(p)].lsum=tr[ls(p)].rsum=(tr[p].tag==0)?(mid-pl+1):0;
		tr[rs(p)].sum=tr[rs(p)].lsum=tr[rs(p)].rsum=(tr[p].tag==0)?(pr-mid):0;
		tr[p].tag=-1;
	}
}
int query(int p,int pl,int pr,int d){
	if(pl==pr&&d==1) return pl;
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(tr[ls(p)].sum>=d) return query(ls(p),pl,mid,d);
	else if(tr[ls(p)].rsum+tr[rs(p)].lsum>=d) return mid-tr[ls(p)].rsum+1;
	else if(tr[rs(p)].sum>=d) return query(rs(p),mid+1,pr,d);
	else return 0;
}
void update(int p,int pl,int pr,int L,int R,int d){
	if(L<=pl&&pr<=R){
		tr[p].tag=d;
		tr[p].sum=tr[p].lsum=tr[p].rsum=(d==0)?(pr-pl+1):0;
		return ;
	}
	int mid=(pl+pr)>>1;
	push_down(p,pl,pr);
	if(L<=mid) update(ls(p),pl,mid,L,R,d);
	if(R>mid) update(rs(p),mid+1,pr,L,R,d);
	push_up(p,pr-pl+1);
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		build(1,1,N);
		int ops,x,d;
		while(M--){
			scanf("%d",&ops);
			if(ops==1)
			{
				scanf("%d",&d);
				int temp=query(1,1,N,d);
				printf("%d\n",temp);
				if(temp) update(1,1,N,temp,temp+d-1,1);
			}
			else
			{
				scanf("%d %d",&x,&d);
				update(1,1,N,x,x+d-1,0);
			}

		}
	}
	return 0;
}

