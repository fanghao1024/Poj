#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2e5+10;
int ans[max_n],p[max_n],v[max_n],tree[max_n<<2];
int N;
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
int read(){
	int num=0,f=1;
	char c=getchar();
	while(c<'0'||c>'0'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		num*=10;
		num+=c-'0';
		c=getchar();
	}
	return num*f;
}
void build(int p,int pl,int pr){
	tree[p]=pr-pl+1;
	if(pl==pr) return ;
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
}
int query(int p,int pl,int pr,int k){
	tree[p]--;
	if(pl==pr){
		return pl;
	}
	int mid=(pl+pr)>>1;
	
	if(k<=tree[ls(p)]) return query(ls(p),pl,mid,k);
	else return query(rs(p),mid+1,pr,k-tree[ls(p)]);
}
int main(){
	while(scanf("%d",&N)!=EOF){
		build(1,1,N);
		for(int i=1;i<=N;i++) scanf("%d %d",&p[i],&v[i]);
		for(int i=N;i>=1;i--){
			ans[query(1,1,N,p[i]+1)]=v[i];
		}
		for(int i=1;i<=N;i++){
			if(i-1) printf(" ");
			printf("%d",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
