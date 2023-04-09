#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5010;

char s1[max_n],s2[max_n];
int dp[2][max_n];
int N;

int main(){
    while(scanf("%d",&N)!=EOF){
        scanf("%s",s1+1);
        for(int i=1;i<=N;i++) s2[i]=s1[N-i+1];
        memset(dp,0,sizeof(dp));
        int cur,pre;
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                cur=i%2;
                pre=1-cur;
                if(s1[i]==s2[j]) dp[cur][j]=dp[pre][j-1]+1;
                else{
                    dp[cur][j]=dp[pre][j];
                    if(dp[cur][j-1]>dp[cur][j]) dp[cur][j]=dp[cur][j-1];
                }
            }
        }
        printf("%d\n",N-dp[cur][N]);
    }
    return 0;
}