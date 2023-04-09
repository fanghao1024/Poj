#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;

const int max_m=25;
const int max_n=205;
const int max_range=805;
int d[max_n],p[max_n];
bitset<max_n> B[max_m][max_range];
int dp[max_m][max_range];

int N,M;

int main(){
    int kase=1;
    while(scanf("%d %d",&N,&M)!=EOF){
        if(!N&&!M) break;
        for(int i=0;i<max_m;i++) for(int j=0;j<max_range;j++) B[i][j]&=0;
        memset(dp,-1,sizeof(dp));
        dp[0][400]=0;
        for(int i=1;i<=N;i++) scanf("%d %d",&d[i],&p[i]);
        for(int i=0;i<M;i++){
            for(int j=0;j<=800;j++){
                if(dp[i][j]==-1) continue;
                for(int k=1;k<=N;k++){
                    if (B[i][j][k] == 0 && j + d[k] - p[k] >= 0 && j + d[k] - p[k] <=800&& dp[i][j] + d[k] + p[k] > dp[i + 1][j + d[k] - p[k]])
                    {
                        dp[i + 1][j + d[k] - p[k]]= dp[i][j] + d[k] + p[k];
                        B[i + 1][j + d[k] - p[k]]=B[i][j];
                        B[i+1][j+d[k]-p[k]][k]=1;
                    }
                }
            }
        }
        int loc;
        for(int i=0;i<=400;i++){
            if(dp[M][400+i]!=-1||dp[M][400-i]!=-1){
                loc=i;
                break;
            }
        }
        if(dp[M][400+loc]>dp[M][400-loc]) loc=400+loc;
        else loc=400-loc;
        int tota=0,totb=0;
        for(int i=1;i<=N;i++){
            if(B[M][loc][i]==1) tota+=d[i],totb+=p[i];
        }
        printf("Jury #%d\n",kase++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n",tota,totb);
        for (int i = 1; i <= N; i++)
        {
            if (B[M][loc][i] == 1)
                printf(" %d",i);
        }
        printf("\n\n");
    }
    return 0;
}