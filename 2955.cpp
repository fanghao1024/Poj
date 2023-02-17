#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
char ch[max_n];
int dp[max_n][max_n];
bool same(char a,char b){
    if(a=='('&&b==')') return true;
    if(a=='['&&b==']') return true;
    return false;
}
int main(){
    while(scanf("%s",ch)!=EOF){
        if(ch[0]=='e') break;
        int l=strlen(ch);
        memset(dp,0,sizeof(dp));
        for(int len=1;len<l;len++){
            for(int i=0;i+len<l;i++){
                if(same(ch[i],ch[i+len]))
                    dp[i][i + len] = max(dp[i][i + len], dp[i + 1][i + len - 1] + 2);
                for(int k=i;k<=i+len;k++)
                    dp[i][i + len] = max(dp[i][i + len], dp[i][k] + dp[k + 1][i + len]);
                //if(same(ch[i],ch[i+1])) dp[i][i+len]=max(dp[i][i+len],dp[i+2][i+len]+2);
                //if(same(ch[i+len-1],ch[i+len])) dp[i][i+len] = max(dp[i][i+len],dp[i][i+len-2]+2);
                //dp[i][i+len]=max(dp[i][i+len],max(dp[i+1][i+len],dp[i][i+len-1]));
            }
        }
        printf("%d\n",dp[0][l-1]);
    }
    return 0;
}