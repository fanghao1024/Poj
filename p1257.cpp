#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int max_n=1024;
int dp[max_n];
int N;
int main(){
    while(scanf("%d",&N)!=EOF){
        int x;
        int cnt=0;
        for(int i=0;i<N;i++){
            scanf("%d",&x);
            if(cnt==0||x>dp[cnt-1]){
                dp[cnt++]=x;
            }else{
                *lower_bound(dp,dp+cnt,x)=x;
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}

