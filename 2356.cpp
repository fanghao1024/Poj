#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e4+10;

int sum[max_n],num[max_n],ind[max_n];
int N;

int main(){
	while(scanf("%d",&N)!=EOF){
		for(int i=1;i<=N;i++) scanf("%d",&num[i]);
		sum[0]=0;
		int i;
		int start,lst;
		bool flag=false;
		for(i=1;i<=N;i++){
			sum[i]=(sum[i-1]+num[i])%N;
			if(sum[i]%N==0) {flag=true;break;}
		}
		if(flag){
			printf("%d\n",i);
			for(int j=1;j<=i;j++) printf("%d\n",num[j]);
		}else{
			memset(ind,-1,sizeof(ind));
			for(i=1;i<=N;i++){
				for(int j=i+1;j<=N;j++){
					if(sum[i]==sum[j]){
						flag=true;
						start=i+1;
						lst=j;
						break;
					}
				}
				if(flag) break;
			}
			if(!flag) printf("0\n");
			else{
				printf("%d\n",lst-start+1);
				for(i=start;i<=lst;i++) printf("%d\n",num[i]);
			}
		}
	}
	return 0;
}
