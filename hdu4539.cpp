#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
const int max_m=15;

int mp[max_n][max_n];
int sta[205];
int dp[max_n][205][205];
int N,M,L;
int init(){
    int cnt=0;
    for(int i=0;i<(1<<M);i++){
        if(((i&(i<<2))==0)&&((i&(i>>2))==0)){
            sta[cnt++]=i;
        }
    }
    return cnt;
}
int count_line(int i,int s){
    int ans=0;
    for(int j=M-1;j>=0;j--){
        if(s&1) ans+=mp[i][j];
        s>>=1;
    }
    return ans;
}
int main(){
    while(scanf("%d %d",&N,&M)!=EOF){
        L=init();
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                scanf("%d",&mp[i][j]);
            }
        }
        memset(dp,0,sizeof(dp));
        int ans=0;
        for(int i=0;i<N;i++){
            for(int j=0;j<L;j++){
                for(int k=0;k<L;k++){
                    if(i==0){
                        dp[i][j][k]=count_line(i,sta[j]);
                        ans=max(ans,dp[i][j][k]);
                        continue;
                    }
                    if(sta[j]&(sta[k]<<1)||sta[j]&(sta[k]>>1)) continue;
                    int temp=0;
                    for(int p=0;p<L;p++){
                        if(sta[k]&(sta[p]<<1)||sta[k]&(sta[p]>>1)) continue;
                        if(sta[j]&sta[p]) continue;
                        temp=max(temp,dp[i-1][k][p]);
                    }
                    dp[i][j][k]=temp+count_line(i,sta[j]);
                    ans=max(ans,dp[i][j][k]);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}