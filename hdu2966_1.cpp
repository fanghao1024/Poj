#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;
const int K=2;
int now;
struct Point{
	int dim[K];
};
bool cmp(const Point& a,const Point& b){
	return a.dim[now]<b.dim[now];
}
ll square(int x){return ((ll)x)*((ll)x);}
Point a[max_n],b[max_n];
int T,N;
void build(int l,int r,int d){
	if(l>=r) return ;
	int mid=(l+r)>>1;
	int dep=d%K;
	now=dep;
	nth_element(b+l,b+mid,b+r,cmp);
	build(l,mid,d+1);
	build(mid+1,r,d+1);
}
ll ans;
void query(int l,int r,int d,Point p){
	if(l>=r) return ;
	int mid=(l+r)>>1;
	int dep=d%K;
	ll dis=square(b[mid].dim[0]-p.dim[0])+square(b[mid].dim[1]-p.dim[1]);
	if(ans==0) ans=dis;
	if(dis!=0&&ans>dis) ans=dis;
	if(p.dim[dep]>b[mid].dim[dep]){
		query(mid+1,r,d+1,p);
		if(ans>square(p.dim[dep]-b[mid].dim[dep])) query(l,mid,d+1,p);
	}else{
		query(l,mid,d+1,p);
		if(ans>square(p.dim[dep]-b[mid].dim[dep])) query(mid+1,r,d+1,p);
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=0;i<N;i++){
			scanf("%d %d",&a[i].dim[0],&a[i].dim[1]);
			b[i]=a[i];
		}
		build(0,N,0);
		for(int i=0;i<N;i++){
			ans=0;
			query(0,N,0,a[i]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
