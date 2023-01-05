#include<stdio.h>
#include<string.h>

short int record[105][100010];
int A[105];
int C[105];
bool used[105];

int main(){
	int n,m;
	while(scanf("%d %d",&n,&m)!=EOF){
		if(n==0&&m==0){
			break;
		}
		for(int i=0;i<n;i++){
			scanf("%d",&A[i]);
		}
		for(int i=0;i<n;i++){
			scanf("%d",&C[i]);
		}

		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++)
				record[i][j]=-1;
			used[i]=false;
		}
		record[0][0]=0;
		int ans=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(record[i-1][j]>=0){
					record[i][j]=C[i-1];
					if(j>0&&!used[j]){
						used[j]=true;
						ans++;
					}
				}else{
					if(j<A[i-1]||record[i][j-A[i-1]]<=0){
						record[i][j]=-1;
					}else{
						record[i][j]=record[i][j-A[i-1]]-1;
						if(j>0&&!used[j]){
							used[j]=true;
							ans++;
						}
					}
				}
			}
		}

		printf("%hd\n",ans);
	}
	return 0;
}
