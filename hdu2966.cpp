#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;
const int max_n=100010;
const int K=2;
const ll inf=1e18;
#define sq(x) (x)*(x)
int T,N,idx;
ll ans;
struct Point{
	int dim[K];
}a[max_n],p[max_n];
bool cmp(const Point& a,const Point& b){
	return a.dim[idx]<b.dim[idx];
}
struct KD_Tree{
	void build(int l,int r,int dep){
		if(l>r) return ;
		int mid=((r-l)>>1)+l;
		idx=dep%K;
		nth_element(a+l,a+mid,a+r+1,cmp);
		build(l,mid-1,dep+1);
		build(mid+1,r,dep+1);
	}
	ll dis(Point p,Point q){
		ll res=0;
		for(int i=0;i<K;i++){
			res+=sqrt(((ll)p.dim[i]-q.dim[i])*((ll)p.dim[i]-q.dim[i]));
		}
		return res?res:inf;
	}
	void query(int l,int r,int dep,Point p){
		if(l>r) return ;
		int mid=(l+r)>>1,d=dep%K;
		ll dist=dis(a[mid],p);
		if(dist<ans) ans=dist;
		ll rd=sq((ll)p.dim[])
	}
}KDT;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=0;i<N;i++){
			scanf("%d %d",&a[i].dim[0],&a[i].dim[1]);
			p[i]=a[i];
		}
		KDT.build(0,N-1,0);
		for(int i=0;i<N;i++){
			ans=inf;
			KDT.query(0,N-1,0,p[i]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
