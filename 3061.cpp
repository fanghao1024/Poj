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
		addsum[0]=num[0];
		for(int i=1;i<n;i++)
			addsum[i]=addsum[i-1]+num[i];
		if(S>addsum[n-1]){
			printf("0\n");
			continue;
		}
		int min_len=n;
		for(int i=0;addsum[i]+S<addsum[n-1];i++){
			int cur_pos=lower_bound(addsum+i,addsum+n,addsum[i]+S)-addsum;
			min_len=min(min_len,cur_pos-i);
		}
		printf("%d\n",min_len);
	}
	return 0;
}
