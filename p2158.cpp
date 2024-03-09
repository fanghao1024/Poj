#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=4e4+10;
int vis[max_n],prime[max_n],sum[max_n],phi[max_n];
int cnt,N;
void get_phi(){
	cnt=0;
	phi[1]=1;
	for(int i=2;i<max_n;i++){
		if(!vis[i]){
			vis[i]=i;
			prime[cnt++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<cnt;j++){
			if(i*prime[j]>max_n) break;
			vis[i*prime[j]]=prime[j];
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*phi[prime[j]];
		}
	}
}
int main(){
	get_phi();
	scanf("%d",&N);
	sum[1]=1;
	for(int i=2;i<max_n;i++) sum[i]=sum[i-1]+phi[i];
	if(N==1) printf("0\n");
	else printf("%d\n",2*sum[N-1]+1);
	return 0;
}
