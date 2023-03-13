#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;
int N,M,x,y;
int num[max_n];
int Sum[max_n<<2],Max[max_n<<2],Min[max_n<<2],lMax[max_n<<2],lMin[max_n<<2],rMax[max_n<<2],rMin[max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void pushup(int p,int pl,int pr){
	int l=ls(p),r=rs(p);
	Sum[p]=Sum[l]+Sum[r];
	Max[p]=max(max(Max[l],Max[r]),rMax[l]+lMax[r]);
	Min[p]=min(min(Min[l],Min[r]),rMin[l]+lMin[r]);
	lMax[p]=max(lMax[l],Sum[l]+lMax[r]);
	lMin[p]=min(lMin[l],Sum[l]+lMin[r]);
	rMax[p]=max(rMax[r],Sum[r]+rMax[l]);
	rMin[p]=min(rMin[r],Sum[r]+rMin[l]);
}
void build(int p,int pl,int pr){
	if(pl==pr){
		Sum[p]=Max[p]=Min[p]=lMax[p]=lMin[p]=rMax[p]=rMin[p]=num[pl];
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	pushup(p,pl,pr);
}
void update(int p,int pl,int pr,int pos,int v){
	if(pl==pr){
		Sum[p]=Max[p]=Min[p]=lMax[p]=lMin[p]=rMax[p]=rMin[p]=v;
		return ;
	}
	int mid=(pl+pr)>>1;
	if(pos<=mid) update(ls(p),pl,mid,pos,v);
	else update(rs(p),mid+1,pr,pos,v);
	pushup(p,pl,pr);
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",&num[i]);
	build(1,1,N);
	scanf("%d",&M);
	while(M--){
		scanf("%d %d",&x,&y);
		update(1,1,N,x,y);
		int ans;
		if(Max[1]==Sum[1]){
			ans=Max[1]-Min[1];
		}else{
			ans=max(Max[1],Sum[1]-Min[1]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
