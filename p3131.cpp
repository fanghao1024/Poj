#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=5e4+10;
int N;
ll num[max_n];
int first[10],last[10];
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%lld",&num[i]),num[i]+=num[i-1];
	//for(int i=1;i<=N;i++) printf("%lld ",num[i]);
	//printf("\n");
	int count=0;
	memset(first,-1,sizeof(first));
	memset(last,-1,sizeof(last));
	for(int i=1;i<=N;i++){
		int x=num[i]%7;
		if(first[x]==-1){
			first[x]=i;
			count++;
			if(count>=7) break;
		}
	}
	first[0]=0;
	count=0;
	for(int i=N;i>=1;i--){
		int x=num[i]%7;
		if(last[x]==-1){
			last[x]=i;
			count++;
			if(count>=7) break;
		}
	}
	int ans=0;
	for(int i=0;i<=6;i++){
		if(first[i]==-1||last[i]==-1) continue;
		//printf("~~%d %d %d\n",i,first[i],last[i]);
		ans=max(ans,last[i]-first[i]);
	}
	printf("%d\n",ans);
	return 0;
}
