#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5010;

char s[max_n];
short dp[max_n][max_n];
int N;

int main(){
    while(scanf("%d",&N)!=EOF){
        scanf("%s",s+1);
        memset(dp,0,sizeof(dp));
      
        for(int len=2;len<=N;len++){
            for (int i = 1; i+len-1 <= N; i++)
            {
                int j=i+len-1;
                if(s[i]==s[j]) dp[i][j]=dp[i+1][j-1];
                else{
                    dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1;
                }
            }
        }
        printf("%d\n",dp[1][N]);
    }
    return 0;
}
