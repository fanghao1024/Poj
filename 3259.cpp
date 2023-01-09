#include<stdio.h>

struct Edge{
	int S,E,T;
}edge[5210];
int d[1000];
const int INF=10000000;
int main(){
	int F;
	int N,M,W;
	scanf("%d",&F);
	int i;
	while(F--){
		scanf("%d %d %d",&N,&M,&W);
		for(i=0;i<M;i++){
			scanf("%d %d %d",&edge[2*i].S,&edge[2*i].E,&edge[2*i].T);
			edge[2*i+1].S=edge[2*i].E;
			edge[2*i+1].E=edge[2*i].S;
			edge[2*i+1].T=edge[2*i].T;
		}
		i*=2;
		for(int j=0;j<W;j++){
			scanf("%d %d %d",&edge[i+j].S,&edge[i+j].E,&edge[i+j].T);
			edge[i+j].T=-edge[i+j].T;
		}
		d[1]=0;
		for(i=2;i<=N;i++){
			d[i]=INF;
		}
		bool flag;
		bool ans=false;
		for(i=0;i<N;i++){
			flag=false;
			for(int j=0;j<2*N+W;j++){
				Edge e=edge[j];
				if(d[e.E]>d[e.S]+e.T){
					d[e.E]=d[e.S]+e.T;
					flag=true;
				}
			}
			if(!flag){
				break;
			}
			if(d[1]==-1){
				ans=true;
				break;
			}
		}
		if(ans){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}
