#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=15;
int M,N,top;
int corn[max_n][max_n];
int cur[max_n],state[1<<12];
int dp[max_n][1<<12];
void init(int n){
    top=0;
    for(int i=0;i<(1<<n);i++){
        if(i&(i<<1)) continue;
        state[top++]=i;
    }
}
bool check(int val,int i){
    if(val&cur[i]) return 0;
    return 1;
}
void solve(){
    for(int i=0;i<top;i++){
        if(check(state[i],1)){
            dp[1][state[i]]=1;
        }
    }
    for(int i=2;i<=M;i++){
        for(int j=0;j<top;j++){
            if(!check(state[j],i)) continue;
            for(int k=0;k<top;k++){
                if(!check(state[k],i-1)) continue;
                if(state[j]&state[k]) continue;
                dp[i][state[j]]=(dp[i][state[j]]+dp[i-1][state[k]])%1000000000;
            }
        }
    }
}
int main(){
    while(scanf("%d %d",&M,&N)!=EOF){
    for(int i=1;i<=M;i++){
        cur[i]=0;
        for(int j=1;j<=N;j++){
            scanf("%d",&corn[i][j]);
            if(!corn[i][j]) cur[i]+=1<<(N-j); //贫瘠为1,肥沃为0
        }
    }
    init(N); //种植为1，不种植为0
    memset(dp,0,sizeof(dp));
    solve();
    int ans=0;
    for(int i=0;i<top;i++) ans=(ans+dp[M][state[i]])%1000000000;
    printf("%d\n",ans);
    }
    return 0;
}