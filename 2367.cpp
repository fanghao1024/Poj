#include<stdio.h>
#include<string.h>

const int max_n=105;
const int max_e=10005;
int N;
struct Edge{
	int to,nxt;
}edge[max_e];
int head[max_n];
int cnt;
int degree[max_n];
bool vis[max_n];
void add_edge(int x,int y){
	edge[++cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt;
}
int main(){
	scanf("%d",&N);
	memset(head,-1,sizeof(head));
	memset(degree,0,sizeof(degree));
	memset(vis,0,sizeof(vis));
	cnt=0;
	int x;
	for(int i=1;i<=N;i++){
		while(scanf("%d",&x)&&x){
			add_edge(i,x);
			degree[x]++;
		}
	}
	int count=0;
	while(count<N){
		for(int i=1;i<=N;i++){
			if(!vis[i]&&!degree[i]){
				if(count) printf(" ");
				printf("%d",i);
				count++;
				for(int j=head[i];j!=-1;j=edge[j].nxt){
					degree[edge[j].to]--;
				}
				vis[i]=1;
			}
		}
	}
	
	printf("\n");
	return 0;
}
