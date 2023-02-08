#include<stdio.h>

int par[150010];
int rank[150010];
int D[100005],X[100005],Y[100005];
void init(int n){
	for(int i=0;i<n;i++){
		par[i]=i;
		rank[i]=0;
	}
}
int find(int x){
	if(par[x]==x){
		return x;
	}else{
		return par[x]=find(par[x]);
	}
}
void unite(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y) return;
	if(rank[x]<rank[y]){
		par[x]=y;
	}else{
		par[y]=x;
		if(rank[x]==rank[y]){
			rank[x]++;
		}
	}
}
bool same(int x,int y){
	return find(x)==find(y);
}

int main(){
	int N,K;
	scanf("%d %d",&N,&K);
	for(int i=0;i<K;i++){
		scanf("%d %d %d",&D[i],&X[i],&Y[i]);
	}
	init(3*N);
	int ans=0;
	int x,y;
	for(int i=0;i<K;i++){
		if(X[i]<1||X[i]>N||Y[i]<1||Y[i]>N){
			ans++;
			continue;
		}
		x=X[i]-1;
		y=Y[i]-1;
		
		if(D[i]==1){
			if(same(x,y+N)||same(x,y+2*N)||same(x+N,y)||same(x+N,y+2*N)||same(x+2*N,y)||same(x+2*N,y+N)){
				ans++;
			}else{
				unite(x,y);
				unite(x+N,y+N);
				unite(x+2*N,y+2*N);
			}
		}else{
			if(same(x,y)||same(x,y+2*N)||same(x+N,y)||same(x+N,y+N)||same(x+2*N,y+2*N)||same(x+2*N,y+N)){
				ans++;
			}else{
				unite(x,y+N);
				unite(x+N,y+2*N);
				unite(x+2*N,y);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
