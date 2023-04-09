#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2020;

int dp[max_n][max_n];
char s1[max_n],s2[max_n];

int main(){
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    int l1=strlen(s1+1),l2=strlen(s2+1);
    for(int i=0;i<=l1;i++) dp[i][0]=i;
    for(int i=0;i<=l2;i++) dp[0][i]=i;
    for(int i=1;i<=l1;i++){
        for(int j=1;j<=l2;j++){
            if(s1[i]==s2[j]) dp[i][j]=dp[i-1][j-1];
            else{
                dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
            }
        }
    }
    printf("%d\n",dp[l1][l2]);
    return 0;
}