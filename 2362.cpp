#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int N,M,m;
int num[25],sum,nxt[25];
bool vis[25];
bool ok;
bool cmp(int a,int b){return a>b;}
void dfs(int index,int last,int rest){
	int i;
	if(!rest){
		if(index==4){
			ok=true;
			return ;
		}
		for(i=0;i<M;i++){
			if(!vis[i]){
				break;
			}
		}
		vis[i]=1;
		dfs(index+1,i,m-num[i]);
		vis[i]=0;
		if(ok) return ;
		
	}
	int l=last+1,r=M-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(num[mid]<=rest) r=mid;
		else l=mid+1;
	}
	for(i=r;i<M;i++){
		if(vis[i]) continue;
		vis[i]=1;
		dfs(index,i,rest-num[i]);
		vis[i]=0;
		if(ok) return ;
		if(rest==num[i]||rest==m) return ;
		i=nxt[i];
	}
}
int main(){
	scanf("%d",&N);
	while(N--){
		scanf("%d",&M);
		sum=0;
		for(int i=0;i<M;i++){
			scanf("%d",&num[i]);
			sum+=num[i];
		}
		sort(num,num+M,cmp);
		if(sum%4!=0||num[0]>(sum/4)){
			printf("no\n");
			continue;
		}
		nxt[M-1]=M-1;
		for(int i=M-2;i>=0;i--){
			if(num[i]==num[i+1]) nxt[i]=nxt[i+1];
			else nxt[i]=i;
		}
		memset(vis,0,sizeof(vis));
		ok=false;
		m=sum/4;
		vis[0]=1;
		dfs(1,0,m-num[0]);
		if(ok) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
