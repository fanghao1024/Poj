#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;


int dp[2020][2020];
int cost[30];
int main(){
	string s;
	int N,M;
	cin>>N>>M;
	cin>>s;
	s=" "+s;
	char ch;
	int costa,costb;
	for(int i=0;i<N;i++){
		cin>>ch>>costa>>costb;
		cost[ch-'a']=min(costa,costb);
	}
	memset(dp,0x3f,sizeof(dp));
	
	for(int i=1;i<=M;i++){
		dp[i][i]=0;
		dp[i][i-1]=0;
	}

	for(int l=2;l<=M;l++){
		for(int i=1;i<=M-l+1;i++){
			int j=i+l-1;
			if(s[i]==s[j]){
				dp[i][j]=dp[i+1][j-1];
			}else{
				dp[i][j]=min(dp[i][j-1]+cost[s[j]-'a'],dp[i+1][j]+cost[s[i]-'a']);
			}
			//cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
		}
	}
	cout<<dp[1][M]<<endl;
	return 0;
}
