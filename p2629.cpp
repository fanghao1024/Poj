#include<cstdio>

const int max_n=1e6+10;

int num[max_n<<1];
int q[max_n<<1];
int N;

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",num+i);
	for(int i=N+1;i<N*2;i++){
		num[i]=num[i-N];
	}
	for(int i=2;i<N*2;i++) num[i]+=num[i-1];
	int f=0,r=-1;
	for(int i=1;i<=N;i++){
		while(f<=r&&num[q[r]]>num[i]) r--;
		q[++r]=i;
	}
	int ans=0;
	for(int k=1;k<=N;k++){
		if(num[q[f]]-num[k-1]>=0) ans++;
		while(f<=r&&num[q[r]]>num[k+N]) r--;
		q[++r]=k+N;
		while(f<=r&&q[f]<k) f++;
	}
	printf("%d\n",ans);
	return 0;
}
