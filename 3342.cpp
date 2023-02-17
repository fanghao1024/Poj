#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=205;
int N,cnt;
vector<int> person[max_n];
map<string,int> msi;
string s1,s2;
int f[max_n][2];
int dp[max_n][2];
void dfs(int p){
	dp[p][0]=0;
	dp[p][1]=1;
	for(int i=0;i<person[p].size();i++){
		int v=person[p][i];
		dfs(v);
		dp[p][0]+=max(dp[v][0],dp[v][1]);
		dp[p][1]+=dp[v][0];
		if(dp[v][1]>dp[v][0]&&f[v][1]) f[p][0]=1;
		if(dp[v][0]>dp[v][1]&&f[v][0]) f[p][0]=1;
		if(dp[v][0]==dp[v][1]) f[p][0]=1;
		if(f[v][0]) f[p][1]=1;
	}
}
int main(){
	while(cin>>N){
		if(!N) break;
		msi.clear();
		for(int i=0;i<=N;i++) person[i].clear();
		memset(f,0,sizeof(f));
		//memset(dp,0,sizeof(dp));
		cnt=0;
		cin>>s1;
		msi[s1]=++cnt;
		person[0].push_back(msi[s1]);
		for(int i=0;i<N-1;i++){
			cin>>s1>>s2;
			if(msi[s1]==0) msi[s1]=++cnt;
			if(msi[s2]==0) msi[s2]=++cnt;
			person[msi[s2]].push_back(msi[s1]);
		}
		dfs(0);
		printf("%d ",dp[0][0]);
		if(f[0][0]) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}
