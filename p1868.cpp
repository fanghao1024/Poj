#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=15e4+10;
const int max_e=3e6+10;

int head[max_e],cnt,dp[max_e];
struct Edge{
    int to,nxt;
}edge[max_n];

void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
}
void add_edge(int x,int y){
    edge[cnt].to=y;
    edge[cnt].nxt=head[x];
    head[x]=cnt++;
}
int N;
int main(){
    scanf("%d",&N);
    int x,y;
    int Max=-1;
    init();
    for(int i=1;i<=N;i++){
        scanf("%d %d",&x,&y);
        add_edge(y,x);
        Max=max(y,Max);
    }
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=Max;i++){
        dp[i]=dp[i-1];
        for(int j=head[i];j!=-1;j=edge[j].nxt){
            int v=edge[j].to;
            dp[i]=max(dp[i],dp[v-1]+i-v+1);
        }
    }
    printf("%d\n",dp[Max]);
    return 0;
}
