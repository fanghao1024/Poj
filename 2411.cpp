#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int h,w;
int now,old;
long long dp[2][1<<11];
int main(){
	while(scanf("%d%d",&h,&w)!=EOF){
		if(h==0&&w==0) break;
	//while(cin>>h>>w&&h){
		if(h<w) swap(h,w);
		memset(dp,0,sizeof(dp));
		now=0;
		old=1;
		dp[now][(1<<w)-1]=1;
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				swap(old,now);
				memset(dp[now],0,sizeof(dp[now]));
				for(int k=0;k<(1<<w);k++){
					if(k&1<<(w-1)){
						dp[now][(k<<1)&(~(1<<w))]+=dp[old][k];
					}
					if(i&&(!(k&1<<(w-1)))){
						dp[now][(k<<1)^1]+=dp[old][k];
					}
					if(j&&(k&1<<(w-1))&&(!(k&1))){
						dp[now][((k<<1)|3)&(~(1<<w))]+=dp[old][k];
					}
				}
			}
			
		}
		printf("%I64d\n",dp[now][(1<<w)-1]);
		//cout<<dp[now][(1<<w)-1]<<endl;
	}
	return 0;
}
