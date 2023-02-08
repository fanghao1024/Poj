#include<stdio.h>
#include<stdio.h>
#include<algorithm>
using namespace std;
int num[100010];
int addsum[100010];
int main(){
	int T,n,S;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&S);
		for(int i=0;i<n;i++)
			scanf("%d",&num[i]);
		int min_len=n;
		int s=0,t=0,sums=0;
		for(;;){
			while(t<n&&sums<S){
				sums+=num[t++];
			}
			if(sums<S) break;
			min_len=min(min_len,t-s);
		
			sums-=num[s++];

		}
		if(min_len==n){
			printf("0\n");
		}else{
			printf("%d\n",min_len);
		}
		
	}
	return 0;
}
