#include<stdio.h>
#include<string.h>

int N,M;
const int max_n=205;
const int max_m=40005;
int degree[max_n];
bool path[max_n][max_n];
bool vis[max_n];
int rec[max_n];

bool TopoSort(){
	memset(vis,0,sizeof(vis));
	int index=N;
	bool flag=true;
	while(flag)
	{
		flag=false;
		for(int i=N;i>=1;i--){
			if(!vis[i]&&!degree[i]){
				rec[i]=index--;
				vis[i]=1;
				flag=true;
				for(int j=1;j<=N;j++){
					if(path[i][j]){
						degree[j]--;
					}
				}
				break;
			}	
		}
	}
	if(index>0) return false;
	return true;
	
}

int main(){
	int case_num;
	scanf("%d",&case_num);
	while(case_num--){
		scanf("%d %d",&N,&M);
		memset(degree,0,sizeof(degree));
		memset(path,0,sizeof(path));
		int x,y;
		for(int i=0;i<M;i++){
			scanf("%d %d",&x,&y);
			if(!path[y][x]) degree[x]++;
			path[y][x]=1;
		}
		if(TopoSort()){
			for(int i=1;i<=N;i++){
				if(i-1) printf(" ");
				printf("%d",rec[i]);
			}
			printf("\n");
		}else{
			printf("-1\n");
		}
	}
	return 0;
}
