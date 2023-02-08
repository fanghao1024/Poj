#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
bool cmp(int a,int b){
	return a>b;
}
int N,L;
const int max_n=70;
int rec[max_n];
bool vis[max_n];
//当前组合的木棒长度,要组合的长度，木棒已经挑选到哪个index了，已经有多少个木棒已经进入组合了
bool dfs(int len,int InitLen,int index,int num){
	if(num==N) return true;
	int prelen=-1;
	for(int i=index;i<N;i++){
		if(vis[i]||rec[i]==prelen) continue;
		vis[i]=true;
		if(len+rec[i]<InitLen){
			if(dfs(len+rec[i],InitLen,i+1,num+1)) return true;
			prelen=rec[i];
		}else{
			if(len+rec[i]==InitLen){
				if(dfs(0,InitLen,0,num+1)) return true;
				prelen=rec[i];
			}
		}
		vis[i]=false;
		if(len==0)
			break;
	}
	return false;
}
int main(){
	
	while(~scanf("%d",&N)){
		if(!N) break;
		L=0;
		for(int i=0;i<N;i++){
			scanf("%d",&rec[i]);
			L+=rec[i];
		}
		sort(rec,rec+N,cmp);
		int ans;
		bool flag=false;
		for(ans=rec[0];ans<=L/2;ans++){
			memset(vis,0,sizeof(vis));
			if(L%ans==0&&dfs(0,ans,0,0)){
				flag=true;
				break;
			}
		}
		if(!flag){printf("%d\n",L);}
		else{
			printf("%d\n",ans);
		}
		
	}
	return 0;
}
