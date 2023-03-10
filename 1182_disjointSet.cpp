#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e4+10;

int par[max_n],d[max_n];
int N,K,ans;
void init(){
	for(int i=0;i<=N;i++){
		par[i]=i;
		d[i]=0;  //0同类，1吃，2被吃
	}
}
int find(int x){
	if(x!=par[x]){
		int f=par[x];
		par[x]=find(par[x]);
		d[x]=(d[x]+d[f])%3;
	}
	return par[x];
}
int main(){
	scanf("%d %d",&N,&K);
	init();
	ans=0;
	int relation,x,y;
	while(K--){
		scanf("%d %d %d",&relation,&x,&y);
		relation--;
		int rx=find(x);
		int ry=find(y);
		if(x>N||y>N||(relation==1&&x==y)){
			ans++;
			continue;
		}
		if(rx==ry){
			if((relation+d[y])%3!=d[x]) ans++;
		}else{
			par[rx]=ry;
			d[rx]=(d[y]+relation-d[x]+3)%3;
		}
	}
	printf("%d\n",ans);
	return 0;
}
