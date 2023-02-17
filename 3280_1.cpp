#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;

const int K=26;
const int max_m=2023;
int N,M;
char ch[max_m];
map<char,int > ma,md;
int dp[max_m][max_m];
int main(){
    scanf("%d %d",&N,&M);
    scanf("%s",ch);
    char alp[3];
    int x,y;
    for(int i=0;i<N;i++){
        scanf("%s %d %d",alp,&x,&y);
        ma[alp[0]]=x;
        md[alp[0]]=y;
    }
    for(int i=0;i<M;i++) dp[i][i]=0;
    for(int i=1;i<M;i++) dp[i][i-1]=0;
    for(int len=1;len<M;len++){
        for(int i=0;i+len<M;i++){
            if(ch[i]==ch[i+len]) dp[i][i+len]=dp[i+1][i+len-1];
            else{
                int pa=dp[i+1][i+len]+min(ma[ch[i]],md[ch[i]]);
                int pb=dp[i][i+len-1]+min(ma[ch[i+len]],md[ch[i+len]]);
                dp[i][i+len]=min(pa,pb);
            }
        }
    }
    printf("%d\n",dp[0][M-1]);
    return 0;
}