#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;

const int max_n=100010;
int num[max_n];
int rec[max_n];
int N,M;
int belong[max_n];
int L[340],R[340];
int len,blocks;

void init(){
	len=int(sqrt(N+0.0));
	blocks=N/len;
	if(N%len) blocks++;
	for(int i=0;i<blocks;i++){
		L[i]=i*len;
		R[i]=len*(i+1)-1;
	}
	R[blocks-1]=N-1;
	for(int i=0;i<blocks;i++)
		sort(rec+L[i],rec+R[i]+1);
	
	for(int i=0;i<N;i++){
		belong[i]=i/len;
	}
	
}
int solve(int LL,int RR,int HH){
	int l=belong[LL];
	int r=belong[RR];
	//printf("%d==%d %d==%d\n",LL,l,RR,r);
	int ans=0;
	if(l==r){
		for(int i=LL;i<=RR;i++){
			if(HH>=num[i]) ans++;
		}
	}else{
		for(int i=LL;i<=R[l];i++){
			if(HH>=num[i]) ans++;
		}
		//printf("< %d\n",ans);
		for(int i=l+1;i<=r-1;i++){
			ans+=upper_bound(rec+L[i],rec+R[i]+1,HH)-rec-L[i];
		}
		//printf("= %d\n",ans);
		for(int i=L[r];i<=RR;i++){
			if(HH>=num[i]) ans++;
		}
		//printf("> %d\n",ans);
	}
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	for(int case_num=1;case_num<=T;case_num++){
		scanf("%d %d",&N,&M);
		for(int i=0;i<N;i++){
			scanf("%d",&num[i]);
			rec[i]=num[i];
		}
		init();
		int LL,RR,HH;
		printf("Case %d:\n",case_num);
		while(M--){
			scanf("%d %d %d",&LL,&RR,&HH);
			printf("%d\n",solve(LL,RR,HH));
		}
	}
	return 0;
}
