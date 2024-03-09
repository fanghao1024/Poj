#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=55;
bool path[max_n][max_n][34];
int map[max_n][max_n];
int N,M;
int main(){
	scanf("%d %d",&N,&M);
	int x,y;
	memset(path,0,sizeof(path));
	memset(map,0x3f,sizeof(map));
	while(M--){
		scanf("%d %d",&x,&y);
		map[x][y]=1;
		path[x][y][0]=1;
	}
	for(int z=1;z<=32;z++){
		for(int k=1;k<=N;k++){
			for(int i=1;i<=N;i++){
				for(int j=1;j<=N;j++){
					if(path[i][k][z-1]&&path[k][j][z-1]){
						map[i][j]=1;
						path[i][j][z]=1;
					}
				}
			}
		}
	}
	for(int k=1;k<=N;k++){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				if(map[i][j]>map[i][k]+map[k][j]){
					map[i][j]=map[i][k]+map[k][j];
				}
			}
		}
	}
	printf("%d\n",map[1][N]);
	return 0;
}
